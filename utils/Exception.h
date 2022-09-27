/* 
 * File:   Exception.h
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

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <string>

using namespace std;

class Exception : public std::exception {
public:
    typedef enum {
        EXP_EMERG,  // System level, exception will cause the system unusable
        EXP_CRIT,   // App level, exception will cause the current app unusable
        EXP_WARNING // Session level, exception will casue session close.
    }TExpLevel;

    Exception(const std::string& msg);
    Exception(uint32_t errcode, const std::string& msg);
    Exception(TExpLevel expLevel, const std::string& msg);
    Exception(TExpLevel expLevel, uint32_t errcode, const std::string& msg);

    Exception(const char* fmt, ...);
    Exception(uint32_t errcode, const char* fmt, ...);
    Exception(TExpLevel expLevel, const char* fmt, ...);
    Exception(TExpLevel expLevel, uint32_t errcode, const char* fmt, ...);    

    virtual const char* what() const noexcept override {
        return _msg.c_str();
    }
    
    virtual string &str() noexcept {
        return _msg;
    }
    
    virtual string fullMsg() noexcept;

    inline TExpLevel getExpLevel() {
        return level;
    }
    
    inline uint32_t getErrorCode() {
        return _errcode;
    }
protected:
    std::string _msg;
    TExpLevel level;
    uint32_t _errcode;
};

#endif	/* EXCEPTION_H */

