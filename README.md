# Compiling and Running

In the root directory (the same one as this file), run:
```bash
cc -Wall card.c deck.c player.c game.c util.c -o game
```
replacing `cc` with your compiler of choice.
Run with `./game`

# Configuration

In the file `config.h` there are options that can be configured at compile time.  Currently the options supported are:
 - `COLOR`: If defined, print the cards in color with ANSI escape codes.

 There may be other options in the file that are not supported.  I am not responsible for what happens if you change these options.