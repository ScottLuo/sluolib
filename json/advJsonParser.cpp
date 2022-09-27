/*
 * File:   advJsonParser.cpp
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

#include "advJsonParser.h"
#include "utils/Exception.h"
#include <iostream>

class advJsonParserHandler :
    public BaseReaderHandler<UTF8<>, advJsonParserHandler> {
public:
    advJsonParserHandler() {
    }

    virtual ~advJsonParserHandler() {
    }
    
    void setRoot(advJsonElementPtr rootEle) {
        root = rootEle;
    }
    
    bool Null() { 
        JVPtr jv = getJV(JSONType_Null);
        return saveValue(jv);
    }
    
    bool Bool(bool b) {
        JVPtr jv = getJV(JSONType_Null);
        jv->setToBoolean(b);
        return saveValue(jv);
    }
    
    bool Int(int i) {
        return Int64(i);
    }
    bool Uint(unsigned u) { 
        return Int64(u);
    }
    
    bool Int64(int64_t i) { 
        JVPtr jv = getJV(JSONType_Null);
        jv->setToInteger(i);
        return saveValue(jv);
    }
    
    bool Uint64(uint64_t u) { 
        return Double(u);
    }
    
    bool Double(double d) { 
        JVPtr jv = getJV(JSONType_Null);
        jv->setToFloat(d);
        return saveValue(jv);
    }
    
    bool String(const char* str, SizeType length, bool copy) {
        string tmp(str, length);
        JVPtr jv = getJV(JSONType_String);
        jv->setToString(tmp);
        return saveValue(jv);
    }
    
    bool StartObject() {
        return handleObjOrArr(JSONType_Object);
    }

    bool Key(const char* str, SizeType length, bool copy) {
        key.assign(str, length);
        return true;
    }
    bool EndObject(SizeType memberCount) { 
        stack.pop_back();
        return true;
    }
    
    bool StartArray() { 
        return handleObjOrArr(JSONType_Array);
    }
    
    bool EndArray(SizeType elementCount) {
        stack.pop_back();
        return true;
    }
protected:
    bool saveValue(JVPtr &jv) {
        if (stack.size() > 0) {
            if (stack.back()->IsArray()) {
                stack.back()->AsArray().push_back(jv);
            } else if (stack.back()->IsObject()) {
                if (key.size() > 0) {
                    stack.back()->AsObject()[key] = jv;
                    key.clear();
                } else {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    
    JVPtr getJV(JSONType type) {
        return make_shared<JSONValue>(type, 0);
    }
    
    bool handleObjOrArr(JSONType type) {
        JVPtr jv = getJV(type);
        if (root->jvPtr.get() == NULL && stack.empty()) {
            root->jvPtr = jv;
            stack.push_back(jv.get());
        } else {
            if (stack.back()->IsArray()) {
                stack.back()->AsArray().push_back(jv);
                stack.push_back(jv.get());
            } else if (stack.back()->IsObject()) {
                if (key.size() > 0) {
                    stack.back()->AsObject()[key] = jv;
                    stack.push_back(jv.get());
                    key.clear();
                } else {
                    return false;
                }
            }    
        }
        return true;
    }
    
    advJsonElementPtr root;
    vector<JSONValue *> stack;
    string key;
};








advJsonParser::advJsonParser() : flgOK(false) {
    
}

advJsonElementPtr advJsonParser::parse(ifstream &file) {
    string line;
    string content;
    if (file.is_open()) {
            while (getline(file, line)) {
                    content += line;
            }
            file.close();
    }

    return parse(content.c_str());
}

advJsonElementPtr advJsonParser::parse(const string &utf8Str) {
    return parse(utf8Str.c_str());
}

advJsonElementPtr advJsonParser::parse(const char * utf8Str) {
    flgOK = false;
    StringStream ss(utf8Str);    
    advJsonElementPtr ret = make_shared<advJsonElement>();
    advJsonParserHandler handler;
    handler.setRoot(ret);
    bool res = reader.Parse(ss, handler);
    if (!res) {
        flgOK = false;
        ret->clear();
    } else {
        flgOK = true;
    }
    return ret;
}

bool advJsonParser::good() {
    return flgOK;
};


