#include <stdio.h>
#include <string.h>

#include "util.h"

char* ordinal(unsigned int n, char buf[], int len) {
    if (n == 0) {
        snprintf(buf, len, "zeroth");
    } else if (n < 20) {
        switch (n) {
            case 1: snprintf(buf, len, "first");
            break;
            case 2: snprintf(buf, len, "second");
            break;
            case 3: snprintf(buf, len, "third");
            break;
            case 4: snprintf(buf, len, "fourth");
            break;
            case 5: snprintf(buf, len, "fifth");
            break;
            case 6: snprintf(buf, len, "sixth");
            break;
            case 7: snprintf(buf, len, "seventh");
            break;
            case 8: snprintf(buf, len, "eighth");
            break;
            case 9: snprintf(buf, len, "ninth");
            break;
            case 10: snprintf(buf, len, "tenth");
            break;
            case 11: snprintf(buf, len, "eleventh");
            break;
            case 12: snprintf(buf, len, "twelfth");
            break;
            case 13: snprintf(buf, len, "thirteenth");
            break;
            case 14: snprintf(buf, len, "fourteenth");
            break;
            case 15: snprintf(buf, len, "fifteenth");
            break;
            case 16: snprintf(buf, len, "sixteenth");
            break;
            case 17: snprintf(buf, len, "seventeenth");
            break;
            case 18: snprintf(buf, len, "eighteenth");
            break;
            case 19: snprintf(buf, len, "nineteenth");
            break;
        }
    } else if (n < 100) {
        //only works because we know n < 10
        char onesbuf[8];
        char* tens;
        switch (n / 10) {
            case 2: tens = "twent";
            break;
            case 3: tens = "thirt";
            break;
            case 4: tens = "fourt";
            break;
            case 5: tens = "fift";
            break;
            case 6: tens = "sixt";
            break;
            case 7: tens = "sevent";
            break;
            case 8: tens = "eight";
            break;
            case 9: tens = "ninet";
            break;
        }
        if (n % 10 == 0) {
            snprintf(buf, len, "%sieth", tens);
        } else {
            snprintf(buf, len, "%sy-%s", tens, ordinal(n % 10, onesbuf, sizeof onesbuf));
        }
    } else {
        //Just print the number
        char* suffix;
        switch (n % 10) {
            case 1: suffix = "st";
            break;
            case 2: suffix = "nd";
            break;
            case 3: suffix = "rd";
            break;
            default: suffix = "th";
        }
        snprintf(buf, len, "%d%s", n, suffix);
    }
    return buf;
}