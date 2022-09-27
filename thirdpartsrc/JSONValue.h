/*
 * File JSONValue.h part of the SimpleJSON Library - http://mjpa.in/json
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

#ifndef _JSONVALUE_H_
#define _JSONVALUE_H_

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <set>

enum JSONType {
    JSONType_Null, JSONType_String, JSONType_Bool, JSONType_Integer, JSONType_Float, JSONType_Array, JSONType_Object
};

class JSONValue;

typedef std::shared_ptr<JSONValue> JVPtr;
typedef std::vector<JVPtr> JSONArray;
typedef std::map<std::string, JVPtr> JSONObject;
typedef std::set<std::string> TStrSet;

class JSONValue {
public:
    JSONValue(/*NULL*/);
    JSONValue(const char *m_char_value);
    JSONValue(const std::string &m_string_value);
    JSONValue(bool m_bool_value);
    JSONValue(double m_number_value);
    JSONValue(int64_t m_integer_value);
//    JSONValue(const JSONArray &m_array_value);
//    JSONValue(const JSONObject &m_object_value);
//    JSONValue(const JSONValue &m_source);
    JSONValue(int jvtype, int whatever);
    ~JSONValue();

    void setToNull();
    void setToString(const char *m_char_value);
    void setToString(const std::string &m_string_value);
    void setToBoolean(bool m_bool_value);
    void setToFloat(double m_number_value);
    void setToInteger(int64_t m_integer_value);
    void setToType(int jvtype);
    
    bool IsNull() const;
    bool IsString() const;
    bool IsBool() const;
    bool IsNumber() const;
    bool IsInteger() const;
    bool IsArray() const;
    bool IsObject() const;

    const std::string &AsString() const;
    bool AsBool() const;
    double AsNumber() const;
    int64_t AsInteger() const;
    JSONArray &AsArray() const;
    JSONObject &AsObject() const;

    std::size_t CountChildren() const;
    bool HasChild(std::size_t index) const;
    JVPtr Child(std::size_t index);
    bool HasChild(const char* name) const;
    JVPtr Child(const char* name);
    std::vector<std::string> ObjectKeys() const;
    TStrSet ObjectKeySet() const;

    std::string Stringify(bool const prettyprint = false) const;
    
    void clear();
    JSONType getType() {
        return type;
    }
protected:
    void reset();
    static JSONValue *Parse(const char **data);

private:
    static std::string StringifyString(const std::string &str, bool rawstring);
    std::string StringifyImpl(size_t const indentDepth, bool rawstring) const;
    
    static std::string Indent(size_t depth);

    JSONType type;

    union {
        bool bool_value;
        double number_value;
        int64_t int_value;
        std::string *string_value;
        JSONArray *array_value;
        JSONObject *object_value;
    };

};

#endif
