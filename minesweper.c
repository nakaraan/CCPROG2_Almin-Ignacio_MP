#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "interface.c"

#define MAX_BOARD_ROW 10
#define MAX_BOARD_COL 15
#define MAX_BOMBS_HARD 35 //max of 35 mines in hard difficulty
#define MAX_BOMBS_EASY 10 //max of 10 mines in easy difficulty

typedef char string20[21]; //string of 20 characters

struct cellTag  //struct for each cell in the game board
{
    char Symbol; //Will be initialized as '.'
    int Value; //0 = empty, 1 = bomb
    int AdjacentBombs; //Special case for a blank cell with adjacent mines
};

struct profileTag   //maximum of 10
{
    string20 playerName;    //must be unique, name must be valid
    int gamesWonN;   //number of games won (normal mode)
    int gamesLostN;
    int gamesWonC;  //number of games lost
    int gamesLostC;
};

struct GameProfile  //struct for 3 most recent games
{
    char mode;  // 
    int result; //0 = lose; 1 = win; 2 = quit
};

/* displayBoard is a function that displays the game board.

    @param board - the current game board
    @param row   - the number of rows in the game board
    @param col   - the number of columns in the game board

    Precondition: The game board must be created.
*/

void displayBoard(struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int row, int col)
{
    int i, j;
    printf(" ");
    //prints the column numbers
    for(i = 0; i < col; i++)
    {
        printf("%3d", i);
    }
    printf("\n");

    for (i = 0; i < row; i++)
    {
        printf("%d", i);    //prints the row numbers
        for (j = 0; j < col; j++)
        {
            if (board[i][j].Symbol != '.' && board[i][j].Symbol != ' ')
            {
                if(board[i][j].Symbol == '1' || board[i][j].Symbol == '2')
                {
                    iSetColor(I_COLOR_CYAN);
                }
                else if(board[i][j].Symbol == '3' || board[i][j].Symbol == '4')
                {
                    iSetColor(I_COLOR_GREEN);
                    
                }
                else if(board[i][j].Symbol == '5' || board[i][j].Symbol == '6')
                {
                    iSetColor(I_COLOR_YELLOW);
                }
                else
                {
                    iSetColor(I_COLOR_RED);
                }
            }
            else
            {
                iSetColor(I_COLOR_WHITE);
            }
            printf("%3c", board[i][j].Symbol);
        }
        printf("\n");
    }
    
    /* DEBUGGING
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%2d", board[i][j].Value);
        }
        printf("\n");
    }
    */
}

/* createBoard is a function that creates the game board. 
    It initializes all cells to '.' and randomly places bombs on the board.

    @param board - the current game board
    @param row   - the number of rows in the game board
    @param col   - the number of columns in the game board
    @param bombs - the number of bombs to be placed on the board

    Precondition: The number of bombs must be less than the number of cells on the board.
*/

void createBoard(struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int row, int col, int bombs, char mode[10])
{
    int i, j;
    int randomRow, randomCol;

    //for loop to initialize all cell displays to '.'
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            board[i][j].Symbol = '.';
            board[i][j].Value = 0;
            board[i][j].AdjacentBombs = 0;
        }
    }
    
    if (strcmp(mode, "CLASSIC") == 0)
    {
        //for loop that randomly places bombs (USED INTERNET FOR REFERENCE ON HOW TO DO THIS)
        for (i = 0; i < bombs; i++)
        {
            randomRow = rand() % row;
            randomCol = rand() % col;
            if (board[randomRow][randomCol].Value == 0)
            {
                board[randomRow][randomCol].Value = 1;
            }
            else
            {
                i--;
            }
        }
    }
    else
    {
        //CUSTOM MODE
    }
    
}

/*  InspectBombs is a function that inspects a cell. 
    It first checks for a bomb in the current cell but if there is none, 
    it inspects the 3x3 grid around the cell and returns the number of bombs in the grid.

    @param board - the current game board
    @param row   - the number of rows in the game board
    @param col   - the number of columns in the game board
    @param x     - the x-coordinate of the cell
    @param y     - the y-coordinate of the cell

    @return -1          (if the cell contains a bomb)
    @return count       (if the cell does not contain a bomb)

    Precondition: The cell must be within the bounds of the game board.
*/

