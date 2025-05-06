#include <stdio.h>

#include "player.h"
#include "card.h"
#include "deck.h"
#include "config.h"

void playCard(player player, card* discard, int* discardSize, int n) {
    if (isValidCard(*player.deck, *discard)) appendCard(discard, discardSize, getCard(player.deck, n));
}

void printPlayer(player player) {
    printf("%s's hand:\n\n", player.name);
    int i = 0;
    for (card* p = player.deck; p && i < player.deckSize; p = p->listp, i++) { 
        printCard(*p);
    }
}

int makeSelection(player player, card topCard) {
    char chosenCardName[20];
    char topCardName[20];
    if (player.computer == false) {
        int choice;
        while (true) {
            printf("%s, enter which card to play from 0 to %d: ", player.name, player.deckSize - 1);
            scanf("%d", &choice);
            card chosenCard = *getCard(player.deck, choice);
            if (choice < 0 || choice >= player.deckSize) {
                printf("Invalid choice, %s does not have %d cards\n", player.name, choice);
            } else if (!isValidCard(chosenCard, topCard)) {
                printf("Invalid choice, cannot place %s on top of %s", 
                    cardName(chosenCard, chosenCardName, sizeof chosenCardName), 
                    cardName(topCard, topCardName, sizeof topCardName));
            } else break;
        }
        return choice;
    } else {
        #ifdef AI_SMART
        #elif defined(AI_RANDOM)
        card** compatibleCards = calloc(player.deckSize, sizeof(card*));
        int compatibleCardCount = 0;
        int i = 0;
        for (card* p = player.deck; p && i < player.deckSize; p = p->listp, i++) {

        }
        #else
        printf("Error: AI players not supported\n");
        #endif
    }
}

