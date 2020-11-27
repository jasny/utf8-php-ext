--TEST--
utf8_ord
--FILE--
<?php
var_dump(dechex(utf8_ord("a")));
var_dump(dechex(utf8_ord("😂")));
?>
--EXPECT--
string(2) "61"
string(5) "1f602"
