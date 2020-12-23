--TEST--
utf8_str_split with a single chunk
--FILE--
<?php
var_dump(utf8_str_split(""));
var_dump(utf8_str_split("", 5));

var_dump(utf8_str_split("1"));
var_dump(utf8_str_split("1", 2));
var_dump(utf8_str_split("1", 5));

var_dump(utf8_str_split("😂"));
var_dump(utf8_str_split("😂", 2));
var_dump(utf8_str_split("😂", 5));

var_dump(utf8_str_split("😂😀", 2));
var_dump(utf8_str_split("😂😀", 5));
?>
--EXPECT--
array(1) {
  [0]=>
  string(0) ""
}
array(1) {
  [0]=>
  string(0) ""
}
array(1) {
  [0]=>
  string(1) "1"
}
array(1) {
  [0]=>
  string(1) "1"
}
array(1) {
  [0]=>
  string(1) "1"
}
array(1) {
  [0]=>
  string(4) "😂"
}
array(1) {
  [0]=>
  string(4) "😂"
}
array(1) {
  [0]=>
  string(4) "😂"
}
array(1) {
  [0]=>
  string(8) "😂😀"
}
array(1) {
  [0]=>
  string(8) "😂😀"
}