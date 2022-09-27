/*
 * CryptAES.h
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

#ifndef SRC_CRYPT_CRYPTAES_H_
#define SRC_CRYPT_CRYPTAES_H_

#include "CryptBase.h"
#include <openssl/evp.h>
#include <openssl/aes.h>

class CryptAES : public CryptBase {
public:
	CryptAES();
	virtual ~CryptAES();
	virtual void operator << (string data) override;
	virtual string resultBinary() override;
	virtual string resultHex() override;
	void initForEncrypt(string key, string iv);
	void initForDecrypt(string key, string iv);
	static string genIV();
	static string genKey();
protected:
	EVP_CIPHER_CTX *ctx;
	string result;
	bool encrypt;
	unsigned char *cipher_buf;
	uint32_t blocksize;
};

#endif /* SRC_CRYPT_CRYPTAES_H_ */
