--TEST--
utf8_strlen with positive start and without specifying the length
--FILE--
<?php
var_dump(substr("1234567", 2));
var_dump(utf8_substr("😀2😁4😂6😈", 2));
echo "\n";

var_dump(substr("1234567", 3));
var_dump(utf8_substr("😀2😁4😂6😈", 3));
?>
--EXPECT--
string(5) "34567"
string(14) "😁4😂6😈"

string(4) "4567"
string(10) "4😂6😈"