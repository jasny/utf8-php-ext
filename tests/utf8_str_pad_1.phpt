--TEST--
utf8_str_pad with default pad string
--FILE--
<?php
var_dump(utf8_str_pad("😀😈a😈😀", 9));
?>
--EXPECT--
string(21) "😀😈a😈😀    "
