/*
 * File:   advJsonArray.cpp
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

#include "advJsonArray.h"
#include "advJsonObject.h"
#include "utils/Exception.h"

advJsonArray::advJsonArray() {
    jvPtr = make_shared<JSONValue>(JSONType_Array, 0);

}

advJsonArray::advJsonArray(const string &jsonStr) : advJsonElement(jsonStr) {
    if (this->jvPtr->IsArray()) {
        // OK
    } else {
        throw Exception("JSON is not an array");
    }
}

advJsonArray::advJsonArray(JVPtr jv) : advJsonElement(jv) {
}

/**
 * Insert an element after the given index to JSON array.
 * if the given index is large than the array size,
 * will push the value to the end of of the array.
 *
 * @access public
 *
 * @return
 *
 */
void advJsonArray::insert(size_t index, const char *value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, make_shared<JSONValue>(value));
    } else {
        pushback(value);
    }
}

void advJsonArray::insert(size_t index, const string &value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, make_shared<JSONValue>(value));
    } else {
        pushback(value);
    }
}

void advJsonArray::insert(size_t index, double value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, make_shared<JSONValue>(value));
    } else {
        pushback(value);
    }
}

void advJsonArray::insert(size_t index, int64_t value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, make_shared<JSONValue>(value));
    } else {
        pushback(value);
    }
}

void advJsonArray::insert(size_t index, bool value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, make_shared<JSONValue>(value));
    } else {
        pushback(value);
    }
}

void advJsonArray::insert(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, JVPtr(new JSONValue()));
    } else {
        pushback();
    }
}

void advJsonArray::insert(size_t index, advJsonElementPtr je) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        root.insert(it + index, je->jvPtr);
    } else {
        pushback(je);
    }
}

/**
 * Replace the element to the given index of the JSON array.
 * if the given index is large than the array size,
 * will push the value to the end of array
 *
 * @access public
 *
 * @return
 *
 */
void advJsonArray::replace(size_t index, const char *value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = make_shared<JSONValue>(value);
    } else {
        pushback(value);
    }
}

void advJsonArray::replace(size_t index, const string &value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {

        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = make_shared<JSONValue>(value);
    } else {
        pushback(value);
    }
}

void advJsonArray::replace(size_t index, double value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {

        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = make_shared<JSONValue>(value);
    } else {
        pushback(value);
    }
}

void advJsonArray::replace(size_t index, int64_t value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {

        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = make_shared<JSONValue>(value);
    } else {
        pushback(value);
    }
}

void advJsonArray::replace(size_t index, bool value) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {

        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = make_shared<JSONValue>(value);
    } else {
        pushback(value);
    }
}

void advJsonArray::replace(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {

        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = JVPtr(new JSONValue());
    } else {
        pushback();
    }
}

void advJsonArray::replace(size_t index, advJsonElementPtr je) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index].get() != NULL) {
            root[index] = NULL;
        }
        root[index] = je->jvPtr;
    } else {
        pushback(je);
    }
}

/**
 * add an element to the end of the JSON array.
 *
 * @access public
 *
 * @return
 *
 */
void advJsonArray::pushback(const char *value) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(make_shared<JSONValue>(value));
}

void advJsonArray::pushback(const string &value) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(make_shared<JSONValue>(value));
}

void advJsonArray::pushback(double value) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(make_shared<JSONValue>(value));
}

void advJsonArray::pushback(int64_t value) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(make_shared<JSONValue>(value));
}

void advJsonArray::pushback(bool value) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(make_shared<JSONValue>(value));
}

void advJsonArray::pushback() {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(JVPtr(new JSONValue()));
}

void advJsonArray::pushback(advJsonElementPtr je) {
    JSONArray &root = jvPtr->AsArray();
    root.push_back(je->jvPtr);
}

void advJsonArray::merge(advJsonArrayPtr arr) {
    for (size_t i = 0; i < arr->size(); i ++) {
        pushback(arr->getChild(i));
    }
}

/**
 * Erase an element of the JSON array.
 *
 * @access public
 *
 * @return
 *
 */
void advJsonArray::erase(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        JSONArray::iterator it = root.begin();
        it += index;
        root.erase(it);
    }
}

/**
 * Return the size of the JSON array.
 *
 * @access public
 *
 * @return size
 *
 */
size_t advJsonArray::size() {
    JSONArray &root = jvPtr->AsArray();
    return root.size();
}

/**
 * Return the value of given index item of the JSON array.
 *
 * @access public
 *
 * @return value
 *
 */
string advJsonArray::getAsString(size_t index, bool checkType) {
    string ret;
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsString()) {
            ret = root[index]->AsString();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return ret;
}

int64_t advJsonArray::getAsInteger(size_t index, bool checkType) {
    int ret = 0;
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsInteger()) {
            ret = root[index]->AsInteger();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return ret;
}

double advJsonArray::getAsNumber(size_t index, bool checkType) {
    double ret = 0.0;
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsNumber()) {
            ret = root[index]->AsNumber();
        } else if (root[index]->IsInteger()) {
            ret = root[index]->AsInteger();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return ret;
}

bool advJsonArray::getAsBool(size_t index, bool checkType) {
    bool ret = false;
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsBool()) {
            ret = root[index]->AsBool();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return ret;
}

advJsonArrayPtr advJsonArray::getAsArray(size_t index, bool checkType) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsArray()) {
            advJsonArrayPtr pJsonArr(new advJsonArray(root[index]));
            return pJsonArr;
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return NULL;
}

advJsonObjectPtr advJsonArray::getAsObject(size_t index, bool checkType) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        if (root[index]->IsObject()) {
            advJsonObjectPtr pJsonObj(new advJsonObject(root[index]));
            return pJsonObj;
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for array(%d), type mismatch", index);
            }
        }
    }
    return NULL;
}

advJsonElementPtr advJsonArray::getChild(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        advJsonElementPtr pJsonEle(new advJsonElement(root[index]));
        return pJsonEle;
    } else {
        return NULL;
    }
}

bool advJsonArray::isChildArray(size_t index){
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsArray();
    }
    return false;
}

bool advJsonArray::isChildObject(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsObject();
    }
    return false;
}

bool advJsonArray::isChildNULL(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsNull();
    }
    return false;
}

bool advJsonArray::isChildNumber(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsNumber();
    }
    return false;
}

bool advJsonArray::isChildInteger(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsInteger();
    }
    return false;
}

bool advJsonArray::isChildBoolean(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsBool();
    }
    return false;
}

bool advJsonArray::isChildString(size_t index) {
    JSONArray &root = jvPtr->AsArray();
    if (index < root.size()) {
        return root[index]->IsString();
    }
    return false;
}
