#include <stdio.h>
#include <stdbool.h>

#include "card.h"

char* cardName(card c) {
    char result[20];
    if (c.color == 'S') {
        switch (c.name) {
            case 'A': return "AND";
            break;
            case 'O': return "OR";
            break;
            case 'N': return "NOT";
            break;
            case 'R': return "Reverse";
        }
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
    //colored text!!
    snprintf(result, sizeof(result), "\033[%dm%s %c\033[0m", colorCode, colorName, c.name);
    return result;
}

bool isCompatible(card a, card b) {
    return a.name == b.name || (a.color == b.color && a.color != 'S');
}