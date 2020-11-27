--TEST--
utf8_strlen with position that's greater than the string length
--FILE--
<?php
var_dump(utf8_substr("😀2😁4😂6😈", 10));
var_dump(utf8_substr("😀2😁4😂6😈", 100));
var_dump(utf8_substr("😀2😁4😂6😈", -10));
var_dump(utf8_substr("😀2😁4😂6😈", -100));
?>
--EXPECT--
bool(false)
bool(false)
bool(false)
bool(false)
