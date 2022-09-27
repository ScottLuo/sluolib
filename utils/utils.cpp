/*
 * File:   utils.cpp
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

#include "utils.h"
#include <bits/stl_algo.h>
#include <unistd.h>
#include <ios>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <chrono>
#include <regex>
#include <atomic>
#include "Exception.h"


uint32_t utils::toInt(string str) {
    return atoi(str.c_str());
}

int64_t utils::toInt64(string str) {
    return atoll(str.c_str());
}

uint16_t utils::toHex(char byte) {
    uint16_t hex;
    char *ret = (char *)&hex;
    char const hex_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    ret[0] = hex_chars[ (byte & 0xF0) >> 4 ];
    ret[1] = hex_chars[ (byte & 0x0F) >> 0 ];
    return hex;
}

string utils::toHex(const char *buf, size_t length, bool withSpace) {
    string ret;
    ret.reserve(3 * length);
    for (size_t i = 0; i < length; i++) {
        if (i > 0 && withSpace) {
            ret.push_back(' ');
        }

        uint16_t hex = toHex(buf[i]);
        char *p = (char *) &hex;
        ret.push_back(p[0]);
        ret.push_back(p[1]);
    }
    return ret;
}

string utils::toHex(const string &data) {
    return toHex(data.c_str(), data.size());
}

string utils::toMix(const char *buf, size_t length) {
    string ret;
    ret.reserve(3 * length);
    for (size_t i = 0; i < length; i++) {
        if (isprint(buf[i])) {
            ret.push_back(buf[i]);
        } else {
            ret.push_back('<');
            uint16_t hex = toHex(buf[i]);
            char *p = (char *) &hex;
            ret.push_back(p[0]);
            ret.push_back(p[1]);
            ret.push_back('>');
        }
    }
    return ret;
}

string utils::readFile(const char *path) {
    FILE * pFile = NULL;
    long lSize = 0;
    char * buffer = NULL;
    size_t result = 0;
    string res = "";

    pFile = fopen(path, "rb");
    if (pFile == NULL) {
        throw Exception("Error:Can not open file(%s)", path);
    }

    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc(sizeof (char) * lSize);
    if (buffer == NULL) {
        fclose(pFile);
        throw Exception("Error:Memory request fail");
    }

    // copy the file into the buffer:
    result = fread(buffer, 1, lSize, pFile);
    if (result != (size_t) lSize) {
        throw Exception("Error:Can not read the file(%s)", path);
    } else {
        res.assign(buffer, lSize);
    }

    fclose(pFile);
    free(buffer);
    buffer = NULL;
    return res;
}

//Mon, 10 Jan 2020 12:30:21 GMT
time_t utils::timeParse(const char *str) {
    struct tm datetime;
    char dn[10], mn[10], ln[10];
    int d, h, m, s, y;
    sscanf(str, "%s %d %s %d %d:%d:%d %s", dn, &d, mn, &y, &h, &m, &s, ln);

    datetime.tm_sec = s;
    datetime.tm_min = m;
    datetime.tm_hour = h;
    datetime.tm_mday = d;
    if (!strcmp(mn, "JAN")) datetime.tm_mon = 0;
    if (!strcmp(mn, "FEB")) datetime.tm_mon = 1;
    if (!strcmp(mn, "MAR")) datetime.tm_mon = 2;
    if (!strcmp(mn, "APR")) datetime.tm_mon = 3;
    if (!strcmp(mn, "MAY")) datetime.tm_mon = 4;
    if (!strcmp(mn, "JUN")) datetime.tm_mon = 5;
    if (!strcmp(mn, "JUL")) datetime.tm_mon = 6;
    if (!strcmp(mn, "AUG")) datetime.tm_mon = 7;
    if (!strcmp(mn, "SEP")) datetime.tm_mon = 8;
    if (!strcmp(mn, "OCT")) datetime.tm_mon = 9;
    if (!strcmp(mn, "NOV")) datetime.tm_mon = 10;
    if (!strcmp(mn, "DEC")) datetime.tm_mon = 11;
    datetime.tm_year = y - 1900;
    time_t t = timegm(&datetime);
    return t;
}

time_t utils::stdTimeParse(const char *str) {
    struct tm datetime;
    int year, mon, day, hour, min, sec;
    sscanf(str, "%d-%d-%d %d:%d:%d", &year, &mon, &day,&hour, &min, &sec);

    datetime.tm_sec = sec;
    datetime.tm_min = min;
    datetime.tm_hour = hour;
    datetime.tm_mday = day;
    datetime.tm_mon = mon - 1;
    datetime.tm_year = year - 1900;
    time_t t = timegm(&datetime);
    return t;
}

string utils::stdDateTime(time_t rawtime, const char * fmt) {
    struct tm * timeinfo;
    char buffer [80];

    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, fmt, timeinfo);
    string ret(buffer);

    return ret;
}

string utils::stdDateTimeNow(const char * fmt) {
    return stdDateTime(time(0), fmt);
}

string utils::gmtDateTime(time_t rawtime, const char * fmt) {
    struct tm * timeinfo;
    char buffer [80];

    timeinfo = gmtime(&rawtime);

    strftime(buffer, 80, fmt, timeinfo);
    string ret(buffer);

    return ret;
}

uint64_t utils::timeStampNow() {
    using namespace std::chrono;
    microseconds ms = duration_cast< microseconds >(
        system_clock::now().time_since_epoch());
    return ms.count();
};


const uint32_t crc32_tab[256] =
{
0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

uint32_t utils::crc32(const void *buf, size_t size)
{
   const uint8_t *p = (uint8_t *)buf;
   uint32_t crc;

   crc = ~0U;
   while (size--)
      crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
   return crc ^ ~0U;
}

        
uint32_t utils::crc32(const string &data) {
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < data.size(); i++) {
        char ch = data[i];
        for (size_t j = 0; j < 8; j++) {
            uint32_t b = (ch^crc)&1;
            crc >>= 1;
            if (b) crc = crc^0xEDB88320;
            ch >>= 1;
        }
    }

    return ~crc;
}

bool utils::validate_ip_address(const string& s) {
    uint32_t bytes[4] = {0};
    if (4 == sscanf(s.c_str(), "%d.%d.%d.%d"
        , &bytes[3]
        , &bytes[2]
        , &bytes[1]
        , &bytes[0])) {
        for (auto i = 0; i < 4; i++) {
            if (bytes[i] > 255) {
                return false;
            }
        }

        return true;
    } else {
        return false;
    }
}

bool utils::validate_domain(const string& s) {
    const regex pattern("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");

    // If the domain name
    // is empty return false
    if (s.empty()) {
        return false;
    } else if (s == "localhost") {
        return true;
    }

    // Return true if the domain name
    // matched the ReGex
    if (regex_match(s, pattern)) {
        return true;
    } else {
        return false;
    }
}

bool utils::validate_mac_address(const string& s) {
    if (s.size() != 17) return false;
    uint32_t bytes[6] = {0};
    return (6 == sscanf(s.c_str(), "%02X:%02X:%02X:%02X:%02X:%02X"
        , &bytes[5]
        , &bytes[4]
        , &bytes[3]
        , &bytes[2]
        , &bytes[1]
        , &bytes[0]));
}

bool utils::validate_timestamp(const string& s) {
    if (s.size() != 19) return false;
    uint32_t bytes[6] = {0};
    if (6 == sscanf(s.c_str(), "%04d-%02d-%02d %02d:%02d:%02d"
        , &bytes[5]
        , &bytes[4]
        , &bytes[3]
        , &bytes[2]
        , &bytes[1]
        , &bytes[0])) {
        //year
        if (bytes[5] < 2021) {
            return false;
        }

        //month and day
        if (bytes[4] == 1 || bytes[4] == 3 || bytes[4] == 5 || bytes[4] == 7 || bytes[4] == 8 || bytes[4] == 10 || bytes[4] == 12) {
            if (bytes[3] - 1 > 30) {
                return false;
            }
        } else if (bytes[4] == 4 || bytes[4] == 6 || bytes[4] == 9 || bytes[4] == 11) {
            if (bytes[3] - 1 > 29) {
                return false;
            }
        } else if (bytes[4] == 2) {
            if (bytes[3] - 1 > 28) {
                return false;
            }
        } else {
            return false;
        }

        //hour
        if (bytes[2] > 24) {
            return false;
        }

        //minute
        if (bytes[1] > 60) {
            return false;
        }

        //second
        if (bytes[0] > 60) {
            return false;
        }

        return true;
    } else {
        return false;
    }
}

int64_t utils::new_id() {
    static atomic<int64_t> id(0);
    return id++;
}

bool utils::is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool utils::is_hex(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isxdigit(c); }) == s.end();
}

bool utils::check_string(const string &str, const string &char_set) {
    for (auto x : str) {
        if (char_set.find(x) == string::npos) {
            return false;
        }
    }
    
    return true;
}

string utils::timezone() {
    std::time_t t = std::time(nullptr);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%Z", std::localtime(&t))) {
        string ret(mbstr);
        return ret;
    } else {
        return "UNKNOWN";
    }
}

string utils::host_name() {
    char hostname[100];
    gethostname(hostname, 100);
    return string(hostname);
}