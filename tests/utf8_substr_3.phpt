--TEST--
utf8_substr with a positive start and a positive length
--FILE--
<?php
var_dump(substr("1234567", 2, 3));
var_dump(utf8_substr("😀2😁4😂6😈", 2, 3));
echo "\n";

var_dump(substr("1234567", 3, 3));
var_dump(utf8_substr("😀2😁4😂6😈", 3, 3));
?>
--EXPECT--
string(3) "345"
string(9) "😁4😂"

string(3) "456"
string(6) "4😂6"