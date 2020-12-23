--TEST--
utf8_str_split
--FILE--
<?php
var_dump(utf8_str_split("1234"));
var_dump(utf8_str_split("😂😀😈a"));
?>
--EXPECT--
array(4) {
  [0]=>
  string(1) "1"
  [1]=>
  string(1) "2"
  [2]=>
  string(1) "3"
  [3]=>
  string(1) "4"
}
array(4) {
  [0]=>
  string(4) "😂"
  [1]=>
  string(4) "😀"
  [2]=>
  string(4) "😈"
  [3]=>
  string(1) "a"
}