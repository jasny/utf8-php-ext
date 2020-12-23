/*
  +----------------------------------------------------------------------+
  | UTF-8 string functions (PHP extension)                               |
  +----------------------------------------------------------------------+
  | Copyright (c) 2020 Arnold Daniels                                    |
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

#ifndef PHP_UTF8_H
#define PHP_UTF8_H 1

#define PHP_UTF8_VERSION "0.0.1-dev"
#define PHP_UTF8_EXTNAME "utf8"

#ifdef PHP_WIN32
# define PHP_UTF8_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_UTF8_API __attribute__ ((visibility("default")))
#else
# define PHP_UTF8_API
#endif

/* Declare all functions and classes of the extension */
static PHP_FUNCTION(utf8_strlen);
static PHP_FUNCTION(utf8_strpos);
static PHP_FUNCTION(utf8_substr);
static PHP_FUNCTION(utf8_ord);
static PHP_FUNCTION(utf8_chr);
static PHP_FUNCTION(utf8_trim);
static PHP_FUNCTION(utf8_ltrim);
static PHP_FUNCTION(utf8_rtrim);
static PHP_FUNCTION(utf8_str_pad);
static PHP_FUNCTION(utf8_strrev);
static PHP_FUNCTION(utf8_str_split);

extern zend_module_entry utf8_module_entry;

#endif

