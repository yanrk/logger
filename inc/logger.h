/********************************************************
 * Description : logger helper
 * Data        : 2014-12-04 09:03:24
 * Author      : yanrk
 * Email       : yanrkchina@hotmail.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2013 - 2015
 ********************************************************/

#ifndef STUPID_LOGGER_H
#define STUPID_LOGGER_H


#include <cstddef>

#ifdef _MSC_VER
    #define STUPID_LOGGER_CDECL         __cdecl
    #define STUPID_LOGGER_API           __declspec(dllexport)
#else
    #define STUPID_LOGGER_CDECL
    #define STUPID_LOGGER_API
#endif // _MSC_VER

#define STUPID_LOGGER_C_API(RET_TYPE)   extern "C" STUPID_LOGGER_API RET_TYPE STUPID_LOGGER_CDECL

enum logger_type
{
    LOGGER_TYPE_LOW, 
    LOGGER_TYPE_TRACE = LOGGER_TYPE_LOW, 
    LOGGER_TYPE_DEBUG, 
    LOGGER_TYPE_INFO, 
    LOGGER_TYPE_WARN, 
    LOGGER_TYPE_ERROR, 
    LOGGER_TYPE_FATAL, 
    LOGGER_TYPE_DUMMY, 
    LOGGER_TYPE_HIG = LOGGER_TYPE_DUMMY  
};

STUPID_LOGGER_C_API(void) logger_enable(logger_type type);
STUPID_LOGGER_C_API(void) logger_disable(logger_type type);
STUPID_LOGGER_C_API(void) logger_enable_all();
STUPID_LOGGER_C_API(void) logger_disable_all();
STUPID_LOGGER_C_API(void) logger_message(logger_type type, const char * file, const char * func, size_t line, const char * format, ...);
STUPID_LOGGER_C_API(void) logger_hex_message(logger_type type, const char * file, const char * func, size_t line, const char * message, const void * data, size_t data_len);

#define LOG_TRACE(fmt, ...)                                                           \
logger_message(LOGGER_TYPE_TRACE, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...)                                                           \
logger_message(LOGGER_TYPE_DEBUG, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...)                                                            \
logger_message(LOGGER_TYPE_INFO,  __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...)                                                            \
logger_message(LOGGER_TYPE_WARN,  __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...)                                                           \
logger_message(LOGGER_TYPE_ERROR, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_FATAL(fmt, ...)                                                           \
logger_message(LOGGER_TYPE_FATAL, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_TRACE_HEX(message, hex_data, data_len)                                                 \
logger_hex_message(LOGGER_TYPE_TRACE, __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_DEBUG_HEX(message, hex_data, data_len)                                                 \
logger_hex_message(LOGGER_TYPE_DEBUG, __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_INFO_HEX(message, hex_data, data_len)                                                  \
logger_hex_message(LOGGER_TYPE_INFO,  __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_WARN_HEX(message, hex_data, data_len)                                                  \
logger_hex_message(LOGGER_TYPE_WARN,  __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_ERROR_HEX(message, hex_data, data_len)                                                 \
logger_hex_message(LOGGER_TYPE_ERROR, __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_FATAL_HEX(message, hex_data, data_len)                                                 \
logger_hex_message(LOGGER_TYPE_FATAL, __FILE__, __FUNCTION__, __LINE__, message, hex_data, data_len)

#define LOG_DUMMY(fmt, ...)
#define LOG_DUMMY_HEX(message, hex_data, data_len)


#endif // STUPID_LOGGER_H
