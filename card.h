#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

//The regular colors, in deck order.
const char regularColors[] = {'R', 'Y', 'G', 'B'};
//The special types, in deck order
const char specialTypes[] = {'A', 'O', 'N', 'R'};

typedef struct card_s {
    char name; 
    char color;
    struct card_s *listp;
} card;

char* cardName(card s);

bool isCompatible(card a, card b);

#endif //CARD_H