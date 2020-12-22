//
// Created by arnold on 22-12-20.
//

#ifndef UTF8_CHARLEN_H
#define UTF8_CHARLEN_H

static const uint8_t utf8len[] = {1,1,1,1,1,1,1,1, 0,0,0,0, 2,2, 3, 4};

static zend_always_inline uint8_t utf8_char_len(char str) {
    return utf8len[(str >> 4) & 0xf];
}

#endif //UTF8_CHARLEN_H
