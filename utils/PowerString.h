/*
 * PowerString.h
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

#ifndef SRC_UTILS_POWERSTRING_H_
#define SRC_UTILS_POWERSTRING_H_
#include <string>
#include "utils/Exception.h"

using namespace std;

class PowerString {
public:
	PowerString(string str);
	virtual ~PowerString();
    uint32_t checksumXOR();
    string fixLengthFromLeft(size_t len, char FillChar = 0);
    string fixLengthFromRight(size_t len, char FillChar = 0);
    string replaceAll(string find, string replace);

    string toLower();
    string toUpper();

    string toHex();
    string toHexWithSpace();
    string toBinary(bool withSpace = false);

    string str();
protected:
    char hexToBin(char c) {
    	if (c >= '0' && c <= '9') {
    		return c - '0';
    	} else if (c >= 'a' && c <= 'f') {
    		return c - 'a' + 10;
    	} else if (c >= 'A' && c <= 'F') {
    		return c - 'A' + 10;
    	} else {
    		throw Exception("invalid hex");
    	}
    }
    string data;
};

#endif /* SRC_UTILS_POWERSTRING_H_ */
