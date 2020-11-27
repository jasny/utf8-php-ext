/*
  +----------------------------------------------------------------------+
  | UTF-8 string functions (PHP extension)                               |
  +----------------------------------------------------------------------+
  | Copyright (c) 2018 Arnold Daniels                                    |
  +----------------------------------------------------------------------+
  | Permission is hereby granted, free of charge, to any person          |
  | obtaining a copy of this software and associated documentation files |
  | (the "Software"), to deal in the Software without restriction,       |
  | including without limitation the rights to use, copy, modify, merge, |
  | publish, distribute, sublicense, and/or sell copies of the Software, |
  | and to permit persons to whom the Software is furnished to do so,    |
  | subject to the following conditions:                                 |
  |                                                                      |
  | The above copyright notice and this permission notice shall be       |
  | included in all copies or substantial portions of the Software.      |
  |                                                                      |
  | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      |
  | EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   |
  | MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                |
  | NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  |
  | BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   |
  | ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    |
  | CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     |
  | SOFTWARE.                                                            |
  +----------------------------------------------------------------------+
  | Author: Arnold Daniels <arnold@jasny.net>                            |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_utf8.h"
#include "utf8_func.h"
#include "zend_exceptions.h"

#if HAVE_UTF8

/* Argument info for each function, used for reflection */
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_utf8_strlen, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 1)
ZEND_END_ARG_INFO()

/* Add all functions. (Keep PHP_FE_END as last element) */
static const zend_function_entry functions[] = {
    PHP_FE(utf8_strlen, arginfo_utf8_strlen)
    PHP_FE(utf8_strpos, NULL)
    PHP_FE(utf8_substr, NULL)
    PHP_FE(utf8_ord, NULL)
    PHP_FE(utf8_chr, NULL)
    PHP_FE_END
};

zend_module_entry utf8_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_UTF8_EXTNAME,
    functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_UTF8_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_UTF8
ZEND_GET_MODULE(utf8)
#endif

PHP_FUNCTION(utf8_strlen)
{
    char *str;
    size_t len;
    size_t count = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();

    for (size_t i = 0; i < len; i++, ++str) {
        count += ((*str & 0b11000000) != 0b10000000); // Don't count secondary bytes of multibyte chars
    }

    RETURN_LONG(count)
}

PHP_FUNCTION(utf8_strpos)
{
    char *str, *substr;
    size_t len, sublen;
    zend_long pos;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(str, len)
        Z_PARAM_STRING(substr, sublen)
    ZEND_PARSE_PARAMETERS_END();

    pos = utf8_pos(str, len, substr, sublen);

    if (pos < 0) {
        RETURN_FALSE
    }

    RETURN_LONG(pos)
}

PHP_FUNCTION(utf8_substr)
{
    char *str, *str_start, *str_end;
    size_t len, len_start;
    zend_long start = 0;
    zend_long length = 0;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STRING(str, len)
        Z_PARAM_LONG(start)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(length)
    ZEND_PARSE_PARAMETERS_END();

    if (labs(start) > len) {
        RETURN_FALSE // Quick return
    }

    if (start == 0) {
        str_start = str;
    } else if (start > 0) {
        str_start = utf8_walk(str, len, start);
    } else {
        str_start = utf8_walk_back(str, len, start);
    }
    if (str_start == NULL) {
        RETURN_FALSE
    }
    len_start = len - (str_start - str);

    if (EX_NUM_ARGS() < 3) {
        RETURN_STRINGL(str_start, len_start);
    }

    if (length == 0) {
        RETURN_EMPTY_STRING()
    }

    if (length > 0) {
        str_end = utf8_walk(str_start, len_start, length);
    } else {
        str_end = utf8_walk_back(str_start, len_start, length);
    }

    if (str_end == NULL) {
        RETURN_FALSE
    }

    RETURN_STRINGL(str_start, (str_end - str_start))
}

PHP_FUNCTION(utf8_ord)
{
    char *str;
    size_t len;
    uint32_t codepoint;
    uint32_t state = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();

    for (size_t i = 0; i < len; i++, str++) {
        if (utf8_decode(&state, &codepoint, *str) == UTF8_ACCEPT) {
            RETURN_LONG(codepoint)
        }
    }

    RETURN_LONG(-1)
}

PHP_FUNCTION(utf8_chr)
{
    char str[4];
    size_t len;
    zend_long codepoint;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(codepoint)
    ZEND_PARSE_PARAMETERS_END();

    len = utf8_encode(str, codepoint);

    RETURN_STRINGL(str, len)
}

#endif
