--TEST--
utf8_strlen basic test
--FILE--
<?php
var_dump(strlen("UTF-8 😀"));
var_dump(utf8_strlen("UTF-8 😀"));

?>
--EXPECT--
