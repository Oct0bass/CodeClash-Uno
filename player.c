#include <stdbool.h>
#include <stdio.h>

#include "player.h"
#include "card.h"
#include "deck.h"
#include "config.h"

void playCard(player* player, card* discard, int* discardSize, int n) {
    appendCard(discard, discardSize, removeCard(&player->deck, &player->deckSize, n));
}

void printPlayer(player player) {
    printf("%s's hand:\n\n", player.name);
    int i = 0;
    for (card* p = player.deck; p && i < player.deckSize; p = p->listp, i++) { 
        printCard(*p);
    }
    puts("");
}

bool checkValidCards(player player, card topCard) {
    int i = 0;
    int validCards = 0;
    for (card* p = player.deck; p && i < player.deckSize; p = p->listp, i++) {
        if (isValidCard(*p, topCard)) validCards++;
    }
    if (validCards == 0) {
        printf("%s has no card that matches %s or %c\n", player.name, colorName(topCard), topCard.name);
        return false;
    }
    return true;
}

int makeSelection(player player, card topCard) {
    char chosenCardName[20];
    char topCardName[20];
    if (player.computer == false) {
        int choice;
        while (true) {
            if (topCard.color == 'S' && topCard.name == 'A') {
                printf("%s, enter which card to play with AND from 0 to %d: ", player.name, player.deckSize - 1);
            } else if (topCard.color == 'S' && topCard.name == 'O') { 
                printf("%s, enter which card to play with OR from 0 to %d: ", player.name, player.deckSize - 1);
            } else printf("%s, enter which card to play from 0 to %d: ", player.name, player.deckSize - 1);
            scanf("%d", &choice);
            if (choice < 0 || choice >= player.deckSize) {
                printf("Invalid choice, %s does not have %d cards\n", player.name, choice + 1);
            } else {
                card chosenCard = *getCard(player.deck, choice);
                if (topCard.name != '\0' && !isValidCard(chosenCard, topCard)) {
                    if (topCard.color == 'S') printf("Cannot place two special cards in a row\n");
                    else printf("Invalid choice, cannot place %s on top of %s\n", 
                        cardName(chosenCard, chosenCardName, sizeof chosenCardName), 
                        cardName(topCard, topCardName, sizeof topCardName));
                } else break;
            }
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

