--TEST--
utf8_strlen with negative start and without specifying the length
--FILE--
<?php
var_dump(substr("1234567", -4));
var_dump(utf8_substr("😀2😁4😂6😈", -4));
echo "\n";

var_dump(substr("1234567", -3));
var_dump(utf8_substr("😀2😁4😂6😈", -3));
?>
--EXPECT--
string(4) "4567"
string(10) "4😂6😈"

string(3) "567"
string(9) "😂6😈"