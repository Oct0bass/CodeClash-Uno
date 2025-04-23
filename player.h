#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "card.h"

typedef struct player_s {
    char name[32];
    card* hand;
    bool computer;
} player;

#endif //PLAYER_H