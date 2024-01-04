@author Maria Chrysanthou   ID: 1123114

This is the game of the Three Musketeers.

How to play:

Open the command line terminal, and compile the threeMusketeers.c file with this command:
gcc threeMusketeers.c -o threeMusketeers
Then, run it with the intial text file which contains the starting state of the board, eg "input.txt":
./threeMusketeers.c input.txt

Game Rules: 

There are two opposing teams, the three Musketeers and the enemies.
One player takes the part of the three musketeers, the other of Cardinal Richelieu's men ("the enemy").
The Musketeer can move to any adjacent square (non-diagonal) where an enemy (Cardinal Richelieu's men) is located. 
After this move, the enemy piece is removed from the game.
The enemy can move a piece to any adjacent empty square.
The enemy wins if they can force all three Musketeers to be in the same row or column.
The Musketeers win if, in turn, they can't move due to the absence of enemy pieces in the neighboring squares of each Musketeer,
and they are not all in the same row or column. 
As long as a Musketeer can move, the game is not over.

How to pause/restart a game:

The user can terminate the game with the command: "0,0=E",
which will then save the current state of the game board in an output
file. To start a game from how it was last displayed, the user instead of
using the initial starting file, can use the output file, eg "out-input.txt":
./threeMusketeers.c out-input.txt
