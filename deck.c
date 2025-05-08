#include <stdlib.h>
#include <time.h>

#include "deck.h"
#include "card.h"
#include "player.h"
#include "util.h"
#include "config.h"

const int shuffleIterations = 10000;

card* initializeDeck(card* deck, int* deckSize) {
    #ifdef DECK_LINKED_LIST
    card* c = deck;
    //2 0-9 sets of cards of each color
    for (int i = 0; i < 80; i++) {
        c->color = regularColors[i / 20];
        c->name = '0' + i % 10;
        if (i >= *deckSize - 1) c->listp = malloc(sizeof(card));
        c = c->listp;
    }
    //Special cards
    for (int i = 0; i < 20; i++) {
        c->color = 'S';
        c->name = specialTypes[i / 5];
        if (i + 80 >= *deckSize) c->listp = malloc(sizeof(card));
        c = c->listp;
    }
    #else
    for (int i = 0; i < 80; i++) {
        deck[i].color = regularColors[i / 20];
        deck[i].name = '0' + i % 10;
    }
    for (int i = 0; i < 20; i++) {
        deck[i].color = 'S';
        deck[i].name = specialTypes[i / 5];
    }
    #endif
    if (*deckSize < 100) *deckSize = 100;
    return deck;
}

void shuffleDeck(card* p) {
    srand(time(NULL));
    for (int i = 0; i < shuffleIterations; i++) {
        int pos1 = rand() % 100;
        int pos2 = rand() % 100;
        int first = MIN(pos1, pos2), last = MAX(pos1, pos2);
        card* c1 = getCard(p, first);
        //Skip unneccesary iteration
        card* c2 = getCard(c1, last - first);
        //Swap the data (color and name)
        char tmpColor = c1->color;
        char tmpName = c1->name;
        c1->color = c2->color;
        c1->name = c2->name;
        c2->color = tmpColor;
        c2->name = tmpName;
    }
}

//Returns a pointer to the nth card in the list
card* getCard(card* deck, int n) {
    #ifdef DECK_LINKED_LIST
    card* p = deck;
    for (int i = 0; i < n && p; i++) {
        p = p->listp;
    }
    return p;
    #else
    return deck[n];
    #endif
}

card* lastCard(card* p, int deckSize) {
    if (deckSize == 0) return NULL;
    for (int i = 0; p->listp && i < deckSize - 1; p = p->listp);
    return p;
}

card* secondLastCard(card* p, int deckSize) {
    if (deckSize < 2) return NULL;
    for (int i = 0; i < deckSize - 2 && p->listp->listp; p = p->listp, i++);
    return p;
}

//Remove the first card and return it
card* popFront(card** listpp, int* deckSize) {
    card* result = *listpp;
    *listpp = (*listpp)->listp;
    (*deckSize)--;
    return result;
}

//Remove the last card and return it
card* popCard(card* p, int* deckSize) {
    //Find the penultimate card
    card* secondLast = secondLastCard(p, *deckSize);
    card* result = secondLast->listp;
    secondLast->listp = NULL;
    (*deckSize)--;
    return result;
}

void appendCard(card* p, int* deckSize, card* new) {
    if (deckSize > 0) {
        lastCard(p, *deckSize)->listp = new;
        (*deckSize)++;
    }
}

void pushCard(card** deckp, int* deckSize, card* new) {
    new->listp = *deckp;
    *deckp = new;
    (*deckSize)++;
}

card* removeCard(card** listpp, int* deckSize, int pos) {
    if (pos == 0) return popFront(listpp, deckSize);
    card* prev = getCard(*listpp, pos - 1);
    card* removed = prev->listp;
    prev->listp = removed->listp;
    (*deckSize)--;
    removed->listp = NULL;
    return removed;
}

int drawCard(card* deck, int* deckSize, player* p) {
    if (*deckSize == 0) return 0;
    card* newCard = popCard(deck, deckSize);
    if (p->deckSize >= 1) { 
        appendCard(p->deck, &p->deckSize, newCard);
    } else {
        p->deck = newCard;
        p->deckSize = 1;
    }
    return 1;
}

int drawCards(card* deck, int* deckSize, player* p, int n) {
    if (n == 0) return 1;
    for (int i = 0; i < n; i++) {
        drawCard(deck, deckSize, p);
    }
}

void dealCards(card* deck, int* deckSize, player players[], int playerCount, int cards) {
    for (int i = 0; i < cards; i++) {
        for (int j = 0; j < playerCount; j++) {
            if (drawCard(deck, deckSize, &players[j]) == 0) return;
        }
    }
}

// Recursively free deck
void freeDeck(card* p, int deckSize) {
    if (p->listp && deckSize > 1) {
        freeDeck(p->listp, deckSize - 1);
        p->listp = NULL;
    }
    free(p);
}