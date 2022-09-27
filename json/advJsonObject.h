/*
 * File:   advJsonObject.h
 * Author: sluo
 *
 * Created on November 4, 2019, 2:31 PM
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

#ifndef ADVJSONOBJECT_H
#define	ADVJSONOBJECT_H

#include "advJsonElement.h"
typedef vector<string> TStrList;
class advJsonObject : public advJsonElement {
    friend class advJsonArray;
    friend class advJsonParser;
    friend class advJsonElement;
public:
    typedef enum {
        MERGE_REPLACE,
        MERGE_SKIP,
        MERGE_ERROR,
    } TMergeOption;
    advJsonObject(JVPtr jv);
    advJsonObject();
    advJsonObject(const string &jsonStr);
    virtual ~advJsonObject(){};
    
    void set(const string &key, const char *value);
    void set(const string &key, const string &value);
    void set(const string &key, double value);
    void set(const string &key, int64_t value);
    void set(const string &key, bool value);
    void set(const string &key, advJsonElementPtr je);
    void set(const string &key);
    void merge(advJsonObjectPtr obj, TMergeOption mergeOpt = MERGE_REPLACE);
    void erase(const string &key);

    string getAsString(const string & key, bool checkType = false);
    int64_t getAsInteger(const string & key, bool checkType = false);
    double getAsNumber(const string & key, bool checkType = false);
    bool getAsBool(const string & key, bool checkType = false);
    advJsonArrayPtr getAsArray(const string & key, bool checkType = false);
    advJsonObjectPtr getAsObject(const string & key, bool checkType = false);
    advJsonElementPtr getChild(const string & key);
    TStrList getAllKeys();
    TStrSet getKeySet();

    bool has(const string & key);
    bool isChildArray(const string & key);
    bool isChildObject(const string & key);
    bool isChildNULL(const string & key);
    bool isChildNumber(const string & key);
    bool isChildInteger(const string & key);
    bool isChildBoolean(const string & key);
    bool isChildString(const string & key);
    
protected:
};

#endif	/* ADVJSONOBJECT_H */

