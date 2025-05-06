#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "card.h"
#include "config.h"

//The regular colors, in deck order.
const char regularColors[] = {'R', 'Y', 'G', 'B'};
//The special types, in deck order
const char specialTypes[] = {'A', 'O', 'N', 'R'};

char* cardName(card c, char buf[], int len) {
    if (c.color == 'S') {
        switch (c.name) {
            case 'A': strncpy(buf, "AND", len);
            break;
            case 'O': strncpy(buf, "OR", len);;
            break;
            case 'N': strncpy(buf, "NOT", len);
            break;
            case 'R': strncpy(buf, "Reverse", len);
        }
        return buf;
    }
    int colorCode;
    char* colorName;
    switch (c.color) {
        case 'R':
        colorName = "RED";
        colorCode = 31;
        break;
        case 'G':
        colorName = "GREEN";
        colorCode = 32;
        break;
        case 'Y':
        colorName = "YELLOW";
        colorCode = 33;
        break;
        case 'B':
        colorName = "BLUE";
        colorCode = 34;
        break;
    }
    #ifdef COLOR
    //colored text!!
    snprintf(buf, len, "\033[%dm%s %c\033[0m", colorCode, colorName, c.name);
    #else
    snprintf(buf, len, "%s %c", colorName, c.name);
    #endif
    return buf;
}

void printCard(card c) {
    char buf[20];
    printf("%s\n", cardName(c, buf, sizeof buf));
}

bool isValidCard(card a, card b) {
    return a.name == b.name || (a.color == b.color && a.color != 'S');
}