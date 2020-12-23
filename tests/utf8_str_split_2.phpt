--TEST--
utf8_str_split with chunk of 2 chars
--FILE--
<?php
var_dump(utf8_str_split("1234567", 2));
var_dump(utf8_str_split("12345678", 2));
var_dump(utf8_str_split("😂😀😈a😂😀😈", 2));
var_dump(utf8_str_split("😂😀😈a😂😀😈z", 2));
?>
--EXPECT--
array(4) {
  [0]=>
  string(2) "12"
  [1]=>
  string(2) "34"
  [2]=>
  string(2) "56"
  [3]=>
  string(1) "7"
}
array(4) {
  [0]=>
  string(2) "12"
  [1]=>
  string(2) "34"
  [2]=>
  string(2) "56"
  [3]=>
  string(2) "78"
}
array(4) {
  [0]=>
  string(8) "😂😀"
  [1]=>
  string(5) "😈a"
  [2]=>
  string(8) "😂😀"
  [3]=>
  string(4) "😈"
}
array(4) {
  [0]=>
  string(8) "😂😀"
  [1]=>
  string(5) "😈a"
  [2]=>
  string(8) "😂😀"
  [3]=>
  string(5) "😈z"
}