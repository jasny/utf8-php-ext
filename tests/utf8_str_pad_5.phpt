--TEST--
utf8_str_pad with string longer than pad length
--FILE--
<?php
var_dump(utf8_str_pad("😂😀😈😂😀😈", 5, "."));
var_dump(utf8_str_pad("😂😀😈😂😀😈", 6, "."));
var_dump(utf8_str_pad("😂😀😈😂😀😈", 7, "."));
?>
--EXPECT--
string(24) "😂😀😈😂😀😈"
string(24) "😂😀😈😂😀😈"
string(25) "😂😀😈😂😀😈."