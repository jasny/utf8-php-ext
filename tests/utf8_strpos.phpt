--TEST--
utf8_strpos
--FILE--
<?php
var_dump(strpos("1234567", "3"));
var_dump(utf8_strpos("😀2😁4😂6😈", "😁"));
echo "\n";

var_dump(strpos("1234567", "X"));
var_dump(utf8_strpos("😀2😁4😂6😈", "X"));
?>
--EXPECT--
int(2)
int(2)

bool(false)
bool(false)