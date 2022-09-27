/*
 * File JSONValue.cpp part of the SimpleJSON Library - http://mjpa.in/json
 *
 * Copyright (C) 2010 Mike Anchor
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

#include "JSONValue.h"

#ifdef __MINGW32__
#define wcsncasecmp wcsncmp
#endif
using namespace std;

// Macros to free an array/object
#define FREE_ARRAY(x) { JSONArray::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { *iter = NULL; } }
#define FREE_OBJECT(x) { JSONObject::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { (*iter).second = NULL; } }

/**
 * Basic constructor for creating a JSON Value of type NULL
 *
 * @access public
 */
JSONValue::JSONValue(/*NULL*/) {
    type = JSONType_Null;
}

/**
 * Basic constructor for creating a JSON Value of type String
 *
 * @access public
 *
 * @param char* m_char_value The string to use as the value
 */
JSONValue::JSONValue(const char *m_char_value) {
    type = JSONType_String;
    string_value = new std::string(m_char_value);
}

/**
 * Basic constructor for creating a JSON Value of type String
 *
 * @access public
 *
 * @param std::string m_string_value The string to use as the value
 */
JSONValue::JSONValue(const std::string &m_string_value) {
    type = JSONType_String;
    string_value = new std::string(m_string_value);
}

/**
 * Basic constructor for creating a JSON Value of type Bool
 *
 * @access public
 *
 * @param bool m_bool_value The bool to use as the value
 */
JSONValue::JSONValue(bool m_bool_value) {
    type = JSONType_Bool;
    bool_value = m_bool_value;
}

/**
 * Basic constructor for creating a JSON Value of type Number
 *
 * @access public
 *
 * @param double m_number_value The number to use as the value
 */
JSONValue::JSONValue(double m_number_value) {
    type = JSONType_Float;
    number_value = m_number_value;
}

/**
 * Basic constructor for creating a JSON Value of type Number
 *
 * @access public
 *
 * @param int m_integer_value The number to use as the value
 */
JSONValue::JSONValue(int64_t m_integer_value) {
    type = JSONType_Integer;
    int_value = m_integer_value;
}

/**
 * Basic constructor for creating a JSON Value of type Array
 *
 * @access public
 *
 * @param JSONArray m_array_value The JSONArray to use as the value
 */
//JSONValue::JSONValue(const JSONArray &m_array_value)
//{
//	type = JSONType_Array;
//	array_value = new JSONArray(m_array_value);
//}

/**
 * Basic constructor for creating a JSON Value of type Object
 *
 * @access public
 *
 * @param JSONObject m_object_value The JSONObject to use as the value
 */
//JSONValue::JSONValue(const JSONObject &m_object_value)
//{
//	type = JSONType_Object;
//	object_value = new JSONObject(m_object_value);
//}

JSONValue::JSONValue(int jvtype, int whatever) {
    switch (jvtype) {
        case JSONType_String:
        {
            type = JSONType_String;
            string_value = new std::string();
            break;
        }
        case JSONType_Bool:
        {
            type = JSONType_Bool;
            bool_value = false;
            break;
        }
        case JSONType_Integer:
        {
            type = JSONType_Integer;
            int_value = 0;
            break;
        }
        case JSONType_Float:
        {
            type = JSONType_Float;
            number_value = 0.0;
            break;
        }
        case JSONType_Array:
        {
            type = JSONType_Array;
            array_value = new JSONArray();
            break;
        }
        case JSONType_Object:
        {
            type = JSONType_Object;
            object_value = new JSONObject();
            break;
        }
        case JSONType_Null:
        default:
        {
            type = JSONType_Null;
            break;
        }
    }
}

void JSONValue::setToNull() {
    reset();
}

void JSONValue::setToString(const char *m_char_value) {
    if (type == JSONType_String) {
        string_value->assign(m_char_value);
    } else {
        reset();
        type = JSONType_String;
        string_value = new std::string(m_char_value);
    }
}

void JSONValue::setToString(const std::string &m_string_value) {
    if (type == JSONType_String) {
        string_value->assign(m_string_value);
    } else {
        reset();
        type = JSONType_String;
        string_value = new std::string(m_string_value);
    }
}

