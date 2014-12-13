/********************************************************
 * Description : time function
 * Data        : 2014-12-01 17:07:22
 * Author      : yanrk
 * Email       : feeling_dxl@yeah.net & ken_scott@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * History     :
 * Copyright(C): 2013 - 2015
 ********************************************************/

#ifndef STUPID_LOGGER_SYSTEM_TIME_H
#define STUPID_LOGGER_SYSTEM_TIME_H


#ifdef _MSC_VER
    #include <windows.h>
#else
    #include <sys/time.h>
    #include <unistd.h>
    #include <errno.h>
#endif // _MSC_VER

#include <ctime>
#include <cstdint>

extern int64_t simple_get_time();
extern struct tm simple_get_localtime();
extern struct tm simple_get_gmtime();
extern struct timeval simple_gettimeofday();
extern int simple_get_timezone();
extern int simple_get_day_of_week();


#endif // STUPID_LOGGER_SYSTEM_TIME_H
