--TEST--
utf8_str_pad with utf8 char pad string
--FILE--
<?php
var_dump(utf8_str_pad("😀😈a😈😀", 9, "😂", STR_PAD_BOTH));
var_dump(utf8_str_pad("😀😈a😈😀", 9, "😂", STR_PAD_LEFT));
var_dump(utf8_str_pad("😀😈a😈😀", 9, "😂", STR_PAD_RIGHT));
?>
--EXPECT--
string(33) "😂😂😀😈a😈😀😂😂"
string(33) "😂😂😂😂😀😈a😈😀"
string(33) "😀😈a😈😀😂😂😂😂"