void JSONValue::setToBoolean(bool m_bool_value) {
    switch (type) {
        case JSONType_Array:
        case JSONType_Object:
        case JSONType_String:
            reset();
            // fall through
        default:
            type = JSONType_Bool;
            bool_value = m_bool_value;
    }
}

void JSONValue::setToFloat(double m_number_value) {
    switch (type) {
        case JSONType_Array:
        case JSONType_Object:
        case JSONType_String:
            reset();
            // fall through
        default:
            type = JSONType_Float;
            number_value = m_number_value;
    }
}

void JSONValue::setToInteger(int64_t m_integer_value) {
    switch (type) {
        case JSONType_Array:
        case JSONType_Object:
        case JSONType_String:
            reset();
            // fall through
        default:
            type = JSONType_Integer;
            int_value = m_integer_value;
    }
}

void JSONValue::setToType(int jvtype) {
    switch (jvtype) {
        case JSONType_String:
        {
            setToString("");
            break;
        }
        case JSONType_Bool:
        {
            setToBoolean(false);
            break;
        }
        case JSONType_Integer:
        {
            setToInteger(0);
            break;
        }
        case JSONType_Float:
        {
            setToFloat(0.0);
            break;
        }
        case JSONType_Array:
        {
            if (type != JSONType_Array) {
                reset();
                type = JSONType_Array;
                array_value = new JSONArray();
            }
            break;
        }
        case JSONType_Object:
        {
            if (type != JSONType_Object) {
                reset();
                type = JSONType_Object;
                object_value = new JSONObject();
            }
            break;
        }
        case JSONType_Null:
        default:
        {
            reset();
            type = JSONType_Null;
            break;
        }
    }
}

/**
 * The destructor for the JSON Value object
 * Handles deleting the objects in the array or the object value
 *
 * @access public
 */
JSONValue::~JSONValue() {
    if (type == JSONType_Array) {
        JSONArray::iterator iter;
        for (iter = array_value->begin(); iter != array_value->end(); iter++)
            *iter = NULL;
        delete array_value;
    } else if (type == JSONType_Object) {
        JSONObject::iterator iter;
        for (iter = object_value->begin(); iter != object_value->end(); iter++) {
            (*iter).second = NULL;
        }
        delete object_value;
    } else if (type == JSONType_String) {
        delete string_value;
    }
}

/**
 * Checks if the value is a NULL
 *
 * @access public
 *
 * @return bool Returns true if it is a NULL value, false otherwise
 */
bool JSONValue::IsNull() const {
    return type == JSONType_Null;
}

/**
 * Checks if the value is a String
 *
 * @access public
 *
 * @return bool Returns true if it is a String value, false otherwise
 */
bool JSONValue::IsString() const {
    return type == JSONType_String;
}

/**
 * Checks if the value is a Bool
 *
 * @access public
 *
 * @return bool Returns true if it is a Bool value, false otherwise
 */
bool JSONValue::IsBool() const {
    return type == JSONType_Bool;
}

/**
 * Checks if the value is a Number
 *
 * @access public
 *
 * @return bool Returns true if it is a Number value, false otherwise
 */
bool JSONValue::IsNumber() const {
    return type == JSONType_Float;
}

bool JSONValue::IsInteger() const {
    return type == JSONType_Integer;
}

/**
 * Checks if the value is an Array
 *
 * @access public
 *
 * @return bool Returns true if it is an Array value, false otherwise
 */
bool JSONValue::IsArray() const {
    return type == JSONType_Array;
}

/**
 * Checks if the value is an Object
 *
 * @access public
 *
 * @return bool Returns true if it is an Object value, false otherwise
 */
bool JSONValue::IsObject() const {
    return type == JSONType_Object;
}

/**
 * Retrieves the String value of this JSONValue
 * Use IsString() before using this method.
 *
 * @access public
 *
 * @return std::string Returns the string value
 */
const std::string & JSONValue::AsString() const {
    return (*string_value);
}

/**
 * Retrieves the Bool value of this JSONValue
 * Use IsBool() before using this method.
 *
 * @access public
 *
 * @return bool Returns the bool value
 */
bool JSONValue::AsBool() const {
    return bool_value;
}

/**
 * Retrieves the Number value of this JSONValue
 * Use IsNumber() before using this method.
 *
 * @access public
 *
 * @return double Returns the number value
 */
double JSONValue::AsNumber() const {
    return number_value;
}

