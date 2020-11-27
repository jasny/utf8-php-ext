--TEST--
utf8_ord
--FILE--
<?php
var_dump(utf8_chr(61));
var_dump(utf8_chr(0x1f602));
var_dump(utf8_chr(0x20FFFF));
?>
--EXPECT--
string(1) "="
string(4) "😂"
string(3) "�"