int InspectBombs (struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int row, int col, int x, int y)
{
    int i, j;
    int yCount = y - 1, xCount = x - 1;
    int count = 0;

    if (board[y][x].Value == 1) //if the cell contains a bomb
    {
        return -1;              //return -1 to indicate that the player has lost
    }
    else
    {
        //nested for loop that inspects the 3x3 grid around the cell
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (board[yCount][xCount].Value == 1) //if the cell contains a bomb 
                {
                    count++; //increment count
                }
                xCount++; //increment xCount to go through the current row
            }
            yCount++; //increment yCount to go through the current column
        }
        
        /*
        if (count == 0)
        {
            //ADD EITHER RECURSION OR NEW CODE TO CHECK SIDE BY SIDE AND UP AND DOWN
        }
        */
       
        return count;
    }
}

/* PlaceFlag is a function that places a flag on a cell.

    @param board - the current game board
    @param x     - the x-coordinate of the cell
    @param y     - the y-coordinate of the cell

    Precondition: The cell must be within the bounds of the game board.
                : The cell must not already contain a flag.
                : The cell has not been inspected.
*/

void PlaceFlag (struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int x, int y)
{
    board[y][x].Symbol = 'F';
}

void revealMines (struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int row, int col)
{
    int i, j;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (board[i][j].Value == 1)
            {
                board[i][j].Symbol = '*';
            }
        }
    }
}

/* scanCustom is a function that scans a given custom level .txt file

*/
int scanCustom (struct cellTag board[MAX_BOARD_ROW][MAX_BOARD_COL], int row, int col)
{
    int i, j;
    int count = 0;
    char input;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            scanf("%c", &input);
            if (input == 'X')
            {
                board[i][j].Value = 1;
                count++;
            }
            else
            {
                board[i][j].Value = 0;
            }
        }
    }

    return count;
}

