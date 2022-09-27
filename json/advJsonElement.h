/*
 * File:   advJsonElement.h
 * Author: sluo
 *
 * Created on November 4, 2019, 2:34 PM
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

#ifndef ADVJSONELEMENT_H
#define	ADVJSONELEMENT_H

#include <memory>
#include <string>
#include "utf8.h"
#include "JSONValue.h"


using namespace std;

class advJsonElement;
class advJsonObject;
class advJsonArray;
class advJsonParser;

typedef std::shared_ptr<advJsonElement> advJsonElementPtr;
typedef std::shared_ptr<advJsonObject> advJsonObjectPtr;
typedef std::shared_ptr<advJsonArray> advJsonArrayPtr;
typedef std::shared_ptr<advJsonParser> advJsonRootPtr;

class advJsonElement {
    friend class advJsonArray;
    friend class advJsonObject;
    friend class advJsonParserHandler;
public:
    advJsonElement(){};
    advJsonElement(const string &jsonStr);
    virtual ~advJsonElement(){};
    string toText(bool pretty = false);
    bool isNULL();
    bool isArray();
    bool isObject();
    bool isNumber();
    bool isInteger();
    bool isBoolean();
    bool isString();
    
    advJsonObjectPtr toObject();
    advJsonArrayPtr toArray();
    
    void clear() {
        jvPtr = NULL;
    }
    
    void swap(advJsonElementPtr jelement);

    string convert2XML(const string &rootTag);
protected:
    advJsonElement(JVPtr jv);
    JVPtr jvPtr;
};

#endif	/* ADVJSONELEMENT_H */