int64_t JSONValue::AsInteger() const {
    return int_value;
}

/**
 * Retrieves the Array value of this JSONValue
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return JSONArray Returns the array value
 */
JSONArray & JSONValue::AsArray() const {
    return (*array_value);
}

/**
 * Retrieves the Object value of this JSONValue
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return JSONObject Returns the object value
 */
JSONObject & JSONValue::AsObject() const {
    return (*object_value);
}

/**
 * Retrieves the number of children of this JSONValue.
 * This number will be 0 or the actual number of children
 * if IsArray() or IsObject().
 *
 * @access public
 *
 * @return The number of children.
 */
std::size_t JSONValue::CountChildren() const {
    switch (type) {
        case JSONType_Array:
            return array_value->size();
        case JSONType_Object:
            return object_value->size();
        default:
            return 0;
    }
}

/**
 * Checks if this JSONValue has a child at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the array has a value at the given index.
 */
bool JSONValue::HasChild(std::size_t index) const {
    if (type == JSONType_Array) {
        return index < array_value->size();
    } else {
        return false;
    }
}

/**
 * Retrieves the child of this JSONValue at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return JSONValue* Returns JSONValue at the given index or NULL
 *                    if it doesn't exist.
 */
JVPtr JSONValue::Child(std::size_t index) {
    if (index < array_value->size()) {
        return (*array_value)[index];
    } else {
        return NULL;
    }
}

/**
 * Checks if this JSONValue has a child at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the object has a value at the given key.
 */
bool JSONValue::HasChild(const char* name) const {
    if (type == JSONType_Object) {
        return object_value->find(name) != object_value->end();
    } else {
        return false;
    }
}

/**
 * Retrieves the child of this JSONValue at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return JSONValue* Returns JSONValue for the given key in the object
 *                    or NULL if it doesn't exist.
 */
JVPtr JSONValue::Child(const char* name) {
    JSONObject::const_iterator it = object_value->find(name);
    if (it != object_value->end()) {
        return it->second;
    } else {
        return NULL;
    }
}

/**
 * Retrieves the keys of the JSON Object or an empty vector
 * if this value is not an object.
 *
 * @access public
 *
 * @return std::vector<std::string> A vector containing the keys.
 */
std::vector<std::string> JSONValue::ObjectKeys() const {
    std::vector<std::string> keys;

    if (type == JSONType_Object) {
        JSONObject::const_iterator iter = object_value->begin();
        while (iter != object_value->end()) {
            keys.push_back(iter->first);
            iter++;
        }
    }

    return keys;
}

TStrSet JSONValue::ObjectKeySet() const {
    TStrSet keys;
    if (type == JSONType_Object) {
        JSONObject::const_iterator iter = object_value->begin();
        while (iter != object_value->end()) {
            keys.insert(iter->first);
            iter++;
        }
    }

    return keys;
}

/**
 * Creates a JSON encoded string for the value with all necessary characters escaped
 *
 * @access public
 *
 * @param bool prettyprint Enable prettyprint
 *
 * @return std::string Returns the JSON string
 */
std::string JSONValue::Stringify(bool const prettyprint) const {
    size_t const indentDepth = prettyprint ? 1 : 0;
    return StringifyImpl(indentDepth, false);
}

/**
 * Creates a JSON encoded string for the value with all necessary characters escaped
 *
 * @access private
 *
 * @param size_t indentDepth The prettyprint indentation depth (0 : no prettyprint)
 *
 * @return std::string Returns the JSON string
 */
