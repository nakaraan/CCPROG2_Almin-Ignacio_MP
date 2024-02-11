#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printMainMenu()
{
    printf("Welcome to MineSweeper!\n");
    printf("1. Start Game\n");
    printf("2. Create Level\n");
    printf("3. Change Profile\n");
    printf("4. View Statistics\n");
    printf("5. Quit\n");
}

int main()
{
    int mainMenuChoice;
    int menuStatus = 1, gameStatus = 0; // 0 = not started, 1 = in progress
    char ClassicOrCustom[10];

    while (menuStatus == 1)
    {
        printMainMenu();
        scanf("%d", &mainMenuChoice);

        switch (mainMenuChoice) //MOVE TO NEW FUNCTION
        {
        case 1:
            gameStatus = 1;
            printf("Classic or Custom?");
            scanf("%s", ClassicOrCustom);

            if (strcmp(ClassicOrCustom, "Classic") == 0) // strcmp returns 0 if the str ClassicOrCustom is equal to "Classic"
            {
                printf("Starting game...\n");
            }
            else if (strcmp(ClassicOrCustom, "Custom") == 0) // strcmp returns 0 if the str ClassicOrCustom is equal to "Custom"
            {
                printf("Creating level...\n");
            }
            else // if the user enters anything other than "Classic" or "Custom"
            {
                printf("Invalid choice. Please try again.\n");
            }

            break;
        case 2:
            printf("Creating level...\n");
            break;
        case 3:
            printf("Changing profile...\n");
            break;
        case 4:
            printf("Viewing statistics...\n");
            break;
        case 5:
            printf("Quitting...\n");
            menuStatus = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}