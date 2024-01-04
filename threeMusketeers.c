/**
 * @file threeMusketeers.c
 * @brief This program implements the game three Musketeers by creating a board and reading the inputs from
 * a file of the user's choice. Once the game starts the user is asked to insert their move starting off by
 * the three Musketeers. The game continuous until there is a winner, either by the enemies/Cardinal Richelieu's 
 * men, or the three Musketeers. The game can be interrupted manually but the board always gets saved in
 * another file, in case the user wants to restart the same game next time.
 * @author Maria Chrysanthou
 * @bug no known bugs
 * 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 5

/**
 * @brief Reads the contents of a specified file and uses it to
 * initialize the game board represented as a 2D character array. It checks
 * the validity of the input and ensures the proper dimensions of the board.
 * @param board the 2D array representing the game board.
 * @param filename the name of the file from which to read the game board.
 * @return 1 if reading the board works successfully, 0 if it fails.
*/
int readBoard (char board[][N], char filename[]);

/**
 * @brief Writes and saves the current game state, represented by the 2D array, 
 * to the specified file. It creates a text file containing the board layout and 
 * allows you to save your progress and continue the game later.
 * @param board the 2D array representing the game board.
 * @param filename the name of the file from which to write the game board.
 * @return 1 if writing the board works successfully, 0 if it fails.
*/
int writeBoard(char board[][N], char filename[]);

/**
 * @brief Prints the current state of the game board to the console,
 * providing a visual representation of the game board to the players.
 * @param board the 2D array representing the game board.
*/
void display_board(char board[][N]);

/**
 * @brief This function basically initiates and controlls the game. 
 * It takes user input for moves and keeps going in a loop until 
 * someone from either teams has won.
 * @param board the 2D array representing the game board.
*/
void play(char board[][N], char outfile[]);

/**
 * @brief Checks and validates whether a move is within the 
 * boundaries of the game board in general and follows
 * a valid direction (L/l, R/r, U/u, D/d).
 * @param row The row where the move is initiated.
 * @param col The column where the move is initiated.
 * @param direction The direction of the move (L/l, R/r, U/u, D/d).
 * @param board the 2D array representing the game board.
 * @return 1 if the move is valid, 0 if it is not.
*/
int isValidMove (int row, int col, char direction, char board[][N]);

/**
 * @brief This function specifically validates moves 
 * for the Musketeer player, ensuring that they only 
 * move in valid directions and that there is a 
 * Musketeer there at all.
 * @param row The row where the move is initiated.
 * @param col The column where the move is initiated.
 * @param direction The direction of the move (L/l, R/r, U/u, D/d).
 * @param board the 2D array representing the game board.
 * @return 1 if the move is valid for a Musketeer, 0 if it is not.
*/
int isValidMusketeerMove(int row, int col, char direction, char board[][N]);

/**
 * @brief  This function specifically validates moves 
 * for the enemies player, ensuring that they only 
 * move in valid directions and that there are 
 * enemies in the specific moves they ask for.
 * @param row The row where the move is initiated.
 * @param col The column where the move is initiated.
 * @param direction The direction of the move (L/l, R/r, U/u, D/d).
 * @param board the 2D array representing the game board.
 * @return 1 if the move is valid for an enemy, 0 if it is not.
*/
int isValidEnemyMove(int row, int col, char direction, char board[][N]);

/**
 * @brief This function applies a valid move to the game board 
 * based on the coordinates and direction as well as whose
 * turn it is (Musketeer or enemy).
 * @param row The row where the move is initiated.
 * @param col The column where the move is initiated.
 * @param direction The direction of the move (L/l, R/r, U/u, D/d).
 * @param board the 2D array representing the game board.
 * @param mTurn A flag indicating whose turn it is (1 for Musketeers, 0 for enemies).
*/
void makeMove(int row, int col, char direction, char board[][N], int mTurn);

/**
 * @brief This function is called when the user inputs a 
 * specific command to interrupt the game. It saves 
 * the current game state to a file by calling the
 * writeBoard function, for later resumption.
 * @param board the 2D array representing the game board.
*/
void gameInterrupt (char board[][N], char outfile[]);

/**
 * @brief determines the game's outcome by checking if
 * either the Musketeers or the enemies have won the 
 * game based on the current game board.
 * @param board the 2D array representing the game board.
 * @return 1 if any opposing team has won, 0 if none have won.
*/
int winGame(char board[][N]);

/**
 * @brief checks for victory conditions for the Musketeer 
 * team, ensuring that the enemies cannot capture all Musketeers,
 * based on the current game board. 
 * @param board the 2D array representing the game board.
 * @return 1 if the Musketeers have won, 0 if they have not.
*/
int winMusketeers(char board[][N]);

/**
 * @brief This function checks for victory conditions 
 * for the enemy team, such as having all three Musketeers 
 * in the same row or column, based on the current game board.
 * @param board the 2D array representing the game board.
 * @return 1 if the enemies have won, 0 if they have not.
*/
int winEnemies(char board[][N]);

