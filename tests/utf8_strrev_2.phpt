--TEST--
utf8_strrev with invalid UTF-8 string
--FILE--
<?php
// We don't care about the output, but this shouldn't segfault.
utf8_strrev("😀" . substr("😁😂", 1)  . substr("😈", 1));
?>
--EXPECT--
