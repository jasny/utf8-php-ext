--TEST--
utf8_rtrim resulting in an empty string
--FILE--
<?php
var_dump(utf8_rtrim("", "😀"));
var_dump(utf8_rtrim("😀😈😀😈😀😈", "😀😈"));
?>
--EXPECT--
string(0) ""
string(0) ""
