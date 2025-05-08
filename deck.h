#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "player.h"
#include "config.h"

card* initializeDeck(card* deck, int* deckSize);

void shuffleDeck(card* p);

card* getCard(card* p, int n);

card* lastCard(card* p, int deckSize);

card* secondLastCard(card* p, int deckSize);

card* popFront(card** listpp, int* deckSize);

card* popCard(card* p, int* deckSize);

void appendCard(card* p, int* deckSize, card* new);

void pushCard(card** listpp, int* deckSize, card* new);

card* removeCard(card** listpp, int* deckSize, int pos);

int drawCard(card* deck, int* deckSize, player* p);

int drawCards(card* deck, int* deckSize, player* p, int n);

void dealCards(card* deck, int* deckSize, player players[], int playerCount, int cards);

void freeDeck(card* p, int deckSize);

#endif //DECK_H