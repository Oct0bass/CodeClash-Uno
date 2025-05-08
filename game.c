#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"
#include "deck.h"
#include "player.h"
#include "util.h"
#include "config.h"

const int maxPlayers = 10;

bool handleAND(player currentPlayer, card topOfPile) {
    int i = 0;
    for (card* p = currentPlayer.deck; p && i < currentPlayer.deckSize; p = p->listp, i++) {
        if (p->color == topOfPile.color && p->name == topOfPile.name) {
            return true;
        }
    }
    return false;
}

bool handleOR(player currentPlayer, card topOfPile) {
    int i = 0;
    for (card* p = currentPlayer.deck; p && i < currentPlayer.deckSize; p = p->listp, i++) {
        if (p->color == topOfPile.color || p->name == topOfPile.name) {
            return true;
        }
    }
    return false;
}

void handleReverse(int* reverseFlag) {
    *reverseFlag *= -1;
}

//Returns the new current player index
int handleNOT(int currentPlayerIndex, int playerCount, int reverseFlag) {
    return (currentPlayerIndex + reverseFlag) % playerCount;
}

int main(void) {
    char linebuf[4];
    int playerCount;
    printf("Enter number of players: ");
    scanf("%d", &playerCount);
    while (playerCount > maxPlayers) {
        printf("Cannot have more than %d layers\nEnter number of players: ", maxPlayers);
        scanf("%d", &playerCount);
    }
    fgets(linebuf, sizeof linebuf, stdin);
    player players[maxPlayers];
    char ordbuf[20];
    for (int i = 0; i < playerCount; i++) {
        printf("Enter %s player's name: ", ordinal(i + 1, ordbuf, sizeof ordbuf));
        fgets(players[i].name, sizeof players[i].name, stdin);
        strtok(players[i].name, "\n");
        players[i].computer = false;
        players[i].deckSize = 0;
    }
    int totalPlayers = playerCount;
    #if defined(AI_RANDOM) || defined(AI_SMART)
    int maxAIPlayers = maxPlayers - playerCount;
    int aiPlayerCount;
    //TODO: implement
    #endif
    #ifdef DECK_LINKED_LIST
    card first;
    card* deck = &first;
    int deckSize = 1;
    initializeDeck(deck, &deckSize);
    #else
    card deck[100];
    initializeDeck(deck, 100);
    #endif
    shuffleDeck(deck);

    dealCards(deck, &deckSize, players, playerCount, 7);

    int discardSize = 0;
    card* discard = NULL;

    player* winner = NULL;
    player* p;
    int reverseFlag = 1;
    char topCardName[20];
    for (int currentPlayer = 0; winner == NULL; currentPlayer = (currentPlayer + reverseFlag) % totalPlayers) {
        card* topCard = lastCard(discard, discardSize);
        card* secondCard = secondLastCard(discard, discardSize);
        if (topCard) {
            cardName(*topCard, topCardName, sizeof topCardName);
            if (secondCard && secondCard->name == 'A')  {
                printf("Top of pile is %s with AND\n", topCardName);
            } else if (secondCard && secondCard->name == 'O') {
                printf("Top of pile is %s with OR\n", topCardName);
            } else printf("Top of pile is %s\n", topCardName);
        }
        for (int i = 0; i < totalPlayers; i++) {
            printPlayer(players[i]);
        }
        p = &players[currentPlayer];
        if (topCard == NULL) {
            discard = removeCard(&p->deck, &p->deckSize, makeSelection(*p, (card) {'\0', '\0', NULL}));
            discardSize++;
            continue;
        }
        if (secondCard && secondCard->color == 'S') {
            switch (secondCard->name) {
                case 'A':
                if (handleAND(*p, *topCard)) {
                    playCard(p, discard, &discardSize, makeSelection(*p, *topCard));
                    printf("Card Matches, no AND penalty\n");
                } else {
                    printf("%s has no card that matches %s and %d\n", p->name, colorName(*topCard), topCard->name);
                    printf("AND penalty, draw 4\n");
                    drawCards(deck, &deckSize, p, 4);
                }
                break;
                case 'O':
                if (handleOR(*p, *topCard)) {
                    playCard(p, discard, &discardSize, makeSelection(*p, *topCard));
                    printf("Card Matches, no OR penalty\n");
                } else {
                    printf("%s has no card that matches %s or %d\n", p->name, colorName(*topCard), topCard->name);
                    printf("OR penalty, draw 4\n");
                    drawCards(deck, &deckSize, p, 4);
                }
            }
        } else if (topCard->color == 'S') {
            switch (topCard->color) {
                case 'R': handleReverse(&reverseFlag);
                break;
                case 'N': currentPlayer = handleNOT(currentPlayer, playerCount, reverseFlag);
            }
        } else if (checkValidCards(*p, *topCard)) {
            card* choice = removeCard(&p->deck, &p->deckSize, makeSelection(*p, *topCard));
            appendCard(discard, &discardSize, choice);
            if (choice->color == 'S' && (choice->name == 'A' || choice->name == 'O')) {
                playCard(p, discard, &discardSize, makeSelection(*p, *choice));
            }
        } else drawCard(deck, &deckSize, p);
        if (p->deckSize == 0) winner = p;
        if (winner == NULL && deckSize == 0) {
            int minHand = players[0].deckSize;
            for (int i = 0; i < playerCount; i++) {
                if (players[i].deckSize < minHand) {
                    minHand = players[i].deckSize;
                    winner = &players[i];
                }
            }
        }
    }
    freeDeck(deck, deckSize);
    freeDeck(discard, discardSize);
    for (int i = 0; i < playerCount; i++) freeDeck(players[i].deck, players[i].deckSize);
}