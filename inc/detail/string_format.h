/********************************************************
 * Description : string operator functions
 * Data        : 2014-12-02 10:05:11
 * Author      : yanrk
 * Email       : feeling_dxl@yeah.net & ken_scott@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * History     :
 * Copyright(C): 2013 - 2015
 ********************************************************/

#ifndef STUPID_LOGGER_STRING_FORMAT_H
#define STUPID_LOGGER_STRING_FORMAT_H


#include <cstdint>
#include <cstdarg>

extern size_t simple_vsnprintf(char * buffer, size_t bufsiz, const char * fmt, va_list args);
extern size_t simple_snprintf(char * buffer, size_t bufsiz, const char * fmt, ...);


#endif // STUPID_LOGGER_STRING_FORMAT_H
