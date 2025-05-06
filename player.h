#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "card.h"

typedef struct player_s {
    char name[32];
    card* deck;
    int deckSize;
    bool computer;
} player;

void playCard(player player, card* discard, int* discardSize, int n);

void printPlayer(player player);

int makeSelection(player player, card topCard);

#endif //PLAYER_H