int main()
{
    //GAME STATUS VARIABLES (0 = not started/done, 1 = in progress)
    int menuStatus = 1;         //initializes to 1 to start and loop menu
    int gameStatus = 0;         //intialized as 0 but will be intialized as 1 when game starts
    int levelCreateStatus = 0;  //intialized as 0 but will be intialized as 1 when level creation starts

    //CHOICE VARIABLES
    char cMenuOption;           //character denoting user menu choice
    char ClassicOrCustom[10];   //string denoting user choice of classic or custom game
    char EasyOrHard;            //[E] or [H] | character denoting user choice of easy or hard difficulty
    char InspectOrFlag;         //[I] or [F] | character denoting the choice to either inspect or place a flag

    //BOARD VARIABLES
    struct cellTag gameBoard[MAX_BOARD_ROW][MAX_BOARD_COL];     //game board
    int rowSize = 0, colSize = 0, numberOfBombs = 0;            //initializes 0 to not input garbage values
    int x, y;                                                   //coordinates for user input

    do
    {
    //TITLE ART
    iSetColor(I_COLOR_RED);
    printf(" __   __  ___   __    _  _______  _______  _     _  _______  _______  _______  _______  ______   \n");
    printf("|  |_|  ||   | |  |  | ||       ||       || | _ | ||       ||       ||       ||       ||    _ |  \n");
    iSetColor(I_COLOR_YELLOW);
    printf("|       ||   | |   |_| ||    ___||  _____|| || || ||    ___||    ___||    _  ||    ___||   | ||  \n");
    iSetColor(I_COLOR_GREEN);
    printf("|       ||   | |       ||   |___ | |_____ |       ||   |___ |   |___ |   |_| ||   |___ |   |_||_ \n");
    iSetColor(I_COLOR_CYAN);
    printf("|       ||   | |  _    ||    ___||_____  ||       ||    ___||    ___||    ___||    ___||    __  | \n");
    iSetColor(I_COLOR_BLUE);
    printf("| ||_|| ||   | | | |   ||   |___  _____| ||   _   ||   |___ |   |___ |   |    |   |___ |   |  | |\n");
    iSetColor(I_COLOR_PURPLE);
    printf("|_|   |_||___| |_|  |__||_______||_______||__| |__||_______||_______||___|    |_______||___|  |_|\n\n");

    iSetColor(I_COLOR_WHITE);

    //MENU LOOP
    printf("[P] Start Game          [L] Create Level\n");
    printf("[C] Change Profile\t[V] View Statistics\n");
    printf("\nSelect an option: ");
    scanf("%c", &cMenuOption);

    switch (cMenuOption)
    {
        case 'P':
        
        system("clear"); //clears the screen
        iSetColor(I_COLOR_PURPLE);
        printf("!!!TIMER START!!!\n");

        //ADD TIMER FUNCTION

        menuStatus = 0; //exits menu loop
        gameStatus = 1; //starts game loop

        iSetColor(I_COLOR_BLUE);    
        printf("[CLASSIC] "); 
        iSetColor(I_COLOR_WHITE);   
        printf("or ");
        iSetColor(I_COLOR_YELLOW);  
        printf("[CUSTOM]?\n");
        iSetColor(I_COLOR_WHITE);
        scanf("%s", ClassicOrCustom);

        system("clear"); //clears the screen

        if (strcmp(ClassicOrCustom, "CLASSIC") == 0)
        {
            while (rowSize == 0 || colSize == 0 || numberOfBombs == 0) //while loop to ensure user inputs valid values
            {
            
            iSetColor(I_COLOR_GREEN);
            printf("[E] Easy "); 
            iSetColor(I_COLOR_WHITE);
            printf("or ");
            iSetColor(I_COLOR_RED);
            printf("[H] Hard?\n");
            iSetColor(I_COLOR_WHITE);
            scanf(" %c", &EasyOrHard);

            system("clear"); //clears the screen

            switch (EasyOrHard)
            {
                case 'E':
                //initializes variables for easy difficulty
                rowSize = 8;
                colSize = 8;
                numberOfBombs = 10;

                //function call to create board
                createBoard(gameBoard, rowSize, colSize, numberOfBombs, ClassicOrCustom);

                do {
                displayBoard(gameBoard, rowSize, colSize);

                printf("\nInput [x] coordinate: ");
                scanf("%d", &x);

                printf("Input [y] coordinate: ");
                scanf("%d", &y);
                
                printf("\n[I] Inspect or [F] Flag?\n");
                scanf(" %c", &InspectOrFlag);

                InspectBombs(gameBoard, rowSize, colSize, x, y);

                if (InspectOrFlag == 'I')
                {
                    if (InspectBombs(gameBoard, rowSize, colSize, x, y) == -1)
                    {
                        system("clear");
                        printf("You lose :(\n");
    
                        //Reveals all mines on the board
                        revealMines(gameBoard, rowSize, colSize);
                        displayBoard(gameBoard, rowSize, colSize);

                        //Resets game status and menu status
                        gameStatus = 0;
                        menuStatus = 1;
                    }
                    else
                    {
                        if (InspectBombs(gameBoard, rowSize, colSize, x, y) == 0)
                        {
                            gameBoard[y][x].Symbol = ' ';
                            
                        }
                        else
                        {
                        gameBoard[y][x].Symbol = InspectBombs(gameBoard, rowSize, colSize, x, y) + '0'; //converts int to char
                        }
                        displayBoard(gameBoard, rowSize, colSize);
                    }
                }
                else if (InspectOrFlag == 'F' && gameBoard[y][x].Symbol == '.')
                {
                    PlaceFlag(gameBoard, x, y);
                    displayBoard(gameBoard, rowSize, colSize);
                }
                else
                {
                    printf("Invalid option. Please try again.\n");
                    //ADD A DELAY TIMER
                    //SUBTRACT THE DELAY TIME FROM THE CURRENT TIMER
                }

                system("clear"); //clears the screen

                } while (gameStatus == 1);

                break;

                case 'H':
                rowSize = 10;
                colSize = 15;
                numberOfBombs = 35;

                //function call to create board
                createBoard(gameBoard, rowSize, colSize, numberOfBombs, ClassicOrCustom);

                do {
                displayBoard(gameBoard, rowSize, colSize);

                printf("\nInput [x] coordinate: ");
                scanf("%d", &x);

                printf("Input [y] coordinate: ");
                scanf("%d", &y);
                
                printf("\n[I] Inspect or [F] Flag?\n");
                scanf(" %c", &InspectOrFlag);

                InspectBombs(gameBoard, rowSize, colSize, x, y);

                if (InspectOrFlag == 'I')
                {
                    if (InspectBombs(gameBoard, rowSize, colSize, x, y) == -1)
                    {
                        system("clear");
                        printf("You lose :(\n");
    
                        //Reveals all mines on the board
                        revealMines(gameBoard, rowSize, colSize);
                        displayBoard(gameBoard, rowSize, colSize);

                        //Resets game status and menu status
                        gameStatus = 0;
                        menuStatus = 1;
                    }
                    else
                    {
                        if (InspectBombs(gameBoard, rowSize, colSize, x, y) == 0)
                        {
                            gameBoard[y][x].Symbol = ' ';
                            
                        }
                        else
                        {
                        gameBoard[y][x].Symbol = InspectBombs(gameBoard, rowSize, colSize, x, y) + '0'; //converts int to char
                        }
                        displayBoard(gameBoard, rowSize, colSize);
                    }
                }
                else if (InspectOrFlag == 'F' && gameBoard[y][x].Symbol == '.')
                {
                    PlaceFlag(gameBoard, x, y);
                    displayBoard(gameBoard, rowSize, colSize);
                }
                else
                {
                    printf("Invalid option. Please try again.\n");
                    //ADD A DELAY TIMER
                    //SUBTRACT THE DELAY TIME FROM THE CURRENT TIMER
                }

                system("clear"); //clears the screen

                } while (gameStatus == 1);

                break;

                default:
                printf("Invalid option. Please try again.\n");

                break;
            }
            
            }
        }
        else if (strcmp(ClassicOrCustom, "CUSTOM") == 0)
        {
            scanf("%d %d", &rowSize, &colSize);

            //assigns the values of the custom board to the board
            scanCustom(gameBoard, rowSize, colSize);
            numberOfBombs = scanCustom(gameBoard, rowSize, colSize);

            //generates the custom board
            createBoard(gameBoard, rowSize, colSize, numberOfBombs, ClassicOrCustom);

            do {
                displayBoard(gameBoard, rowSize, colSize);

                printf("\nInput [x] coordinate: ");
                scanf("%d", &x);

                printf("Input [y] coordinate: ");
                scanf("%d", &y);
                
                printf("\n[I] Inspect or [F] Flag?\n");
                scanf(" %c", &InspectOrFlag);

                InspectBombs(gameBoard, rowSize, colSize, x, y);

                if (InspectOrFlag == 'I')
                {
                    if (InspectBombs(gameBoard, rowSize, colSize, x, y) == -1)
                    {
                        system("clear");
                        printf("You lose :(\n");
    
                        //Reveals all mines on the board
                        revealMines(gameBoard, rowSize, colSize);
                        displayBoard(gameBoard, rowSize, colSize);

                        //Resets game status and menu status
                        gameStatus = 0;
                        menuStatus = 1;
                    }
                    else
                    {
                        if (InspectBombs(gameBoard, rowSize, colSize, x, y) == 0)
                        {
                            gameBoard[y][x].Symbol = ' ';
                            
                        }
                        else
                        {
                        gameBoard[y][x].Symbol = InspectBombs(gameBoard, rowSize, colSize, x, y) + '0'; //converts int to char
                        }
                        displayBoard(gameBoard, rowSize, colSize);
                    }
                }
                else if (InspectOrFlag == 'F' && gameBoard[y][x].Symbol == '.')
                {
                    PlaceFlag(gameBoard, x, y);
                    displayBoard(gameBoard, rowSize, colSize);
                }
                else
                {
                    printf("Invalid option. Please try again.\n");
                    //ADD A DELAY TIMER
                    //SUBTRACT THE DELAY TIME FROM THE CURRENT TIMER
                }

                system("clear"); //clears the screen

                } while (gameStatus == 1);
            
            
        }
        else
        {
            printf("Invalid option. Please try again.\n");
        }
        break;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        case 'L':
        printf("Creating level...\n"); //REPLACE WITH ACTUAL LEVEL CREATION FUNCTION
        levelCreateStatus = 1;
        break;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        case 'C':
        printf("Changing profile...\n"); //REPLACE WITH ACTUAL PROFILE CHANGE FUNCTION
        //changeProfile(VARIABLES); //ADD function to change profile
        break;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        case 'V':
        printf("Viewing statistics...\n"); //REPLACE WITH ACTUAL STATISTICS FUNCTION
        //viewStatistics(VARIABLES); //ADD function to call files and display statistics
        break;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        default:
        printf("Invalid option. Please try again.\n");

        //system("clear"); //clears the screen
        break;
    }
    } while (menuStatus == 1);
    
    

    
}