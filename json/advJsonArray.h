/*
 * File:   advJsonArray.h
 * Author: sluo
 *
 * Created on November 4, 2019, 2:42 PM
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

#ifndef ADVJSONARRAY_H
#define	ADVJSONARRAY_H

#include "advJsonElement.h"

class advJsonArray : public advJsonElement {
    friend class advJsonObject;
    friend class advJsonParser;
    friend class advJsonElement;    
public:
    advJsonArray(JVPtr jv);
    advJsonArray();
    advJsonArray(const string &jsonStr);
    void insert(size_t index, const char *value);
    void insert(size_t index, const string &value);
    void insert(size_t index, double value);
    void insert(size_t index, int64_t value);
    void insert(size_t index, bool value);
    void insert(size_t index);
    void insert(size_t index, advJsonElementPtr je);

    void replace(size_t index, const char *value);
    void replace(size_t index, const string &value);
    void replace(size_t index, double value);
    void replace(size_t index, int64_t value);
    void replace(size_t index, bool value);
    void replace(size_t index);
    void replace(size_t index, advJsonElementPtr je);

    void pushback(const char *value);
    void pushback(const string &value);
    void pushback(double value);
    void pushback(int64_t value);
    void pushback(bool value);
    void pushback();
    void pushback(advJsonElementPtr je);

    void merge(advJsonArrayPtr arr);
    
    void erase(size_t index);
    size_t size();

    string getAsString(size_t index, bool checkType = false);
    int64_t getAsInteger(size_t index, bool checkType = false);
    double getAsNumber(size_t index, bool checkType = false);
    bool getAsBool(size_t index, bool checkType = false);
    advJsonArrayPtr getAsArray(size_t index, bool checkType = false);
    advJsonObjectPtr getAsObject(size_t index, bool checkType = false);
    advJsonElementPtr getChild(size_t index);

    bool isChildArray(size_t index);
    bool isChildObject(size_t index);
    bool isChildNULL(size_t index);
    bool isChildNumber(size_t index);
    bool isChildInteger(size_t index);
    bool isChildBoolean(size_t index);
    bool isChildString(size_t index);
    
protected:

};

#endif	/* ADVJSONARRAY_H */

