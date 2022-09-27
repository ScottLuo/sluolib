/*
 * powerString.cpp
 *
 *  Created on: Jan 5, 2021
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

#include <utils/PowerString.h>
#include <utils/utils.h>
#include <iostream>

PowerString::PowerString(string str) : data(str) {
	// TODO Auto-generated constructor stub

}

PowerString::~PowerString() {
	// TODO Auto-generated destructor stub
}

string PowerString::str() {
	return data;
}

uint32_t PowerString::checksumXOR() {
	const char *pBuf = data.c_str();
	size_t size = data.length();
	unsigned char ret = 0;
	// 8-bit XOR of the data
	while (size--) {
		ret ^= *pBuf++;
	}
	return (ret);
}

string PowerString::fixLengthFromLeft(size_t len, char FillChar) {
	string ret(data);
	ret.append(len, FillChar);
	ret = ret.substr(0, len);
    return ret;
}

string PowerString::fixLengthFromRight(size_t len, char FillChar) {
	string ret(data);
	ret.insert(0, len, FillChar);
	ret = ret.substr(ret.size() - len, len);
    return ret;
}

string PowerString::replaceAll(string find, string replace) {
	string ret;
	size_t findStrLen = find.length();
	size_t findBegin = 0;
	const char *p = data.c_str();
    string::size_type loc = data.find(find, findBegin);
    while (loc != string::npos) {
    	ret.append((p+findBegin), loc - findBegin);
    	ret.append(replace);
    	findBegin = loc + findStrLen;
    	loc = data.find(find, findBegin);
    }

    if (findBegin < data.length()) {
    	ret.append((p + findBegin), data.length() - findBegin);
    }

    return ret;
}

string PowerString::toUpper() {
	string ret;
	const char *p = data.c_str();
	for (size_t i = 0; i < data.size(); i++) {
		ret.push_back(toupper(p[i]));
	}
    return ret;
}

string PowerString::toLower() {
	string ret;
	const char *p = data.c_str();
	for (size_t i = 0; i < data.size(); i++) {
		ret.push_back(tolower(p[i]));
	}
    return ret;
}


string PowerString::toHex() {
	return utils::toHex(data.c_str(), data.length(), false);
}

string PowerString::toHexWithSpace() {
	return utils::toHex(data.c_str(), data.length(), true);
}

string PowerString::toBinary(bool withSpace) {
	string ret;
	int width = 2;
	if (withSpace) width ++;

	for (size_t i = 0 ; i < data.size(); i += width) {
		char h = data.at(i);
		char l = data.at(i + 1);
		h = hexToBin(h);
		l = hexToBin(l);
		char c = h * 16 + l;
		ret.push_back(c);
	}
	return ret;
}

// TEST
#ifdef TEST
#include "test/test.h"

class UnitTest_PowerString : public UnitTest {
public:

protected:
	virtual void doTest() override {
		string s;
		s = "9387faskdfnvxklcmvnbiw465918234skjfdhgwABCDEFG";
		cout << PowerString(s).checksumXOR() << endl;
		cout << PowerString(s).toUpper() << endl;
		cout << PowerString(s).toLower() << endl;
		cout << PowerString(s).toHex() << endl;
		cout << PowerString(s).toHexWithSpace() << endl;

		s = "0123456789";
		cout << PowerString(s).fixLengthFromLeft(6,'#') << endl;
		cout << PowerString(s).fixLengthFromLeft(16,'#') << endl;
		cout << PowerString(s).fixLengthFromRight(6,'#') << endl;
		cout << PowerString(s).fixLengthFromRight(16,'#') << endl;

		s = "123412341234123412341234";
		PowerString ps(s);
		cout << ps.replaceAll("12", "000") << endl;
		cout << ps.replaceAll("23", "000") << endl;
		cout << ps.replaceAll("34", "000") << endl;
		cout << ps.replaceAll("41", "000") << endl;

		cout << ps.replaceAll("12", "0") << endl;
		cout << ps.replaceAll("23", "0") << endl;
		cout << ps.replaceAll("34", "0") << endl;
		cout << ps.replaceAll("41", "0") << endl;
	}
};

UnitTest_PowerString test_PowerString;

#endif
