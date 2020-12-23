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

#define STR_PAD_LEFT   0
#define STR_PAD_RIGHT  1
#define STR_PAD_BOTH   2

static const zend_function_entry functions[] = {
    PHP_FE(utf8_strlen, NULL)
    PHP_FE(utf8_strpos, NULL)
    PHP_FE(utf8_substr, NULL)
    PHP_FE(utf8_ord, NULL)
    PHP_FE(utf8_chr, NULL)
    PHP_FE(utf8_trim, NULL)
    PHP_FE(utf8_ltrim, NULL)
    PHP_FE(utf8_rtrim, NULL)
    PHP_FE(utf8_str_pad, NULL)
    PHP_FE(utf8_strrev, NULL)
    PHP_FE(utf8_str_split, NULL)
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

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(utf8_count(str, len));
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
        RETURN_FALSE;
    }

    RETURN_LONG(pos);
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
        RETURN_FALSE; // Quick return
    }

    if (start == 0) {
        str_start = str;
    } else if (start > 0) {
        str_start = utf8_walk(str, len, start);
    } else {
        str_start = utf8_rwalk(str, len, start);
    }
    if (str_start == NULL) {
        RETURN_FALSE;
    }
    len_start = len - (str_start - str);

    if (EX_NUM_ARGS() < 3) {
        RETURN_STRINGL(str_start, len_start);
    }

    if (length == 0) {
        RETURN_EMPTY_STRING();
    }

    if (length > 0) {
        str_end = utf8_walk(str_start, len_start, length);
    } else {
        str_end = utf8_rwalk(str_start, len_start, length);
    }

    if (str_end == NULL) {
        RETURN_FALSE;
    }

    RETURN_STRINGL(str_start, (str_end - str_start));
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
            RETURN_LONG(codepoint);
        }
    }

    RETURN_LONG(-1);
}

PHP_FUNCTION(utf8_chr)
{
    char str[5];
    size_t len;
    zend_long codepoint;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(codepoint)
    ZEND_PARSE_PARAMETERS_END();

    len = utf8_encode(str, codepoint);

    RETURN_STRINGL(str, len);
}

PHP_FUNCTION(utf8_trim)
{
    char *str, *chars, *str_start, *str_end;
    size_t len, charslen;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(str, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(chars, charslen)
    ZEND_PARSE_PARAMETERS_END();

    str_start = utf8_skip_chars(str, len, chars, charslen);

    if (str_start == str + len) {
        RETURN_EMPTY_STRING()
    }

    str_end = utf8_rskip_chars(str, len, chars, charslen);

    RETURN_STRINGL(str_start, (str_end - str_start));
}

PHP_FUNCTION(utf8_ltrim)
{
    char *str, *chars, *str_start;
    size_t len, charslen;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(str, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(chars, charslen)
    ZEND_PARSE_PARAMETERS_END();

    str_start = utf8_skip_chars(str, len, chars, charslen);

    RETURN_STRINGL(str_start, len - (str_start - str));
}

PHP_FUNCTION(utf8_rtrim)
{
    char *str, *chars, *str_end;
    size_t len, charslen;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(str, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(chars, charslen)
    ZEND_PARSE_PARAMETERS_END();

    str_end = utf8_rskip_chars(str, len, chars, charslen);

    RETURN_STRINGL(str, (str_end - str));
}

PHP_FUNCTION(utf8_str_pad)
{
    zend_string *input;
    zend_long pad_length, count;

    size_t num_pad_chars;
    char *pad_str = " ";
    size_t pad_str_len = 1;
    zend_long pad_type_val = STR_PAD_RIGHT;
    size_t left_pad = 0, right_pad = 0;
    zend_string *result = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 4)
        Z_PARAM_STR(input)
        Z_PARAM_LONG(pad_length)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(pad_str, pad_str_len)
        Z_PARAM_LONG(pad_type_val)
    ZEND_PARSE_PARAMETERS_END();

    count = utf8_count(ZSTR_VAL(input), ZSTR_LEN(input));

    if (pad_length < 0  || (size_t)pad_length <= count) {
        RETURN_STR_COPY(input);
    }

    if (pad_str_len == 0) {
        php_error_docref(NULL, E_WARNING, "Padding string cannot be empty");
        return;
    }

    if (pad_type_val < STR_PAD_LEFT || pad_type_val > STR_PAD_BOTH) {
        php_error_docref(NULL, E_WARNING, "Padding type has to be STR_PAD_LEFT, STR_PAD_RIGHT, or STR_PAD_BOTH");
        return;
    }

    num_pad_chars = (pad_length - count);
    if (num_pad_chars >= INT_MAX) {
        php_error_docref(NULL, E_WARNING, "Padding length is too long");
        return;
    }

    result = zend_string_safe_alloc(1, ZSTR_LEN(input), num_pad_chars * MIN(pad_str_len, 4), 0);
    ZSTR_LEN(result) = 0;

    switch (pad_type_val) {
        case STR_PAD_RIGHT:
            left_pad = 0;
            right_pad = num_pad_chars;
            break;

        case STR_PAD_LEFT:
            left_pad = num_pad_chars;
            right_pad = 0;
            break;

        case STR_PAD_BOTH:
            left_pad = num_pad_chars / 2;
            right_pad = num_pad_chars - left_pad;
            break;
    }

    if (left_pad > 0) {
        utf8_repeat(&result, pad_str, pad_str_len, left_pad);
    }

    memcpy(ZSTR_VAL(result) + ZSTR_LEN(result), ZSTR_VAL(input), ZSTR_LEN(input));
    ZSTR_LEN(result) += ZSTR_LEN(input);

    if (right_pad > 0) {
        utf8_repeat(&result, pad_str, pad_str_len, right_pad);
    }

    ZSTR_VAL(result)[ZSTR_LEN(result)] = '\0';

    RETURN_NEW_STR(result);
}

PHP_FUNCTION(utf8_strrev)
{
    char *str, *ptr;
    size_t len;
    uint8_t i, n;
    zend_string *result;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();

    result = zend_string_alloc(len, 0);
    ptr = result->val + len;

    while (ptr > result->val) {
        n = utf8_char_len(*str) ?: 1;

        for (i = 0; i < n; i++) {
            *(ptr - n + i) = *str;
            str++;
        }

        ptr -= n;
    }

    RETURN_NEW_STR(result);
}

PHP_FUNCTION(utf8_str_split)
{
    char *str, *next;
    size_t len, chunk_len;
    zend_long split_length = 1;
    const char *p;

    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STRING(str, len)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(split_length)
    ZEND_PARSE_PARAMETERS_END();

    if (split_length <= 0) {
        php_error_docref(NULL, E_WARNING, "The length of each segment must be greater than zero");
        RETURN_FALSE;
    }

    if (len == 0) {
        array_init_size(return_value, 1);
        add_next_index_stringl(return_value, str, len);
        return;
    }

    array_init(return_value);

    do {
        next = utf8_walk(str, len, split_length);
        chunk_len = next != NULL && str + len > next ? next - str : len;

        if (len > 0) {
            add_next_index_stringl(return_value, str, chunk_len);
        }

        len -= chunk_len;
        str = next;
    } while (len > 0);
}

#endif