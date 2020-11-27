--TEST--
utf8_substr with a negative start and a negative length
--FILE--
<?php
var_dump(substr("1234567", -5, -3));
var_dump(utf8_substr("😀2😁4😂6😈", -5, -3));
echo "\n";
?>
--EXPECT--
string(2) "34"
string(5) "😁4"
