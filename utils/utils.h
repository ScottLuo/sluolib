/* 
 * File:   utils.h
 * Author: sluo
 *
 * Created on March 23, 2020, 12:08 PM
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

#ifndef UTILS_H
#define	UTILS_H

#include <string>
#include <clocale>
#include <ctime>
#include <vector>
#include <map>
#include <condition_variable>
#include <mutex>

using namespace std;

typedef vector<string> TStringList;
typedef map<string, string> TParams;

class utils {
public:
    static uint32_t toInt(string str);
    static int64_t toInt64(string str);
    
    static uint16_t toHex(char byte);
    static string toHex(const char *buf, size_t length, bool withSpace = true);
    static string toHex(const string &data);
    static string toMix(const char *buf, size_t length);
    static string readFile(const char *path);
    static time_t timeParse(const char *str);
    static time_t stdTimeParse(const char *str);
    static string stdDateTime(time_t rawtime, const char * fmt = "%Y-%m-%d %H:%M:%S");
    static string stdDateTimeNow(const char * fmt = "%Y-%m-%d %H:%M:%S");
    static string gmtDateTime(time_t rawtime, const char * fmt = "%Y-%m-%d %H:%M:%S");
    static uint64_t timeStampNow();
    static string timezone();

    static uint32_t crc32(const void *buf, size_t size);
    static uint32_t crc32(const string &data);
    
    static bool validate_ip_address(const string& s);
    static bool validate_domain(const string& s);
    static bool validate_mac_address(const string& s);
    static bool validate_timestamp(const string& s);
    
    static int64_t new_id();
    
    static bool is_number(const std::string& s);
    static bool is_hex(const std::string& s);
    static bool check_string(const string &str, const string &char_set);
    static string host_name();
private:

};

class Semaphore {
public:
    Semaphore (int count_ = 0)
    : count(count_) 
    {
    }
    
    inline void notify() {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            //wait on the mutex until notify is called
            cv.wait(lock);
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

#endif	/* UTILS_H */

