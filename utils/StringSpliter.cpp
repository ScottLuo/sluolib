/*
 * File:   stringSpliter.cpp
 * Author: sluo
 *
 * Created on February 14, 2020, 10:10 AM
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

#include <utils/StringSpliter.h>

StringSpliter::StringSpliter(const string &str, char de) : data(str), delimiter(1, de) {
    parseString();
}

StringSpliter::StringSpliter(const string &str, string de) : data(str), delimiter(de) {
    parseString();
}


StringSpliter::~StringSpliter() {
}

void StringSpliter::parseString() {
    pos.push_back(0);
    size_t start = 0;
    size_t l = data.find(delimiter, start);
    while (l != string::npos) {
        start = l + delimiter.size();
        pos.push_back(start);
        l = data.find(delimiter, start);
    }

    pos.push_back(data.size() + delimiter.size());
}

string StringSpliter::getField(size_t n) {
    string ret;
    if (n < pos.size() - 1) {
        size_t start = pos[n];
        size_t len = pos[n + 1] - start - delimiter.size();
        ret = data.substr(start, len);
    }

    return ret;
}

string StringSpliter::getFirst() {
    return getField(0);
}

string StringSpliter::getLast() {
    return getField(getNumberOfFields() - 1);
}

string StringSpliter::getStr(size_t begin, size_t end) {
    string ret;
    if ((begin < pos.size() - 1) && (end >= begin && end < pos.size() - 1)) {
        size_t start = pos[begin];
        size_t len = pos[end + 1] - start - delimiter.size();
        ret = data.substr(start, len);
    }
    return ret;
}

size_t StringSpliter::getNumberOfFields() {
    return pos.size() - 1;
}