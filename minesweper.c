#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef char string20[21];
typedef char string5[6];

struct cellTag  //hi
{
    char Blank; //Will be initialized as '.'
    char Value; //Will contain either an 'X' for a mine or a '.' for a blank cell w/o adjacent mines
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

struct GameProfile  // 
{
    char mode;  // 
    string5 result; // WIN/LOSE/QUIT
};

int main()
{
    char cMenuOption;   //character denoting user menu choice
    int menuStatus = 1, gameStatus = 0; // 0 = not started, 1 = in progress
    char ClassicOrCustom[10];

    printf("[TITLE TEXT]\n\n"); // replace with ASCII code "MINESWEEPER (in c99!)"

    printf("[P] Start Game\t[L] Create Level\t[P] Change Profile\t[V] View Statistics\n");
    printf("Select an option: ");
    
    

    
}