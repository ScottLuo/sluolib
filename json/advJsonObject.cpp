/*
 * File:   advJsonObject.cpp
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

#include "advJsonObject.h"
#include "advJsonArray.h"
#include "utils/Exception.h"

advJsonObject::advJsonObject() {
    jvPtr = make_shared<JSONValue>(JSONType_Object, 0);
}

advJsonObject::advJsonObject(const string &jsonStr) : advJsonElement(jsonStr) {
    if (this->jvPtr->IsObject()) {
        // OK
    } else {
        throw Exception("JSON is not an object");
    }
}

/**
 * Set a new key:value pair to JSON object.
 *
 *
 * @access public
 *
 * @return
 *
 */
void advJsonObject::set(const string &key, const char *value) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = make_shared<JSONValue>(value);
}

void advJsonObject::set(const string &key, const string &value) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = make_shared<JSONValue>(value);
}

void advJsonObject::set(const string &key, double value) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = make_shared<JSONValue>(value);
}

void advJsonObject::set(const string &key, int64_t value) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = make_shared<JSONValue>(value);
}

void advJsonObject::set(const string &key, bool value) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = make_shared<JSONValue>(value);
}

void advJsonObject::set(const string &key, advJsonElementPtr je) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = je->jvPtr;
}

void advJsonObject::set(const string &key) {
    erase(key);
    JSONObject &root = jvPtr->AsObject();
    root[key] = JVPtr(new JSONValue());
}

void advJsonObject::merge(advJsonObjectPtr obj, TMergeOption mergeOpt) {
    TStrList keys = obj->getAllKeys();
    for (size_t i = 0; i < keys.size(); i ++) {
        switch (mergeOpt) {
            case MERGE_REPLACE:
                set(keys[i], obj->getChild(keys[i]));
                break;
            case MERGE_SKIP:
                if (!has(keys[i])) {
                    set(keys[i], obj->getChild(keys[i]));
                }
                break;
            default:
                if (has(keys[i])) {
                    throw Exception("Duplicated key(%s)", keys[i].c_str());
                } else {
                    set(keys[i], obj->getChild(keys[i]));
                }
                break;
        }
    }
}

void advJsonObject::erase(const string &key) {
    JSONObject &root = jvPtr->AsObject();
    JSONObject::iterator ii = root.find(key);
    if (ii != root.end()) {
        ii->second = NULL;
        root.erase(ii);
    }
}

/**
 * Get value of a key from JSON object.
 *
 *
 * @access public
 *
 * @return value
 *
 */
string advJsonObject::getAsString(const string &key, bool checkType) {
    string ret;
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        if (root[key]->IsString()) {
            ret = root[key]->AsString();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }
    return ret;
}

int64_t advJsonObject::getAsInteger(const string &key, bool checkType) {
    int64_t ret = 0;
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        if (root[key]->IsInteger()) {
            ret = root[key]->AsInteger();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }

    return ret;
}

double advJsonObject::getAsNumber(const string &key, bool checkType) {
    double ret = 0.0;
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        if (root[key]->IsNumber()) {
            ret = root[key]->AsNumber();
        } else if (root[key]->IsInteger()) {
            ret = root[key]->AsInteger();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }
    return ret;
}

bool advJsonObject::getAsBool(const string &key, bool checkType) {
    bool ret = false;
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        if (root[key]->IsBool()) {
            ret = root[key]->AsBool();
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }
    return ret;
}

advJsonArrayPtr advJsonObject::getAsArray(const string &key, bool checkType) {
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        if (root[key]->IsArray()) {
            advJsonArrayPtr pJsonArr(new advJsonArray(root[key]));
            return pJsonArr;
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }
    return NULL;
}

advJsonObjectPtr advJsonObject::getAsObject(const string &key, bool checkType) {
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end() && root[key]->IsObject()) {
        if (root[key]->IsObject()) {
            advJsonObjectPtr pJsonObj(new advJsonObject(root[key]));
            return pJsonObj;
        } else {
            if (checkType) {
                throw Exception("Unable to get JSON value for (%s), type mismatch", key.c_str());
            }
        }
    }
    return NULL;
}

advJsonElementPtr advJsonObject::getChild(const string &key) {
    JSONObject &root = jvPtr->AsObject();
    if (root.find(key) != root.end()) {
        advJsonElementPtr pJsonEle(new advJsonElement(root[key]));
        return pJsonEle;
    } else {
        return NULL;
    }
}

advJsonObject::advJsonObject(JVPtr jv) : advJsonElement(jv) {
}

bool advJsonObject::has(const string &key) {
    return jvPtr->HasChild(key.c_str());
}

bool advJsonObject::isChildArray(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsArray();
    }

    return false;
}

bool advJsonObject::isChildObject(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsObject();
    }

    return false;
}

bool advJsonObject::isChildNULL(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsNull();
    }

    return false;
}

bool advJsonObject::isChildNumber(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsNumber();
    }

    return false;
}

bool advJsonObject::isChildInteger(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsInteger();
    }

    return false;
}

bool advJsonObject::isChildBoolean(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsBool();
    }

    return false;
}

bool advJsonObject::isChildString(const string &key) {
    if (jvPtr->HasChild(key.c_str())) {
        JVPtr ch = jvPtr->Child(key.c_str());
        return ch->IsString();
    }

    return false;
}

TStrList advJsonObject::getAllKeys() {
    TStrList keys;
    keys = jvPtr->ObjectKeys();
    return keys;
}

TStrSet advJsonObject::getKeySet() {
    TStrSet keys;
    keys = jvPtr->ObjectKeySet();
    return keys;
}
