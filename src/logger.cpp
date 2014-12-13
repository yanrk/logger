/********************************************************
 * Description : logger helper
 * Data        : 2014-12-04 09:03:24
 * Author      : yanrk
 * Email       : feeling_dxl@yeah.net & ken_scott@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * History     :
 * Copyright(C): 2013 - 2015
 ********************************************************/

#ifdef _MSC_VER
    #include <windows.h>
#else
    #include <pthread.h>
#endif // _MSC_VER

#include <cstring>
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "detail/system_time.h"
#include "detail/hex_convert.h"
#include "detail/string_format.h"
#include "logger.h"

static size_t current_thread_id()
{
#ifdef _MSC_VER
    return(static_cast<size_t>(GetCurrentThreadId()));
#else
    return(static_cast<size_t>(pthread_self()));
#endif // _MSC_VER
}

using namespace log4cxx;
using namespace log4cxx::helpers;

static const char * const s_week_name[] = 
{
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char * const s_logger_type_name[LOGGER_TYPE_HIG - LOGGER_TYPE_LOW + 1] = 
{
    "Trace", 
    "Debug", 
    " Info", 
    " Warn", 
    "Error", 
    "Fatal"  
};

static unsigned char s_logger_type_open[LOGGER_TYPE_HIG - LOGGER_TYPE_LOW + 1] = { 0x00 };

class LoggerWrapper
{
private:
    LoggerWrapper();
    ~LoggerWrapper();

private:
    LoggerWrapper(const LoggerWrapper &);
    LoggerWrapper & operator = (const LoggerWrapper &);

public:
    static LoggerWrapper & instance();

public:
    void log_message(logger_type type, const char * file, const char * func, size_t line, const char * format, ...);
    void log_message(logger_type type, const char * file, const char * func, size_t line, const char * format, va_list args);
    void log_hex_message(logger_type type, const char * file, const char * func, size_t line, const char * message, const void * data, size_t data_len);

private:
    void log_normal_record(logger_type type, const char * file, const char * func, size_t line, const char * format, va_list args);

private:
    enum { LOG_RECORD_SIZE = 2048 };

private:
    static LoggerWrapper   s_logger_wrapper;

private:
    LoggerPtr              m_trace_logger;
    LoggerPtr              m_debug_logger;
    LoggerPtr              m_info_logger;
    LoggerPtr              m_warn_logger;
    LoggerPtr              m_error_logger;
    LoggerPtr              m_fatal_logger;
};

LoggerWrapper LoggerWrapper::s_logger_wrapper;

LoggerWrapper::LoggerWrapper()
{
    PropertyConfigurator::configure("log4cxx.cfg");
    m_trace_logger = Logger::getLogger("trace_logger");
    m_debug_logger = Logger::getLogger("debug_logger");
    m_info_logger = Logger::getLogger("info_logger");
    m_warn_logger = Logger::getLogger("warn_logger");
    m_error_logger = Logger::getLogger("error_logger");
    m_fatal_logger = Logger::getLogger("fatal_logger");
    memset(&s_logger_type_open, 0x01, sizeof(s_logger_type_open));
}

LoggerWrapper::~LoggerWrapper()
{
    memset(&s_logger_type_open, 0x00, sizeof(s_logger_type_open));
}

LoggerWrapper & LoggerWrapper::instance()
{
    return(s_logger_wrapper);
}

void LoggerWrapper::log_message(logger_type type, const char * file, const char * func, size_t line, const char * format, ...)
{
    va_list args = nullptr;
    va_start(args, format);
    log_normal_record(type, file, func, line, format, args);
    va_end(args);
}

void LoggerWrapper::log_message(logger_type type, const char * file, const char * func, size_t line, const char * format, va_list args)
{
    log_normal_record(type, file, func, line, format, args);
}

void LoggerWrapper::log_hex_message(logger_type type, const char * file, const char * func, size_t line, const char * message, const void * data, size_t data_len)
{
    const char * more = "";
    if (data_len > LOG_RECORD_SIZE * 9 / 20)
    {
        data_len = LOG_RECORD_SIZE * 9 / 20;
        more = "...";
    }
    char hex_data[LOG_RECORD_SIZE];
    hex_encode(data, data_len, hex_data, sizeof(hex_data) / sizeof(hex_data[0]), false);
    log_message(type, file, func, line, "%s%s%s", message, hex_data, more);
}

void LoggerWrapper::log_normal_record(logger_type type, const char * file, const char * func, size_t line, const char * format, va_list args)
{
    if (nullptr == file || nullptr == func || nullptr == format || nullptr == args)
    {
        return;
    }

    if (type < LOGGER_TYPE_LOW || type >= LOGGER_TYPE_HIG)
    {
        return;
    }

    char record[LOG_RECORD_SIZE];
    size_t record_size = 0;

    struct tm tm_now = simple_get_localtime();
    struct timeval tv_now = simple_gettimeofday();
    int millisecond = static_cast<int>(tv_now.tv_usec / 1000);
    int time_zone = simple_get_timezone();
    int day_of_week = simple_get_day_of_week();

    record_size += simple_snprintf
    (
        record + record_size, LOG_RECORD_SIZE - record_size, 
        "%4d-%02d-%02d %02d:%02d:%02d.%03d GMT%+03d:00 %s", 
        tm_now.tm_year + 1900, tm_now.tm_mon + 1, tm_now.tm_mday, 
        tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec, millisecond, 
        time_zone, s_week_name[day_of_week]
    );

    record_size += simple_snprintf
    (
        record + record_size, LOG_RECORD_SIZE - record_size, 
        " | %s | T%010u | %s:%s:%05d | ", 
        s_logger_type_name[type], current_thread_id(), file, func, line
    );

    record_size += simple_vsnprintf
    (
        record + record_size, LOG_RECORD_SIZE - record_size, format, args
    );

    record_size += 1; /* for '\0' */
    if (record_size > LOG_RECORD_SIZE)
    {
        record_size = LOG_RECORD_SIZE;
    }
    record[record_size - 1] = '\0';

    switch (type)
    {
        case LOGGER_TYPE_TRACE:
        {
            LOG4CXX_TRACE(m_trace_logger, record);
            break;
        }
        case LOGGER_TYPE_DEBUG:
        {
            LOG4CXX_DEBUG(m_debug_logger, record);
            break;
        }
        case LOGGER_TYPE_INFO:
        {
            LOG4CXX_INFO(m_info_logger, record);
            break;
        }
        case LOGGER_TYPE_WARN:
        {
            LOG4CXX_WARN(m_warn_logger, record);
            break;
        }
        case LOGGER_TYPE_ERROR:
        {
            LOG4CXX_ERROR(m_error_logger, record);
            break;
        }
        case LOGGER_TYPE_FATAL:
        {
            LOG4CXX_FATAL(m_fatal_logger, record);
            break;
        }
        default:
        {
            break;
        }
    }
}

void logger_enable(logger_type type)
{
    s_logger_type_open[type] = 0x01;
}

void logger_disable(logger_type type)
{
    s_logger_type_open[type] = 0x00;
}

void logger_enable_all()
{
    memset(&s_logger_type_open, 0x01, sizeof(s_logger_type_open));
}

void logger_disable_all()
{
    memset(&s_logger_type_open, 0x00, sizeof(s_logger_type_open));
}

void logger_message(logger_type type, const char * file, const char * func, size_t line, const char * format, ...)
{
    if (0x00 == s_logger_type_open[type])
    {
        return;
    }

    va_list args = nullptr;
    va_start(args, format);
    LoggerWrapper::instance().log_message(type, file, func, line, format, args);
    va_end(args);
}

void logger_hex_message(logger_type type, const char * file, const char * func, size_t line, const char * message, const void * data, size_t data_len)
{
    if (0x00 == s_logger_type_open[type])
    {
        return;
    }

    LoggerWrapper::instance().log_hex_message(type, file, func, line, message, data, data_len);
}
