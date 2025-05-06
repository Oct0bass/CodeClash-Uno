#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"
#include "deck.h"
#include "player.h"
#include "util.h"
#include "config.h"

const int maxPlayers = 10;

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

    int discardSize = 1;
    card* discard = popCard(deck, &deckSize);

    player* winner = NULL;
    int currentPlayer = 0;
    int reverseFlag = 1;
    while (winner == NULL) {
        for (int i = 0; i < totalPlayers; i++) {
            printPlayer(players[i]);
        }
        int choice = makeSelection(players[currentPlayer], *lastCard(discard, discardSize));
        playCard(players[currentPlayer], discard, &discardSize, choice);
        currentPlayer = (currentPlayer + reverseFlag) % totalPlayers;
    }
}