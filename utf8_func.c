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

#include "utf8_func.h"
#include "zend_string.h"

size_t utf8_count(char *str, size_t len)
{
    size_t count = 0;

    for (size_t i = 0; i < len; i++, ++str) {
        count += IS_NOT_MB_CHAR(*str); // Don't count secondary bytes of multibyte chars
    }

    return count;
}

size_t utf8_pos(char *str, size_t len, char *substr, size_t sublen)
{
    char *ptr = substr;
    size_t count = -1;

    for (size_t i = 0; i < len; i++, str++) {
        if (EXPECTED(*str != *ptr)) {
            ptr = substr;
        } else {
            ptr++;

            if (UNEXPECTED(ptr - substr == sublen)) {
                return count;
            }
        }

        count += IS_NOT_MB_CHAR(*str); // Don't count secondary bytes of multibyte chars
    }

    return -1;
}

char* utf8_walk(char *str, size_t len, size_t pos)
{
    size_t count;
    size_t bytes;

    for (count = 0, bytes = 0; count < pos; str++, bytes++) {
        if (bytes > len) {
            return NULL;
        }
        count += IS_NOT_MB_CHAR(*str); // Don't count secondary bytes of multibyte chars
    }

    while (IS_MB_CHAR(*str)) {
        str++; // Walk to the end of multibyte char
    }

    return str;
}

char* utf8_rwalk(char *str, size_t len, zend_long pos)
{
    zend_long count;
    size_t bytes;

    str += len; // jump to the end of the string

    for (count = 0, bytes = 0; count > pos; str--, bytes++) {
        if (bytes > len) {
            return NULL;
        }
        count -= IS_NOT_MB_CHAR(*str); // Don't count secondary bytes of multibyte chars
    }

    while (IS_MB_CHAR(*str)) {
        str--; // Walk to the beginning of multibyte char
    }

    return str;
}

static zend_always_inline uint8_t match_chars(char *str, char *str_end, char *chars, size_t charslen)
{
    for (size_t j = 0; j < charslen; j++) {
        if (IS_NOT_MB_CHAR(chars[j]) && UTF8_CHAR_EQ(str, str_end, (chars + j), chars + charslen)) {
            return 1;
        }
    }

    return 0;
}

char* utf8_skip_chars(char *str, size_t len, char *chars, size_t charslen)
{
    char *str_end = str + len;

    for (size_t i = 0; i < len; i++, str++) {
        if (IS_NOT_MB_CHAR(*str) && !match_chars(str, str_end, chars, charslen)) {
            break;
        }
    }

    return str;
}

char* utf8_rskip_chars(char *str, size_t len, char *chars, size_t charslen)
{
    char *str_end = str + len;
    str += (len - 1); // jump to the end of the string

    for (size_t i = 0; i < len; i++, str--) {
        if (IS_NOT_MB_CHAR(*str) && !match_chars(str, str_end, chars, charslen)) {
            break;
        }
    }

    str++;

    while (IS_MB_CHAR(*str)) {
        str++; // Walk to the end of multibyte char
    }

    return str;
}

void utf8_repeat(zend_string **result, char *pad_str, size_t pad_str_len, size_t length)
{
    char *ptr = pad_str;
    size_t i;

    for (i = 0; i < length; i++) {
        do {
            ZSTR_VAL(*result)[ZSTR_LEN(*result)++] = *ptr;
        } while (ptr < pad_str + pad_str_len && IS_MB_CHAR(*(++ptr)));

        if (ptr == pad_str + pad_str_len) {
            ptr = pad_str;
        }
    }
}

/**
 * Encode a code point using UTF-8.
 * (produces U+FFFD on failure)
 *
 * @author Ondřej Hruška <ondra@ondrovo.com>
 * @license MIT
 * @see https://gist.github.com/MightyPork/52eda3e5677b4b03524e40c9f0ab1da5
 *
 * @param out - output buffer (min 4 characters)
 * @param utf - code point 0-0x10FFFF
 * @return number of bytes
 */
uint8_t utf8_encode(char *out, uint32_t utf)
{
    if (utf <= 0x7F) {
        // Plain ASCII
        out[0] = (char) utf;
        out[1] = '\0';
        return 1;
    } else if (utf <= 0x07FF) {
        // 2-byte unicode
        out[0] = (char) (((utf >> 6) & 0x1F) | 0xC0);
        out[1] = (char) (((utf >> 0) & 0x3F) | 0x80);
        out[2] = '\0';
        return 2;
    } else if (utf <= 0xFFFF) {
        // 3-byte unicode
        out[0] = (char) (((utf >> 12) & 0x0F) | 0xE0);
        out[1] = (char) (((utf >>  6) & 0x3F) | 0x80);
        out[2] = (char) (((utf >>  0) & 0x3F) | 0x80);
        out[3] = '\0';
        return 3;
    } else if (utf <= 0x10FFFF) {
        // 4-byte unicode
        out[0] = (char) (((utf >> 18) & 0x07) | 0xF0);
        out[1] = (char) (((utf >> 12) & 0x3F) | 0x80);
        out[2] = (char) (((utf >>  6) & 0x3F) | 0x80);
        out[3] = (char) (((utf >>  0) & 0x3F) | 0x80);
        out[4] = '\0';
        return 4;
    } else {
        // error - use replacement character
        out[0] = (char) 0xEF;
        out[1] = (char) 0xBF;
        out[2] = (char) 0xBD;
        out[3] = '\0';
        return 3;
    }
}
