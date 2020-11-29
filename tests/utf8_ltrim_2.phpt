--TEST--
utf8_ltrim resulting in an empty string
--FILE--
<?php
var_dump(utf8_ltrim("", "😀"));
var_dump(utf8_ltrim("😀😈😀😈😀😈", "😀😈"));
?>
--EXPECT--
string(0) ""
string(0) ""
