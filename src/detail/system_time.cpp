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

#include "detail/system_time.h"

int64_t simple_get_time()
{
    return(static_cast<int64_t>(time(nullptr)));
}

struct tm simple_get_localtime()
{
    time_t time_now = time(nullptr);
    struct tm tm_now;

#ifdef _MSC_VER
    localtime_s(&tm_now, &time_now);
#else
    localtime_r(&time_now, &tm_now);
#endif // _MSC_VER

    return(tm_now);
}

struct tm simple_get_gmtime()
{
    time_t time_now = time(nullptr);
    struct tm tm_now;

#ifdef _MSC_VER
    gmtime_s(&tm_now, &time_now);
#else
    gmtime_r(&time_now, &tm_now);
#endif // _MSC_VER

    return(tm_now);
}

struct timeval simple_gettimeofday()
{
    struct timeval tv_now;

#ifdef _MSC_VER
    SYSTEMTIME sys_now;
    GetLocalTime(&sys_now);
    tv_now.tv_sec = static_cast<long>(time(nullptr));
    tv_now.tv_usec = sys_now.wMilliseconds * 1000L;
#else
    gettimeofday(&tv_now, nullptr);
#endif // _MSC_VER

    return(tv_now);
}

int simple_get_timezone()
{
    static long time_diff = 0;
    static bool first_time = true;

    if (first_time)
    {
#ifdef _MSC_VER
        _get_timezone(&time_diff);
#else
        time_diff = timezone;
#endif // _MSC_VER

        time_diff /= -3600;

        first_time = false;
    }

    return(time_diff);
}

int simple_get_day_of_week()
{
    struct tm tm_now = simple_get_localtime();
    return(tm_now.tm_wday);
}
