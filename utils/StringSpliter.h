/* 
 * File:   stringSpliter.h
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

#ifndef STRINGSPLITER_H
#define	STRINGSPLITER_H

#include <string>
#include <vector>

using namespace std;

class StringSpliter {
public:
    StringSpliter(const string &str, char de);
    StringSpliter(const string &str, string de);
    virtual ~StringSpliter();
    string getField(size_t n);
    size_t getNumberOfFields();
    string getFirst();
    string getLast();
    string getStr(size_t begin, size_t end);
protected:
    const string &data;
    string delimiter;
    vector<size_t> pos;
    
    void parseString();
};

#endif	/* STRINGSPLITER_H */

