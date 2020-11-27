![improved PHP library](https://user-images.githubusercontent.com/100821/46372249-e5eb7500-c68a-11e8-801a-2ee57da3e5e3.png)

# UTF-8 string functions

[![Build Status](https://travis-ci.org/improved-php-library/utf8string.svg?branch=master)](https://travis-ci.org/improved-php-library/utf8string)
[![Build status](https://ci.appveyor.com/api/projects/status/7rof1vr8mv4kam17/branch/master?svg=true)](https://ci.appveyor.com/project/jasny/utf8string/branch/master)

Drop in replacement string functions for UTF-8 encoded strings.

This extension only supports UTF-8. It performs much better than the mbstring, which uses heavy abstraction to support a
large set of character sets.

---

## Requirements

* PHP 7.2+

## Installation

    phpize
    ./configure
    make
    make test
    make install

Add the following line to your `php.ini`

    extension=utf8string.so

To try out the extension, you can run the following command

    php -a -d extension=modules/utf8string.so

## Functions

