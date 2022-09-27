/* 
 * File:   Exception.cpp
 * Author: sluo
 * 
 * Created on March 9, 2020, 4:46 PM
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

#include "Exception.h"
#include <stdarg.h>
#include "utils/utils.h"

#define BUFFER_SIZE 1024
#define ERROR_CODE_COMMON   100000

Exception::Exception(const std::string& msg) : _msg(msg), level(EXP_WARNING), _errcode(ERROR_CODE_COMMON) {
}

Exception::Exception(uint32_t errcode, const std::string& msg) : _msg(msg), level(EXP_WARNING), _errcode(errcode) {
}

Exception::Exception(TExpLevel expLevel, const std::string& msg) : _msg(msg), level(expLevel), _errcode(ERROR_CODE_COMMON) {
}

Exception::Exception(TExpLevel expLevel, uint32_t errcode, const std::string& msg) : _msg(msg), level(expLevel), _errcode(errcode) {
}

    
Exception::Exception(const char* fmt, ...) : level(EXP_WARNING), _errcode(ERROR_CODE_COMMON) {
    va_list varg;
    va_start(varg, fmt);
    char buf[BUFFER_SIZE];
    vsnprintf(buf, BUFFER_SIZE, fmt, varg);
    _msg.assign(buf);
    va_end(varg);
}

Exception::Exception(TExpLevel expLevel, const char* fmt, ...) : level(expLevel), _errcode(ERROR_CODE_COMMON)  {
    va_list varg;
    va_start(varg, fmt);
    char buf[BUFFER_SIZE];
    vsnprintf(buf, BUFFER_SIZE, fmt, varg);
    _msg.assign(buf);
    va_end(varg);
}

Exception::Exception(uint32_t errcode, const char* fmt, ...) : level(EXP_WARNING), _errcode(errcode)  {
    va_list varg;
    va_start(varg, fmt);
    char buf[BUFFER_SIZE];
    vsnprintf(buf, BUFFER_SIZE, fmt, varg);
    _msg.assign(buf);
    va_end(varg);
}

Exception::Exception(TExpLevel expLevel, uint32_t errcode, const char* fmt, ...) : level(expLevel), _errcode(errcode)  {
    va_list varg;
    va_start(varg, fmt);
    char buf[BUFFER_SIZE];
    vsnprintf(buf, BUFFER_SIZE, fmt, varg);
    _msg.assign(buf);
    va_end(varg);
}

string Exception::fullMsg() noexcept {
    string ret;
    ret.append(to_string(_errcode));
    ret.push_back(',');
    ret.append(_msg);
    return ret;
}