std::string JSONValue::StringifyImpl(size_t const indentDepth, bool rawstring) const {
    std::string ret_string;
    size_t const indentDepth1 = indentDepth ? indentDepth + 1 : 0;
    std::string const indentStr = Indent(indentDepth);
    std::string const indentStr1 = Indent(indentDepth1);

    switch (type) {
        case JSONType_Null:
            ret_string = "null";
            break;

        case JSONType_String:
            ret_string = StringifyString(*string_value, rawstring);
            break;

        case JSONType_Bool:
            ret_string = bool_value ? "true" : "false";
            break;

        case JSONType_Float:
        {
            if (isinf(number_value) || isnan(number_value))
                ret_string = "null";
            else {
                std::stringstream ss;
                ss.precision(15);
                ss << number_value;
                ret_string = ss.str();
            }
            break;
        }
        case JSONType_Integer:
        {
            std::stringstream ss;
            ss.precision(15);
            ss << int_value;
            ret_string = ss.str();
            break;
        }

        case JSONType_Array:
        {
            ret_string = indentDepth ? "[\n" + indentStr1 : "[";
            JSONArray::const_iterator iter = array_value->begin();
            while (iter != array_value->end()) {
                ret_string += (*iter)->StringifyImpl(indentDepth1, rawstring);

                // Not at the end - add a separator
                if (++iter != array_value->end())
                    ret_string += ",\n" + indentStr1;
            }
            ret_string += indentDepth ? "\n" + indentStr + "]" : "]";
            break;
        }

        case JSONType_Object:
        {
            ret_string = indentDepth ? "{\n" + indentStr1 : "{";
            JSONObject::const_iterator iter = object_value->begin();
            while (iter != object_value->end()) {
                ret_string += StringifyString((*iter).first, rawstring);
                ret_string += ":";
                ret_string += (*iter).second->StringifyImpl(indentDepth1, rawstring);

                // Not at the end - add a separator
                if (++iter != object_value->end())
                    ret_string += ",\n" + indentStr1;
            }
            ret_string += indentDepth ? "\n" + indentStr + "}" : "}";
            break;
        }
    }
    return ret_string;
}

/**
 * Creates a JSON encoded string with all required fields escaped
 * Works from http://www.ecma-internationl.org/publications/files/ECMA-ST/ECMA-262.pdf
 * Section 15.12.3.
 *
 * @access private
 *
 * @param std::string str The string that needs to have the characters escaped
 *
 * @return std::string Returns the JSON string
 */
std::string JSONValue::StringifyString(const std::string &str, bool rawstring) {
    std::string str_out = "\"";

    std::string::const_iterator iter = str.begin();
    while (iter != str.end()) {
        char chr = *iter;

        if (chr == '"' || chr == '\\' || chr == '/') {
            str_out += '\\';
            str_out += chr;
        } else if (chr == '\b') {
            str_out += "\\b";
        } else if (chr == '\f') {
            str_out += "\\f";
        } else if (chr == '\n') {
            str_out += "\\n";
        } else if (chr == '\r') {
            str_out += "\\r";
        } else if (chr == '\t') {
            str_out += "\\t";
        } else if (!rawstring && (chr < ' ' || chr > 126)) {
            str_out += "\\u";
            for (int i = 0; i < 4; i++) {
                int value = (chr >> 12) & 0xf;
                if (value >= 0 && value <= 9)
                    str_out += (char) ('0' + value);
                else if (value >= 10 && value <= 15)
                    str_out += (char) ('A' + (value - 10));
                chr <<= 4;
            }
        } else {
            str_out += chr;
        }

        iter++;
    }

    str_out += "\"";
    return str_out;
}

/**
 * Creates the indentation string for the depth given
 *
 * @access private
 *
 * @param size_t indent The prettyprint indentation depth (0 : no indentation)
 *
 * @return std::string Returns the string
 */
std::string JSONValue::Indent(size_t depth) {
    const size_t indent_step = 2;
    depth ? --depth : 0;
    std::string indentStr(depth * indent_step, ' ');
    return indentStr;
}

void JSONValue::clear() {
    switch (type) {
        case JSONType_String:
        {
            string_value->clear();
            break;
        }
        case JSONType_Bool:
        {
            type = JSONType_Null;
            int_value = 0;
            break;
        }
        case JSONType_Integer:
        {
            type = JSONType_Null;
            int_value = 0;
            break;
        }
        case JSONType_Float:
        {
            type = JSONType_Null;
            int_value = 0;
            break;
        }
        case JSONType_Array:
        {
            array_value->clear();
            break;
        }
        case JSONType_Object:
        {
            object_value->clear();
            break;
        }
        case JSONType_Null:
        default:
        {
            type = JSONType_Null;
            break;
        }
    }
}

void JSONValue::reset() {
    if (type == JSONType_Object) {
        delete object_value;
        object_value = NULL;
    } else if (type == JSONType_Array) {
        delete array_value;
        array_value = NULL;
    } else if (type == JSONType_String) {
        delete string_value;
        string_value = NULL;
    } else {
        clear();
    }
    type = JSONType_Null;
}
