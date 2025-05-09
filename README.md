# Code Clash: Uno

This is a card game similar to regular Uno, but with different special cards:
 - **AND**: Player playing this card plays another card, the next player must either play a card of the same number *AND* color, or draw 4
 - **OR**: Like AND, but the following player can play a card with the same color *OR* same number
 - **NOT**: Equivalent to "Skip" in regular Uno
 - **Reverse**: Same as regular Uno
Note: Unlike regular Uno, this special cards do not have colors.

Another key difference is that **all player hands are public**.

## Compiling and Running

In the root directory (the same one as this file), run:
```bash
cc -Wall card.c deck.c player.c game.c util.c -o game
```
replacing `cc` with your compiler of choice.
Run with `./game`

## Configuration

In the file `config.h` there are options that can be configured at compile time.  Currently the options supported are:
 - `COLOR`: If defined, print the cards in color with ANSI escape codes.

 There may be other options in the file that are not supported.  I am not responsible for what happens if you change these options.

 ## Gameplay

 At first, the game will prompt for the number of players.  There cannot be more than 10 players.  Then, the names of each player are entered.
 On each turn, the top pile in the discard, and all the player's hands will be printed.  If the first card under the top is a AND or OR, that will also be printed.
 The player is prompted for which card they want to play.  If they play AND or OR, they are prompted again for which regular card to play on top.
 Play continues until someone runs out of cards, in which they win, or the deck runs out, in which case the player with the least cards wins.

 ## Grading Notes

 The required functions are located in the following files.  Some of the signatures have changed.
 
 `game.c`:
```c
bool handleAND(player currentPlayer, card topOfPile);
bool handleOR(player currentPlayer, card topOfPile);
void handleReverse(int* reverseFlag);
bool handleOR(player currentPlayer, card topOfPile);
```

`card.c`
```c
bool isValidCard(card a , card b);
void printCard(card c);
```

`card.h`: `struct card` definition.

`deck.c`
```c
card* initializeDeck(card* deck, int* deckSize);
void shuffleDeck(card* p);
int drawCard(card* deck, int* deckSize, player* p);
```

`player.c`:
```c
void printPlayer(player player);
```