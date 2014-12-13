/********************************************************
 * Description : test logger
 * Data        : 2014-01-07 09:11:12
 * Author      : yanrk
 * Email       : yanrenke@viewat.com.cn
 * Blog        :
 * Version     : 1.0
 * History     :
 * Copyright(C): viewat & ewanshang
 ********************************************************/

#include "test.h"
#include "logger.h"

void test_logger(void)
{
    LOG_TRACE("log trace test, log type %d", LOGGER_TYPE_TRACE);
    LOG_DEBUG("log debug test, log type %d", LOGGER_TYPE_DEBUG);
    LOG_INFO("log info test, log type %d", LOGGER_TYPE_INFO);
    LOG_WARN("log warn test, log type %d", LOGGER_TYPE_WARN);
    LOG_ERROR("log error test, log type %d", LOGGER_TYPE_ERROR);
    LOG_FATAL("log fatal test, log type %d", LOGGER_TYPE_FATAL);
    LOG_DUMMY("log dummy test, log type %d", LOGGER_TYPE_DUMMY);

    const unsigned char temp[] = "hello world";

    LOG_TRACE_HEX("log trace test, temp(binary): ", temp, sizeof(temp));
    LOG_DEBUG_HEX("log debug test, temp(binary): ", temp, sizeof(temp));
    LOG_INFO_HEX("log info test, temp(binary): ", temp, sizeof(temp));
    LOG_WARN_HEX("log warn test, temp(binary): ", temp, sizeof(temp));
    LOG_ERROR_HEX("log error test, temp(binary): ", temp, sizeof(temp));
    LOG_FATAL_HEX("log fatal test, temp(binary): ", temp, sizeof(temp));
    LOG_DUMMY_HEX("log dummy test, temp(binary): ", temp, sizeof(temp));
}