/**
 * @brief reads the user file input and proceeds to play the game
 * while doing the appropriate checks for errors
 * @param argc
 * @param argv
 * @return 0 if the program is done running 
*/
int main (int argc, char *argv[]){
    char board[N][N];
    // const char* filename;                           // input file
   // const char* outputFile = "out-inputfile.txt";   // output file
    
    readBoard(board, argv[1]);

    // read the board and print an error message if it fails
    if (!readBoard(board, argv[1])){
        printf("Failed to read the board from the file.\n");
        return 0;
    }

    play(board, argv[1]);

    return 0;
}

// Reads the board from a given file
int readBoard (char board[][N], char filename[]){
    FILE* file = fopen(filename, "r");

    if (file == NULL){
        printf("Error opening the file: %s\n", filename);
        return 0;
    }

    int i,k;
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++){
            int ch = fgetc(file);

            if (ch == EOF || ch != 'o' && ch != 'M' && ch != '\n' && ch != ' ' && ch != '.'){
                printf("Invalid character in the input file\n");
                fclose(file);
                return 0;
            }

            if (ch != '\n' && ch != ' ')
                board[i][k] = (char)ch;
            else
                k--;
        }

    fclose(file);
    return 1;
}

// Saves the current game state to a file
int writeBoard(char board[][N], char filename[]) {
    char outputfile[30] = "out-";
    char *p;
    p = strcat(outputfile, filename);
    FILE *file = fopen(outputfile, "w+");

    if (file == NULL){
        printf("Error opening the saved file: %s\n", filename);
        return 0;
    }

    int i,k;
    for (i = 0; i < N; i++){
        for (k = 0; k < N; k++){
            fputc(board[i][k], file);

             // Add a space after each character except the last in a row
            if (k < N - 1) 
                fputc(' ', file);
        }
        fputc('\n', file);
     }
    fclose(file);
    printf("Saving %s...Done.\nAu revoir!\n\n", outputfile);
    return 1;
}

// Function to display the game board
void display_board(char board[][N]) {
    printf("\n    1   2   3   4   5\n");
    printf("  +---+---+---+---+---+\n");

    int i, k;
    for (i = 0; i < N; i++) {
        printf("%c |", 'A' + i);            // increase the index of A for each row

        for (k = 0; k < N; k++) {
            printf(" %c |", board[i][k]);
        }
        
        printf("\n");
        printf("  +---+---+---+---+---+\n");
    }
}

// play the game
void play (char board[][N], char outfile[]){

    int   row, col, musketeersTurn = 1; // musketeers turn = 1, enemies turn = 0
    char direction;
    char *playerMove = (char *) malloc(11 * sizeof(char));  // declare the player move parameter and allocate memory

    // Printing the intro message needed for the instructions of the game
    printf("*** The Three Musketeers Game ***\nTo make a move, enter the location of the piece you want to move,\nand the direction you want it to move. Locations are indicated as\na letter (A, B, C, D, E) followed by a nnumber (1, 2, 3, 4, or 5).\nDirections are indicated as left, right, up, down (L/l, R/r, U/u, D/d).\nFor example, to move the Musketeer from the top right-hand corner\nto the row below, enter 'A,5 = L' or 'a,5=l'(without quotes).\nFor convenience in typing, use lowercase letters.\n\n");

    display_board(board);                                   // display the current board

    while (!winGame(board)){

        if (musketeersTurn){
            printf("\nGive the Musketeer's move\n>");
            fgets(playerMove, sizeof(playerMove), stdin);           // read the player move as a string
        }
        else {
            printf("\nGive the enemy's move\n>");
            fgets(playerMove, sizeof(playerMove), stdin);           // read the player move as a string
        }

        if ((strcmp(playerMove, "0,0=E\n") == 0) || (strcmp(playerMove, "0,0=e\n") == 0)) {               // if the game is interrupted
            // User wants to quit the game
            printf("\nGame interrupted. Exiting...\n");
            gameInterrupt(board, outfile);
            break;
        }

        // Parse the move input
        if ((sscanf(playerMove, " %c,%c=%c", (char*)&row, (char*)&col, &direction) == 3) || (sscanf(playerMove, " %c,%c = %c", (char*)&row, (char*)&col, &direction) == 3)) {
            row = tolower(playerMove[0]) - 'a';  // Convert row to index (0-4)
            col = playerMove[2] - '1';           // Convert col to index (0-4)
            
            if (musketeersTurn){
                if (isValidMusketeerMove(row, col, direction, board)){ 
                    makeMove(row, col, direction, board, musketeersTurn);
                    musketeersTurn = !musketeersTurn;
                    display_board(board);
                }
            }
            else{
                if (isValidEnemyMove(row, col, direction, board)) {
                    makeMove(row, col, direction, board, musketeersTurn);
                    musketeersTurn = !musketeersTurn;
                    display_board(board);
                }
            }
        }
        else {
            printf("Invalid input format. Use i,j=value (e.g., A,5=L).\n");
        }
    }

    if (winMusketeers(board)){
        printf("\nThe Musketeers win!\n\n");
        gameInterrupt(board, outfile);
    }

    else if (winEnemies(board)){
        printf("\nCardinal Richelieu's men win!\n\n");
        gameInterrupt(board, outfile);
    }
}   

