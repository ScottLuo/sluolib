/*
 * File:   advJsonParser.h
 * Author: sluo
 *
 * Created on November 4, 2019, 2:44 PM
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

#ifndef ADVJSONPARSER_H
#define	ADVJSONPARSER_H

#include <fstream>
#include "advJsonElement.h"
#include "advJsonArray.h"
#include "advJsonObject.h"
#include "rapidjson/reader.h"
#include "rapidjson/error/en.h"

using namespace rapidjson;
using namespace std;

class advJsonParserHandler;

class advJsonParser {
public:
    advJsonParser();

    advJsonElementPtr parse(const char * utf8Str);
    advJsonElementPtr parse(ifstream& file);
    advJsonElementPtr parse(const string &utf8Str);

    bool good();
protected:
    bool flgOK;
    Reader reader;
};

#endif	/* ADVJSONPARSER_H */

