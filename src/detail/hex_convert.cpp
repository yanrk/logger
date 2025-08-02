/********************************************************
 * Description : conversions of binary and hexadecimal
 * Data        : 2014-12-02 12:10:44
 * Author      : yanrk
 * Email       : yanrkchina@hotmail.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2013 - 2015
 ********************************************************/

#include <cstring>
#include "detail/hex_convert.h"

#define HEX_ENCODE_SIZE(in_len) ((in_len) * 3 + 1)

static const char hex_lower_table[] = 
{
    '0', '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'  
};

static const char hex_upper_table[] = 
{
    '0', '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'  
};

bool binary_to_hex(const unsigned char src, char dst[3], bool lower)
{
    if (nullptr == dst)
    {
        return false;
    }

    if (lower)
    {
        dst[0] = hex_lower_table[(src >> 4) & 0x0F];
        dst[1] = hex_lower_table[src & 0x0F];
    }
    else
    {
        dst[0] = hex_upper_table[(src >> 4) & 0x0F];
        dst[1] = hex_upper_table[src & 0x0F];
    }
    dst[2] = ' ';

    return true;
}

bool hex_encode(const unsigned char * src, size_t src_len, char * dst, size_t dst_len, bool lower)
{
    if (nullptr == src || nullptr == dst || HEX_ENCODE_SIZE(src_len) > dst_len)
    {
        return false;
    }

    for (size_t index = 0; index < src_len; ++index)
    {
        if (!binary_to_hex(src[0], dst, lower))
        {
            return false;
        }

        src += 1;
        dst += 3;
    }

    dst[0] = '\0';

    return true;
}

bool hex_encode(const void * src, size_t src_len, char * dst, size_t dst_len, bool lower)
{
    return hex_encode(reinterpret_cast<const unsigned char *>(src), src_len, dst, dst_len, lower);
}