// make sure the move the user has inserted is valid
int isValidMove (int row, int col, char direction, char board[][N]){
    int cnt = 0;

        if (row >= 0 && row < N && col >= 0 && col < N) {
              if (direction == 'L' || direction == 'l' || direction == 'R' || direction == 'r' ||
                    direction == 'U' || direction == 'u' || direction == 'D' || direction == 'd')
                    // Valid move, apply it to the board
                    cnt++;
              else 
                    printf("Invalid direction. Use L/l, R/r, U/u, or D/d.\n");
        }
        else 
              printf("\nThis move gets out of the board or is a wrong move.\n");  
    
    if (cnt > 0)
        return 1;
    return 0;
}

int isValidMusketeerMove(int row, int col, char direction, char board[][N]){
    int cnt = 0;

    if (isValidMove(row, col, direction, board)){
        if ((board[row][col] == 'M') && (board[row-1][col] == 'o') && ((direction == 'U') || (direction == 'u')) && (row > 0))
            cnt++;
        if ((board[row][col] == 'M') && (board[row+1][col] == 'o') && ((direction == 'D') || (direction == 'd')) && (row < N-1))
            cnt++;
        if ((board[row][col] == 'M') && (board[row][col-1] == 'o') && ((direction == 'L') || (direction == 'l')) && (col > 0))
            cnt++;
        if ((board[row][col] == 'M') && (board[row][col+1] == 'o') && ((direction == 'R') || (direction == 'r')) && (col < N-1))
            cnt++;
    }

    if (cnt > 0)
        return 1;

    printf("\nNo Musketeers spotted!.\n");
    return 0;
}

int isValidEnemyMove(int row, int col, char direction, char board[][N]){
    int cnt = 0;

    if (isValidMove(row, col, direction, board)){
         if ((board[row][col] == 'o') && (board[row-1][col] == '.') && ((direction == 'U') || (direction == 'u')))
            cnt++;
        if ((board[row][col] == 'o') && (board[row+1][col] == '.') && ((direction == 'D') || (direction == 'd')))
            cnt++;
        if ((board[row][col] == 'o') && (board[row][col-1] == '.') && ((direction == 'L') || (direction == 'l')))
            cnt++;
        if ((board[row][col] == 'o') && (board[row][col+1] == '.') && ((direction == 'R') || (direction == 'r')))
            cnt++;
    }

    if (cnt > 0)
        return 1;

    printf("\nNo enemies spotted!\n");
    return 0;
}

// makes the move given by the user
void makeMove(int row, int col, char direction, char board[][N], int mTurn){
    int newRow, newCol;

    if ((direction == 'l') || (direction == 'L')){
        newRow = row;
        newCol = col - 1;
    }
    else if ((direction == 'r') || (direction == 'R')){
        newRow = row;
        newCol = col + 1;
    }
    else if ((direction == 'u') || (direction == 'U')){
        newRow = row - 1;
        newCol = col;
    }
    else if ((direction == 'd') || (direction == 'D')){
        newRow = row + 1;
        newCol = col;
    }

    board[row][col] = '.';
    if (mTurn)
        board[newRow][newCol] = 'M';
    else
        board[newRow][newCol] = 'o';
}

// used when the user inputs 0,0=E
void gameInterrupt (char board[][N], char outfile[]){

    //const char* outputFile;
    //inputfile.txt";   

    // After the game is interrupted or a winner is determined
    if (!writeBoard(board, outfile)) {
        printf("Failed to save the game state.\n");
    }
}

// returns 1 if the musketeers have won
int winMusketeers(char board[][N]){
    int cnt = 0;

    int i, k;
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++){
            if (board[i][k] == 'M'){
                if((k-1 >= 0) && (board[i][k-1] == 'o'))
                    cnt++;
                if((k+1 < N) && (board[i][k+1] == 'o'))
                    cnt++;
                if((i-1 >= 0) && (board[i-1][k]) == 'o')
                    cnt++;
                if((i+1 < N) && (board[i+1][k] == 'o'))
                    cnt++;
            }
        }

    if (cnt > 0)
        return 0;

    return 1;
}

// returns 1 if the enemies have won
int winEnemies(char board[][N]){

    int i,k;
    // Check if all three Musketeers are in the same row
    for (i = 0; i < N; i++) {
        int mCount = 0;
        for (k = 0; k < N; k++) {
            if (board[i][k] == 'M') 
                mCount++;
        }
        if (mCount == 3) 
            return 1;
    }


    // Check if all three Musketeers are in the same column
    for (k = 0; k < N; k++) {
        int mCount = 0;
        for (i = 0; i < N; i++) {
            if (board[i][k] == 'M')
                mCount++;
        }
        if (mCount == 3) 
            return 1;
    }

    return 0;
}

// returns 1 if any of the opposing teams have won the game
int winGame (char board[][N]){
    if (winMusketeers(board) || winEnemies(board))
        return 1;
    return 0;
}


