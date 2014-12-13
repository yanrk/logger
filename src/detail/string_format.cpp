/********************************************************
 * Description : string operator functions
 * Data        : 2014-12-02 10:05:11
 * Author      : yanrk
 * Email       : yanrkchina@hotmail.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2013 - 2015
 ********************************************************/

#include <cstdio>
#include <cstring>
#include "detail/string_format.h"

size_t simple_vsnprintf(char * buffer, size_t bufsiz, const char * fmt, va_list args)
{
    if (nullptr == buffer || 0 == bufsiz || nullptr == fmt || nullptr == args)
    {
        return(0);
    }

#ifdef _MSC_VER
    size_t ret_siz = _vsnprintf(buffer, bufsiz, fmt, args);
#else
    size_t ret_siz = vsnprintf(buffer, bufsiz, fmt, args);
#endif // _MSC_VER

    if (bufsiz <= ret_siz)
    {
        ret_siz = bufsiz - 1;
        buffer[ret_siz] = '\0';
    }

    return(ret_siz);
}

size_t simple_snprintf(char * buffer, size_t bufsiz, const char * fmt, ...)
{
    if (nullptr == fmt)
    {
        return(0);
    }

    va_list args = nullptr;

    va_start(args, fmt);

    size_t ret_siz = simple_vsnprintf(buffer, bufsiz, fmt, args);

    va_end(args);

    return(ret_siz);
}
