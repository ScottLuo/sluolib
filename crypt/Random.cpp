/*
 * Random.cpp
 *
 *  Created on: Feb 19, 2021
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

#include <crypt/Random.h>
#include <time.h>
#include <stdlib.h>

shared_ptr<Random> Random::rnd;

Random::Random() {
	// TODO Auto-generated constructor stub
	srand(time(0));
}

Random::~Random() {
	// TODO Auto-generated destructor stub
}

string Random::getRnd(size_t len) {
	string ret;
	for (size_t i = 0; i < len; i++) {
		char c = rand() % 256;
		ret.push_back(c);
	}
	return ret;
}

int64_t Random::getRndInt64() {
    int32_t a[2];
    a[0] = rand();
    a[1] = rand();
    int64_t *p = (int64_t *)a;
    return *p;
}

int32_t Random::getRndInt32() {
    return rand();
}

int16_t Random::getRndInt16() {
    int16_t ret = rand() % 0x10000;
    return ret;
}

int8_t Random::getRndInt8() {
    int16_t ret = rand() % 0x100;
    return ret;
}
