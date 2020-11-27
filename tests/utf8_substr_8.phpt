--TEST--
utf8_strlen with a zero length
--FILE--
<?php
var_dump(utf8_substr("😀2😁4😂6😈", 0, 0));
?>
--EXPECT--
string(0) ""