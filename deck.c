#include <stdlib.h>

#include "card.h"
#include "util.h"

const int shuffleIterations = 10000;

card* CreateDeck() {
    card first;
    card* c = &first;
    //2 0-9 sets of cards of each color
    for (int i = 0; i < 80; i++) {
        c->color = regularColors[i / 20];
        c->name = '0' + i % 10;
        c->listp = malloc(sizeof(card));
        c = c->listp;
    }
    //Special cards
    for (int i = 0; i < 20; i++) {
        c->color = 'S';
        c->name = specialTypes[i / 5];
        c->listp = malloc(sizeof(card));
        c = c->listp;
    }
}

void shuffle(card* p) {
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
        c2->name = tmpName;
        c2->color = tmpColor;
    }
}

//Returns a pointer to the nth card in the list
card* getCard(card* p, int n) {
    for (int i = 0; i < n && p; i++) {
        p = p->listp;
    }
    return p;
}

card* lastCard(card* p) {
    for (; p->listp; p = p->listp);
    return p;
}

//Remove the first card and return it
card* popFront(card** listpp) {
    card* result = *listpp;
    *listpp = (*listpp)->listp;
    return result;
}

//Remove the last card and return it
card* pop(card* p) {
    //Find the penultimate card
    for (; p->listp->listp; p = p->listp);
    card* result = p->listp;
    p->listp = NULL;
    return result;
}

void push(card** listpp, card* new) {
    
}