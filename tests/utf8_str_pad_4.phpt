--TEST--
utf8_str_pad with multiple char pad string
--FILE--
<?php
var_dump(utf8_str_pad("a", 8, "😂😀😈", STR_PAD_BOTH));
var_dump(utf8_str_pad("a", 8, "😂😀😈", STR_PAD_LEFT));
var_dump(utf8_str_pad("a", 8, "😂😀😈", STR_PAD_RIGHT));
?>
--EXPECT--
string(29) "😂😀😈a😂😀😈😂"
string(29) "😂😀😈😂😀😈😂a"
string(29) "a😂😀😈😂😀😈😂"
