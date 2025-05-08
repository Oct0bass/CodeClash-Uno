#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

extern const char regularColors[];
extern const char specialTypes[];

typedef struct card_s {
    char name; 
    char color;
    struct card_s *listp;
} card;

char* colorName(card c);

char* cardName(card s, char buf[], int len);

void printCard(card s);

bool isValidCard(card a, card b);

#endif //CARD_H