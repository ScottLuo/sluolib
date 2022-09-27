/*
 * CryptSha256.cpp
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

#include <crypt/CryptSha256.h>
#include <utils/utils.h>

CryptSha256::CryptSha256() {
	// TODO Auto-generated constructor stub
	SHA256_Init(&ctx);

}

CryptSha256::~CryptSha256() {
	// TODO Auto-generated destructor stub
}

void CryptSha256::operator <<(string data) {
	SHA256_Update(&ctx, data.c_str(), data.length());
}

string CryptSha256::resultBinary() {
	char hash[SHA256_DIGEST_LENGTH];
	SHA256_Final((unsigned char*) hash, &ctx);
	string ret(hash, SHA256_DIGEST_LENGTH);
	return ret;
}

string CryptSha256::resultHex() {
	string data = resultBinary();
	return utils::toHex(data.c_str(), data.size(), false);
}

