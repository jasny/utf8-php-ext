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

#include "php.h"
#include "utf8_decode.h"

#ifndef UTF8_FUNC_H
#define UTF8_FUNC_H

#define IS_MB_CHAR(chr) ((chr & 0b11000000) == 0b10000000)
#define IS_NOT_MB_CHAR(chr) ((chr & 0b11000000) != 0b10000000)

#define UTF8_CHAR_EQ(str, str_end, chars, chars_end) \
    (chars[0] == str[0] && (chars + 1 > chars_end || IS_NOT_MB_CHAR(chars[1]) || \
        (str + 1 <= str_end && chars[1] == str[1]) && (chars + 2 > chars_end || IS_NOT_MB_CHAR(chars[2]) || \
            (str + 2 <= str_end && chars[2] == str[2]) && (chars + 3 > chars_end || IS_NOT_MB_CHAR(chars[3]) || \
                (str + 3 <= str_end && chars[3] == str[3])))))

zend_long utf8_pos(char *str, size_t len, char *substr, size_t sublen);
char* utf8_walk(char *str, size_t len, size_t pos);
char* utf8_rwalk(char *str, size_t len, zend_long pos);
char* utf8_skip_chars(char *str, size_t len, char *chars, size_t charslen);
char* utf8_rskip_chars(char *str, size_t len, char *chars, size_t charslen);
uint8_t utf8_encode(char *out, uint32_t utf);

#endif //UTF8_FUNC_H
