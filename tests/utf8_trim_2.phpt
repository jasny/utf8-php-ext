--TEST--
utf8_trim resulting in an empty string
--FILE--
<?php
var_dump(utf8_trim("", "😀"));
var_dump(utf8_trim("😀😈😀😈😀😈", "😀😈"));
?>
--EXPECT--
string(0) ""
string(0) ""
