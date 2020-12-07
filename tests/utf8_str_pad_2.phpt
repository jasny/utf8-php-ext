--TEST--
utf8_str_pad with single char pad string
--FILE--
<?php
var_dump(utf8_str_pad("😀😈a😈😀", 9, ".", STR_PAD_BOTH));
var_dump(utf8_str_pad("😀😈a😈😀", 9, ".", STR_PAD_LEFT));
var_dump(utf8_str_pad("😀😈a😈😀", 9, ".", STR_PAD_RIGHT));
?>
--EXPECT--
string(21) "..😀😈a😈😀.."
string(21) "....😀😈a😈😀"
string(21) "😀😈a😈😀...."
