#pragma once
#include <cstring>

struct Message {
    static const int MAX_MSG_LEN = 256;
    char text[MAX_MSG_LEN];
    bool isEmpty;

    Message() : text{}, isEmpty(true) {
        text[0] = '\0';
    }
};