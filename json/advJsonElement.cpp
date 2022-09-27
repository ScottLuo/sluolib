/*
 * File:   advJsonElement.cpp
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

#include "advJsonElement.h"
#include "advJsonObject.h"
#include "advJsonArray.h"
#include "advJsonParser.h"
#include "utils/Exception.h"

advJsonElement::advJsonElement(JVPtr jv) {
    jvPtr = jv;
}

advJsonElement::advJsonElement(const string &jsonStr) {
    advJsonParser jp;
    advJsonElementPtr jroot = jp.parse(jsonStr);
    if (jp.good()) {
        jvPtr = jroot->jvPtr;
    } else {
        throw Exception("JSON Parse fail");
    }
}


string advJsonElement::toText(bool pretty) {
        return jvPtr->Stringify(pretty);
}

bool advJsonElement::isNULL() {
    return jvPtr->IsNull();
}

bool advJsonElement::isArray() {
    return jvPtr->IsArray();
}

bool advJsonElement::isObject() {
    return jvPtr->IsObject();
}

bool advJsonElement::isNumber() {
    return jvPtr->IsNumber();
}

bool advJsonElement::isInteger() {
    return jvPtr->IsInteger();
}

bool advJsonElement::isBoolean() {
    return jvPtr->IsBool();
}

bool advJsonElement::isString() {
    return jvPtr->IsString();
}


advJsonObjectPtr advJsonElement::toObject() {
    advJsonObjectPtr jobj(new advJsonObject(jvPtr));
    return jobj;
}

advJsonArrayPtr advJsonElement::toArray() {
    advJsonArrayPtr jarr(new advJsonArray(jvPtr));
    return jarr;
}

void advJsonElement::swap(advJsonElementPtr jelement) {
    if (jvPtr->getType() == jelement->jvPtr->getType()) {
        JVPtr jv;
        jv = this->jvPtr;
        this->jvPtr = jelement->jvPtr;
        jelement->jvPtr = jv;
    } else {
        throw Exception("unable to swap different type JSON");
    }
}

string advJsonElement::convert2XML(const string &rootTag) {
   string xml;
   string xmlTag("<" + rootTag +">");
   string xmlEndTag("</" + rootTag +">");
   
   xml.append(xmlTag);
   switch (jvPtr->getType()) {
   case JSONType_Null:
      break;
   case JSONType_String:
      xml.append(jvPtr->AsString());
      break;
   case JSONType_Bool:
      if (jvPtr->AsBool()) {
         xml.append("True");
      } else {
         xml.append("False");
      }
      break;
   case JSONType_Integer:
      xml.append(std::to_string(jvPtr->AsInteger()));
      break;
   case JSONType_Float:
      xml.append(std::to_string(jvPtr->AsNumber()));
      break;
   case JSONType_Array:
   {
      advJsonArrayPtr arr = toArray();
      for (size_t i = 0; i < arr->size(); i++) {
         xml.append(arr->getChild(i)->convert2XML(rootTag + "Element"));
      }
      break;
   }
   case JSONType_Object:
   {
      advJsonObjectPtr obj = toObject();
      TStrList keys = obj->getAllKeys();
      for (size_t i = 0; i < keys.size(); i++) {
         xml.append(obj->getChild(keys[i])->convert2XML(keys[i]));
      }
      break;
   }
   default:
      break;
   };
   xml.append(xmlEndTag);
   return xml;
}
