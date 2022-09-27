/*
 * CryptAES.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: sluo
 * 
 * 
 * Copyright (c) 2021 Scott Luo (MIT License)
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include <crypt/CryptAES.h>
#include <utils/utils.h>
#include <utils/PowerString.h>
#include "Random.h"

#define BUF_SIZE 4096

CryptAES::CryptAES() {
	// TODO Auto-generated constructor stub
	ctx = EVP_CIPHER_CTX_new();
}

CryptAES::~CryptAES() {
	// TODO Auto-generated destructor stub
	EVP_CIPHER_CTX_free(ctx);
}

void CryptAES::initForEncrypt(string key, string iv) {
	key = PowerString(key).fixLengthFromLeft(EVP_MAX_KEY_LENGTH);
	iv = PowerString(iv).fixLengthFromLeft(EVP_MAX_IV_LENGTH);
	EVP_EncryptInit(ctx,EVP_aes_256_cbc(), (const unsigned char *)key.c_str(),(const unsigned char *)iv.c_str());
	encrypt = true;
	EVP_CIPHER_CTX_set_key_length(ctx, EVP_MAX_KEY_LENGTH);
	blocksize = EVP_CIPHER_CTX_block_size(ctx);
	cipher_buf = (unsigned char *)malloc(BUF_SIZE + blocksize);
}

void CryptAES::initForDecrypt(string key, string iv) {
	key = PowerString(key).fixLengthFromLeft(EVP_MAX_KEY_LENGTH);
	iv = PowerString(iv).fixLengthFromLeft(EVP_MAX_IV_LENGTH);
	EVP_DecryptInit(ctx,EVP_aes_256_cbc(), (const unsigned char *)key.c_str(),(const unsigned char *)iv.c_str());
	encrypt = false;
	EVP_CIPHER_CTX_set_key_length(ctx, EVP_MAX_KEY_LENGTH);
	blocksize = EVP_CIPHER_CTX_block_size(ctx);
	cipher_buf = (unsigned char *)malloc(BUF_SIZE + blocksize);
}

void CryptAES::operator <<(string data) {
	unsigned char *p = (unsigned char *)data.c_str();
	int32_t k = data.size();
	while  (k > 0) {
		int len = 0;
		int inputLen = BUF_SIZE;
		if (k < BUF_SIZE) {
			inputLen = k;
		}
		if (encrypt) {
			EVP_EncryptUpdate(ctx, cipher_buf, &len, p, inputLen);
		} else {
			EVP_DecryptUpdate(ctx, cipher_buf, &len, p, inputLen);
		}
		if (len > 0) {
			result.append((char *)cipher_buf, len);
		}
		p += inputLen;
		k -= inputLen;
	}
}

string CryptAES::resultBinary() {
	int len = 0;
	if (encrypt) {
		EVP_EncryptFinal(ctx,cipher_buf,&len);
	} else {
		EVP_DecryptFinal(ctx,cipher_buf,&len);
	}
	result.append((char *)cipher_buf, len);
	free(cipher_buf);
	return result;
}

string CryptAES::resultHex() {
	string data = resultBinary();
	return utils::toHex(data.c_str(), data.size(), false);
}

string CryptAES::genIV() {
	return Random::getInstance()->getRnd(EVP_MAX_IV_LENGTH);
}

string CryptAES::genKey() {
	return Random::getInstance()->getRnd(EVP_MAX_KEY_LENGTH);
}

// TEST
#ifdef TEST
#include "test/test.h"

class UnitTest_CryptAES : public UnitTest {
public:

protected:
	virtual void doTest() override {
		string key("1234567812345678");
		string iv("1234567812345678");

		{
		string data("0123456789abcdef0123456789abcdef");
		string result;
		CryptAES aes1;
		aes1.initForEncrypt(key, iv);
		aes1 << data;
		result = aes1.resultBinary();
		cout << PowerString(result).toHex() << endl;

		CryptAES aes2;
		aes2.initForDecrypt(key, iv);
		aes2 << result;
		result = aes2.resultBinary();

		cout << data << endl;
		cout << result << endl;
		}

		string ret;
		{
			CryptAES aes1;
			aes1.initForEncrypt(key, iv);
			aes1 << "10000";
			ret = aes1.resultBinary();
			cout << PowerString(ret).toHex() << endl;

			CryptAES aes2;
			aes2.initForDecrypt(key, iv);
			aes2 << ret;
			cout << aes2.resultBinary() << endl;
		}

		{
			CryptAES aes;
			aes.initForEncrypt("12345678", "12345678");
			aes << "10000";
			cout << aes.resultHex() << endl;
		}
		{
			CryptAES aes;
			aes.initForEncrypt("12345678", "12345678");
			aes << "10000";
			cout << aes.resultHex() << endl;
		}

	}
};

UnitTest_CryptAES test_CryptAES;

#endif

