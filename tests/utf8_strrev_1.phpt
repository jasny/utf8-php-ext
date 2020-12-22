--TEST--
utf8_strrev
--FILE--
<?php
var_dump(utf8_strrev("1234567"));
var_dump(utf8_strrev("😀😁😂😈"));
var_dump(utf8_strrev("😀2😁4😂6😈"));
?>
--EXPECT--
string(7) "7654321"
string(16) "😈😂😁😀"
string(19) "😈6😂4😁2😀"