dnl $Id$
dnl config.m4 for extension utf8

sinclude(./autoconf/pecl.m4)
sinclude(./autoconf/php-executable.m4)

PECL_INIT([utf8])

PHP_ARG_ENABLE(utf8, whether to enable utf8, [ --enable-utf8   Enable utf8])

if test "$PHP_utf8" != "no"; then
  AC_DEFINE(HAVE_UTF8, 1, [whether utf8 is enabled])
  PHP_NEW_EXTENSION(utf8, utf8.c, $ext_shared)

  PHP_ADD_MAKEFILE_FRAGMENT
  PHP_INSTALL_HEADERS([ext/utf8], [php_utf8.h])
fi
