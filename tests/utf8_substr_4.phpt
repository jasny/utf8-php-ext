--TEST--
utf8_substr with a negative start and a positive length
--FILE--
<?php
var_dump(substr("1234567", -4, 3));
var_dump(utf8_substr("😀2😁4😂6😈", -4, 3));
echo "\n";

var_dump(substr("1234567", -3, 1));
var_dump(utf8_substr("😀2😁4😂6😈", -3, 1));
?>
--EXPECT--
string(3) "456"
string(6) "4😂6"

string(1) "5"
string(4) "😂"