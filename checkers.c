/*

NAME:          JOHN KALOKI
LOCALITY:      NGONG, KENYA
DATE:          MAY 1,2024
GITHUB:        ActiveElder

This checkers game is played on an 8x8 tile with 12 pieces on side.
Men(the uncrowned pieces) only move and capture diagonally forward.
When there is more than one way for a  player to jump, you may choose
which sequence to make, not necessarilly the sequence that will result
in the greatest number of captures. However, you must make all the
captures in that sequence. Kings can move only one square. It is mandatory
to capture other player pieces if possible.

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int row[2];
int column[2];
char input[10];
int play_count[6];
int choice;
char tile[8][4];
char proceed = 'N';
char selected = 'N';
char moved = 'N';
char more_knocks = 'N';
char player1_name[10];
char player2_name[10];

void reset_board();
void print_board();
void player1();
void player2();
int forced_knock_p1();
int forced_knock_p2();
void forced_move_p1();
void forced_move_p2();
void more_knocks_check();
void choice_processing(int);
void select_piece_p1();
void select_piece_p2();
void move_piece_p1(int);
void move_piece_p2(int);
int check_winner();
void print_winner();

int main()
{
    char play_again = 'Y';
    printf("\n        Player 1 name: ");
    scanf("%[^\n]", player1_name);
    for (int h = 0; h <= strlen(player1_name); h++) // looping while player name is not equal to playername length
    {
        player1_name[h] = toupper(player1_name[h]); // making all player name characters uppercase
    }
    printf("        Player 2 name: ");
    getchar();
    scanf("%[^\n]", player2_name);
    getchar();
    for (int h = 0; h <= strlen(player2_name); h++) // looping while player name is not equal to playername length
    {
        player2_name[h] = toupper(player2_name[h]); // making all player name characters uppercase
    }
    // printing each player pieces
    printf("\n                  PIECE  |  PLAYER");
    printf("\n        -----------------|-----------------------");
    printf("\n                     x   |   %s", player1_name);
    printf("\n                     X   |   %s", player1_name);
    printf("\n                     o   |   %s", player2_name);
    printf("\n                     O   |   %s", player2_name);
    printf("\n        -----------------|-----------------------\n");
    printf("\n        Press enter to continue... ");
    fgets(input, sizeof(input), stdin); // getting any input from player

    while (play_again != 'N')
    {
        int winner = 0;
        for (int i = 0; i < 6; i++)
        {
            play_count[i] = 0;
        }
        reset_board(); // resetting tile
        do
        {
            player1();
            winner = check_winner(); // checking for any winner
            if (winner != 0)
            {
                break; // breaking loop if there's a winner
            }
            player2();
            winner = check_winner();
        } while (winner == 0);

        print_winner(); // prints winner
        printf("\n        Do you want to play again? (Y/N) ");
        scanf("%c", &play_again);
        if (play_again != 'y' && play_again != 'Y')
        {
            play_again = 'N';
        }
        getchar(); // removing new line character
    }
    printf("        Thank you for playing!\n\n");
    return 0;
}

void reset_board()
{
    // resetting all tile values to ' '
    for (int e = 0; e < 8; e++)
    {
        for (int f = 0; f < 4; f++)
        {
            tile[e][f] = ' ';
        }
    }
    // assinging player 1 values
    for (int a = 0; a <= 2; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            tile[a][b] = 'x';
        }
    }
    // assigning player 2 values
    for (int c = 5; c <= 7; c++)
    {
        for (int d = 0; d < 4; d++)
        {
            tile[c][d] = 'o';
        }
    }
}

void print_board()
{
    // prints the entire tile features with updated tiles for player 1
    printf("\n");
    printf("              1   2   3   4   5   6   7   8  \n");
    printf("\n");
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        8   | %c |   | %c |   | %c |   | %c |   |   8\n", tile[7][0], tile[7][1], tile[7][2], tile[7][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        7   |   | %c |   | %c |   | %c |   | %c |   7\n", tile[6][0], tile[6][1], tile[6][2], tile[6][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        6   | %c |   | %c |   | %c |   | %c |   |   6\n", tile[5][0], tile[5][1], tile[5][2], tile[5][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        5   |   | %c |   | %c |   | %c |   | %c |   5\n", tile[4][0], tile[4][1], tile[4][2], tile[4][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        4   | %c |   | %c |   | %c |   | %c |   |   4\n", tile[3][0], tile[3][1], tile[3][2], tile[3][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        3   |   | %c |   | %c |   | %c |   | %c |   3\n", tile[2][0], tile[2][1], tile[2][2], tile[2][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        2   | %c |   | %c |   | %c |   | %c |   |   2\n", tile[1][0], tile[1][1], tile[1][2], tile[1][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("        1   |   | %c |   | %c |   | %c |   | %c |   1\n", tile[0][0], tile[0][1], tile[0][2], tile[0][3]);
    printf("            |---|---|---|---|---|---|---|---|\n");
    printf("\n");
    printf("              1   2   3   4   5   6   7   8  \n");
    printf("\n");
}

void player1()
{
    play_count[5]++;
    printf("\n        -----------------------------------------");
    printf("\n           %s'S TURN           ", player1_name);
    printf("\n        -----------------------------------------\n");

    int knock = forced_knock_p1(); // checking for player knocks before move
    if (knock == 0)
    {
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        do
        {
            do
            {
                printf("        Enter piece row# column# e.g 12: ");
                fgets(input, sizeof(input), stdin); // getting any input
                sscanf(input, "%d", &choice);       // making above input an integer
                choice_processing(0);
                if (proceed == 'N')
                {
                    print_board();
                    printf("        TRY AGAIN, %s\n", player1_name);
                }
            } while (proceed == 'N');
            select_piece_p1(); // calling select_piece_p1 function
            if (selected == 'N')
            {
                print_board();
                printf("        TRY AGAIN, %s\n", player1_name);
            }
        } while (selected == 'N');

        print_board();
        printf("        ***  SELECTED, %s  ***\n", player1_name);
        do
        {
            do
            {
                printf("        Enter target row# column# e.g 12: ");
                fgets(input, sizeof(input), stdin); // allowing player to enter any input
                sscanf(input, "%d", &choice);       // making input an integer
                choice_processing(1);
                if (proceed == 'N')
                {
                    print_board();
                    printf("        TRY AGAIN, %s\n", player1_name);
                }
            } while (proceed == 'N');
            move_piece_p1(0);
            if (moved == 'N')
            {
                print_board();
                printf("        TRY AGAIN, %s\n", player1_name);
            }
        } while (moved == 'N');
    }
    else
        forced_move_p1();
    if (proceed == 'Y')
    {
        more_knocks_check(); // checking for more mandatory knocks if player moved by knock
        do
        {
            if (more_knocks == 'Y')
            {
                if (tile[row[0]][column[0]] == 'X')
                {
                    tile[row[0]][column[0]] = 'S';
                }
                else
                {
                    tile[row[0]][column[0]] = 's';
                }
                print_board();
                printf("        MORE KNOCK(S) AVAILABLE, %s\n", player1_name);
                do
                {
                    printf("        Enter target row# column# e.g 23: ");
                    fgets(input, sizeof(input), stdin);
                    sscanf(input, "%d", &choice); // converting input to integer
                    choice_processing(1);
                    move_piece_p1(0);
                    if (moved != 'Y')
                    {
                        print_board();
                        printf("        TRY AGAIN, %s\n", player1_name);
                    }
                } while (moved == 'N');
            }
            more_knocks_check();
        } while (more_knocks == 'Y');
    }
    print_board();
    printf("        ***  MOVED, %s  ***\n", player1_name);
}

void player2()
{
    printf("\n        -----------------------------------------");
    printf("\n           %s'S TURN           ", player2_name);
    printf("\n        -----------------------------------------\n");

    int knock = forced_knock_p2(); // checking for player knocks before move
    if (knock == 0)
    {
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        do
        {
            do
            {
                printf("        Enter piece row# column# e.g 12: ");
                fgets(input, sizeof(input), stdin); // getting any input
                sscanf(input, "%d", &choice);       // making above input an integer
                choice_processing(0);
                if (proceed == 'N')
                {
                    print_board();
                    printf("        TRY AGAIN, %s\n", player2_name);
                }
            } while (proceed == 'N');
            select_piece_p2(); // calling select_piece_p1 function
            if (selected == 'N')
            {
                print_board();
                printf("        TRY AGAIN, %s\n", player2_name);
            }
        } while (selected == 'N');

        print_board();
        printf("        ***  SELECTED, %s  ***\n", player2_name);
        do
        {
            do
            {
                printf("        Enter target row# column# e.g 12: ");
                fgets(input, sizeof(input), stdin); // allowing player to enter any input
                sscanf(input, "%d", &choice);       // making input an integer
                choice_processing(1);
                if (proceed == 'N')
                {
                    print_board();
                    printf("        TRY AGAIN, %s\n", player2_name);
                }
            } while (proceed == 'N');
            move_piece_p2(0);
            if (moved == 'N')
            {
                print_board();
                printf("        TRY AGAIN, %s\n", player2_name);
            }
        } while (moved == 'N');
    }
    else
        forced_move_p2();
    if (proceed == 'Y')
    {
        more_knocks_check(); // checking for more mandatory knocks if player moved by knock
        do
        {
            if (more_knocks == 'Y')
            {
                if (tile[row[0]][column[0]] == 'O')
                {
                    tile[row[0]][column[0]] = 'S';
                }
                else
                {
                    tile[row[0]][column[0]] = 's';
                }
                print_board();
                printf("        MORE KNOCK(S) AVAILABLE, %s\n", player2_name);
                do
                {
                    printf("        Enter target row# column# e.g 23: ");
                    fgets(input, sizeof(input), stdin);
                    sscanf(input, "%d", &choice); // converting input to integer
                    choice_processing(1);
                    move_piece_p2(0);
                    if (moved != 'Y')
                    {
                        print_board();
                        printf("        TRY AGAIN, %s\n", player2_name);
                    }
                } while (moved == 'N');
            }
            more_knocks_check();
        } while (more_knocks == 'Y');
    }
    print_board();
    printf("        ***  MOVED, %s  ***\n", player2_name);
}

void choice_processing(int num)
{
    // processing player 1 choice
    if (choice == 11 || choice == 13 || choice == 15 || choice == 17 || choice == 22 || choice == 24 || choice == 26 || choice == 28 || choice == 31 || choice == 33 || choice == 35 || choice == 37 || choice == 42 || choice == 44 || choice == 46 || choice == 48)
    {
        proceed = 'N';
    }
    else if (choice == 51 || choice == 53 || choice == 55 || choice == 57 || choice == 62 || choice == 64 || choice == 66 || choice == 68 || choice == 71 || choice == 73 || choice == 75 || choice == 77 || choice == 82 || choice == 84 || choice == 86 || choice == 88)
    {
        proceed = 'N';
    }
    else if (choice >= 12 && choice <= 87)
    {
        // converting choice from 1D to 2D
        row[num] = choice / 10;
        column[num] = choice % 10;

        if (row[num] == 8 || row[num] == 6 || row[num] == 4 || row[num] == 2)
        {
            if (column[num] == 1)
            {
                column[num] = 0;
            }
            else if (column[num] == 3)
            {
                column[num] = 1;
            }
            else if (column[num] == 5)
            {
                column[num] = 2;
            }
            else if (column[num] == 7)
            {
                column[num] = 3;
            }
            row[num] = row[num] - 1;
            proceed = 'Y';
        }
        else if (row[num] == 7 || row[num] == 5 || row[num] == 3 || row[num] == 1)
        {
            if (column[num] == 2)
            {
                column[num] = 0;
            }
            else if (column[num] == 4)
            {
                column[num] = 1;
            }
            else if (column[num] == 6)
            {
                column[num] = 2;
            }
            else if (column[num] == 8)
            {
                column[num] = 3;
            }
            row[num] = row[num] - 1;
            proceed = 'Y';
        }
    }
    else
        proceed = 'N';
}

void select_piece_p1()
{
    selected = 'N';
    // selecting to move up
    if (tile[row[0]][column[0]] == 'x' || tile[row[0]][column[0]] == 'X')
    {
        // moving up without knock
        if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && (tile[row[0] + 1][column[0]] == ' ' || tile[row[0] + 1][column[0]] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == ' ' || tile[row[0] + 1][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && (tile[row[0] + 1][column[0]] == ' ' || tile[row[0] + 1][column[0]] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == ' ' || tile[row[0] + 1][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        // moving up with knock
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'o' || tile[row[0] + 1][column[0] + 1] == 'O') &&
                 (tile[row[0] + 2][column[0] + 1] == ' ' || tile[row[0] + 2][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                 (tile[row[0] + 2][column[0] - 1] == ' ' || tile[row[0] + 2][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                 (tile[row[0] + 2][column[0] + 1] == ' ' || tile[row[0] + 2][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'o' || tile[row[0] + 1][column[0] - 1] == 'O') &&
                 (tile[row[0] + 2][column[0] - 1] == ' ' || tile[row[0] + 2][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'x')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
    }
    if (tile[row[0]][column[0]] == 'X' && selected == 'N')
    {
        // moving down without knock
        if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && (tile[row[0] - 1][column[0]] == ' ' || tile[row[0] - 1][column[0]] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == ' ' || tile[row[0] - 1][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && (tile[row[0] - 1][column[0]] == ' ' || tile[row[0] - 1][column[0]] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == ' ' || tile[row[0] - 1][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        // moving down with knock
        else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'o' || tile[row[0] - 1][column[0] + 1] == 'O') &&
                 (tile[row[0] - 2][column[0] + 1] == ' ' || tile[row[0] - 2][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                 (tile[row[0] - 2][column[0] - 1] == ' ' || tile[row[0] - 2][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                 (tile[row[0] - 2][column[0] + 1] == ' ' || tile[row[0] - 2][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'o' || tile[row[0] - 1][column[0] - 1] == 'O') &&
                 (tile[row[0] - 2][column[0] - 1] == ' ' || tile[row[0] - 2][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
    }
}

void select_piece_p2()
{
    selected = 'N';
    if (tile[row[0]][column[0]] == 'O')
    {
        // moving up without knock
        if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && (tile[row[0] + 1][column[0]] == ' ' || tile[row[0] + 1][column[0]] == '.'))
        {

            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == ' ' || tile[row[0] + 1][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && (tile[row[0] + 1][column[0]] == ' ' || tile[row[0] + 1][column[0]] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == ' ' || tile[row[0] + 1][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        // moving up with knoyk
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'x' || tile[row[0] + 1][column[0] + 1] == 'X') &&
                 (tile[row[0] + 2][column[0] + 1] == ' ' || tile[row[0] + 2][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                 (tile[row[0] + 2][column[0] - 1] == ' ' || tile[row[0] + 2][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                 (tile[row[0] + 2][column[0] + 1] == ' ' || tile[row[0] + 2][column[0] + 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'x' || tile[row[0] + 1][column[0] - 1] == 'X') &&
                 (tile[row[0] + 2][column[0] - 1] == ' ' || tile[row[0] + 2][column[0] - 1] == '.'))
        {
            tile[row[0]][column[0]] = 'S';
            selected = 'Y';
        }
    }
    if ((tile[row[0]][column[0]] == 'o' || tile[row[0]][column[0]] == 'O') && selected == 'N')
    {
        // moving down without knoyk
        if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && (tile[row[0] - 1][column[0]] == ' ' || tile[row[0] - 1][column[0]] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == ' ' || tile[row[0] - 1][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && (tile[row[0] - 1][column[0]] == ' ' || tile[row[0] - 1][column[0]] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == ' ' || tile[row[0] - 1][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        // moving down with knoyk
        else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'x' || tile[row[0] - 1][column[0] + 1] == 'X') &&
                 (tile[row[0] - 2][column[0] + 1] == ' ' || tile[row[0] - 2][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                 (tile[row[0] - 2][column[0] - 1] == ' ' || tile[row[0] - 2][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                 (tile[row[0] - 2][column[0] + 1] == ' ' || tile[row[0] - 2][column[0] + 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
        else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'x' || tile[row[0] - 1][column[0] - 1] == 'X') &&
                 (tile[row[0] - 2][column[0] - 1] == ' ' || tile[row[0] - 2][column[0] - 1] == '.'))
        {
            if (tile[row[0]][column[0]] == 'o')
            {
                tile[row[0]][column[0]] = 's';
            }
            else
            {
                tile[row[0]][column[0]] = 'S';
            }
            selected = 'Y';
        }
    }
}

void move_piece_p1(int num)
{
    // moving players selected piece
    moved = 'N';
    proceed = 'N';
    if (num == 0)
    {
        // moving up without knock
        if (row[0] + 1 == row[1] && more_knocks == 'N')
        {
            if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && (column[0] == column[1] || column[0] + 1 == column[1]))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] == 3 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && (column[0] == column[1] || column[0] - 1 == column[1]))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] == 0 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
            }
        }
        // moving down without knock
        else if (row[0] - 1 == row[1] && more_knocks == 'N' && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (column[0] == column[1] || column[0] + 1 == column[1]) &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] == 3 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] != 0 && (column[0] == column[1] || column[0] - 1 == column[1]) &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] == 0 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0]][column[0]] = '.';
            }
        }
        // moving up with knock
        else if (row[0] + 2 == row[1])
        {
            if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'o' || tile[row[0] + 1][column[0] - 1] == 'O') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] - 1] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'o' || tile[row[0] + 1][column[0] + 1] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] + 1] = '.';
            }
        }
        // moving down with knock
        else if (row[0] - 2 == row[1] && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'o' || tile[row[0] - 1][column[0] - 1] == 'O') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0] - 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'o' || tile[row[0] - 1][column[0] + 1] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0] + 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
        }
    }
    if (moved == 'Y')
    {
        row[0] = row[1];
        column[0] = column[1];
    }
    // king
    for (int v = 0; v < 4; v++)
    {
        if (tile[7][v] == 'x')
        {
            tile[7][v] = 'X';
        }
    }
}

void move_piece_p2(int num)
{
    // moving players selected piece
    moved = 'N';
    proceed = 'N';
    if (num == 0)
    {
        // moving up without knock
        if (row[0] + 1 == row[1] && more_knocks == 'N' && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && (column[0] == column[1] || column[0] + 1 == column[1]))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] == 3 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && (column[0] == column[1] || column[0] - 1 == column[1]))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] == 0 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
            }
        }
        // moving down without knock
        else if (row[0] - 1 == row[1] && more_knocks == 'N')
        {
            if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] != 3 && (column[0] == column[1] || column[0] + 1 == column[1]) &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 2 || row[0] == 4 || row[0] == 6) && column[0] == 3 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] != 0 && (column[0] == column[1] || column[0] - 1 == column[1]) &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5 || row[0] == 7) && column[0] == 0 && column[0] == column[1] &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.'))
            {
                moved = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0]][column[0]] = '.';
            }
        }
        // moving up with knock
        else if (row[0] + 2 == row[1] && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'x' || tile[row[0] + 1][column[0] - 1] == 'X') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] - 1] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'x' || tile[row[0] + 1][column[0] + 1] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] + 1] = '.';
            }
        }
        // moving down with knock
        else if (row[0] - 2 == row[1])
        {
            if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'x' || tile[row[0] - 1][column[0] - 1] == 'X') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0] - 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'x' || tile[row[0] - 1][column[0] + 1] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0] + 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
        }
    }
    if (moved == 'Y')
    {
        row[0] = row[1];
        column[0] = column[1];
    }
    /// king
    for (int v = 0; v < 4; v++)
    {
        if (tile[0][v] == 'o')
        {
            tile[0][v] = 'O';
        }
    }
}

void more_knocks_check()
{
    // checks for more knocks
    more_knocks = 'N';
    if (tile[row[1]][column[1]] == 'x' || tile[row[1]][column[1]] == 'X')
    {
        if ((row[1] == 1 || row[1] == 3 || row[1] == 5) && column[1] != 0 && (tile[row[1] + 1][column[1] - 1] == 'o' || tile[row[1] + 1][column[1] - 1] == 'O') &&
            (tile[row[1] + 2][column[1] - 1] == ' ' || tile[row[1] + 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 1 || row[1] == 3 || row[1] == 5) && column[1] != 3 && (tile[row[1] + 1][column[1]] == 'o' || tile[row[1] + 1][column[1]] == 'O') &&
            (tile[row[1] + 2][column[1] + 1] == ' ' || tile[row[1] + 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 0 || row[1] == 2 || row[1] == 4) && column[1] != 0 && (tile[row[1] + 1][column[1]] == 'o' || tile[row[1] + 1][column[1]] == 'O') &&
            (tile[row[1] + 2][column[1] - 1] == ' ' || tile[row[1] + 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 0 || row[1] == 2 || row[1] == 4) && column[1] != 3 && (tile[row[1] + 1][column[1] + 1] == 'o' || tile[row[1] + 1][column[1] + 1] == 'O') &&
            (tile[row[1] + 2][column[1] + 1] == ' ' || tile[row[1] + 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
    }
    if (tile[row[1]][column[1]] == 'X')
    {
        if ((row[1] == 7 || row[1] == 3 || row[1] == 5) && column[1] != 0 && (tile[row[1] - 1][column[1] - 1] == 'o' || tile[row[1] - 1][column[1] - 1] == 'O') &&
            (tile[row[1] - 2][column[1] - 1] == ' ' || tile[row[1] - 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 7 || row[1] == 3 || row[1] == 5) && column[1] != 3 && (tile[row[1] - 1][column[1]] == 'o' || tile[row[1] - 1][column[1]] == 'O') &&
            (tile[row[1] - 2][column[1] + 1] == ' ' || tile[row[1] - 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 6 || row[1] == 2 || row[1] == 4) && column[1] != 0 && (tile[row[1] - 1][column[1]] == 'o' || tile[row[1] - 1][column[1]] == 'O') &&
            (tile[row[1] - 2][column[1] - 1] == ' ' || tile[row[1] - 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 6 || row[1] == 2 || row[1] == 4) && column[1] != 3 && (tile[row[1] - 1][column[1] + 1] == 'o' || tile[row[1] - 1][column[1] + 1] == 'O') &&
            (tile[row[1] - 2][column[1] + 1] == ' ' || tile[row[1] - 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
    }
    if (tile[row[1]][column[1]] == 'o' || tile[row[1]][column[1]] == 'O')
    {
        if ((row[1] == 7 || row[1] == 3 || row[1] == 5) && column[1] != 0 && (tile[row[1] - 1][column[1] - 1] == 'x' || tile[row[1] - 1][column[1] - 1] == 'X') &&
            (tile[row[1] - 2][column[1] - 1] == ' ' || tile[row[1] - 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 7 || row[1] == 3 || row[1] == 5) && column[1] != 3 && (tile[row[1] - 1][column[1]] == 'x' || tile[row[1] - 1][column[1]] == 'X') &&
            (tile[row[1] - 2][column[1] + 1] == ' ' || tile[row[1] - 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 6 || row[1] == 2 || row[1] == 4) && column[1] != 0 && (tile[row[1] - 1][column[1]] == 'x' || tile[row[1] - 1][column[1]] == 'X') &&
            (tile[row[1] - 2][column[1] - 1] == ' ' || tile[row[1] - 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 6 || row[1] == 2 || row[1] == 4) && column[1] != 3 && (tile[row[1] - 1][column[1] + 1] == 'x' || tile[row[1] - 1][column[1] + 1] == 'X') &&
            (tile[row[1] - 2][column[1] + 1] == ' ' || tile[row[1] - 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
    }
    if (tile[row[1]][column[1]] == 'O')
    {
        if ((row[1] == 1 || row[1] == 3 || row[1] == 5) && column[1] != 0 && (tile[row[1] + 1][column[1] - 1] == 'x' || tile[row[1] + 1][column[1] - 1] == 'X') &&
            (tile[row[1] + 2][column[1] - 1] == ' ' || tile[row[1] + 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 1 || row[1] == 3 || row[1] == 5) && column[1] != 3 && (tile[row[1] + 1][column[1]] == 'x' || tile[row[1] + 1][column[1]] == 'X') &&
            (tile[row[1] + 2][column[1] + 1] == ' ' || tile[row[1] + 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 0 || row[1] == 2 || row[1] == 4) && column[1] != 0 && (tile[row[1] + 1][column[1]] == 'x' || tile[row[1] + 1][column[1]] == 'X') &&
            (tile[row[1] + 2][column[1] - 1] == ' ' || tile[row[1] + 2][column[1] - 1] == '.'))
        {
            more_knocks = 'Y';
        }
        if ((row[1] == 0 || row[1] == 2 || row[1] == 4) && column[1] != 3 && (tile[row[1] + 1][column[1] + 1] == 'x' || tile[row[1] + 1][column[1] + 1] == 'X') &&
            (tile[row[1] + 2][column[1] + 1] == ' ' || tile[row[1] + 2][column[1] + 1] == '.'))
        {
            more_knocks = 'Y';
        }
    }
}

int forced_knock_p1()
{
    // checking forced knocks
    int total = 0;
    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            // checking upwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (tile[a + 1][b + 1] == 'o' || tile[a + 1][b + 1] == 'O') &&
                (tile[a + 2][b + 1] == ' ' || tile[a + 2][b + 1] == '.') && (tile[a][b] == 'x' || tile[a][b] == 'X'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (tile[a + 1][b] == 'o' || tile[a + 1][b] == 'O') &&
                (tile[a + 2][b - 1] == ' ' || tile[a + 2][b - 1] == '.') && (tile[a][b] == 'x' || tile[a][b] == 'X'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (tile[a + 1][b] == 'o' || tile[a + 1][b] == 'O') &&
                (tile[a + 2][b + 1] == ' ' || tile[a + 2][b + 1] == '.') && (tile[a][b] == 'x' || tile[a][b] == 'X'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (tile[a + 1][b - 1] == 'o' || tile[a + 1][b - 1] == 'O') &&
                (tile[a + 2][b - 1] == ' ' || tile[a + 2][b - 1] == '.') && (tile[a][b] == 'x' || tile[a][b] == 'X'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            // checking downwards
            if ((a == 6 || a == 2 || a == 4) && b != 3 && (tile[a - 1][b + 1] == 'o' || tile[a - 1][b + 1] == 'O') &&
                (tile[a - 2][b + 1] == ' ' || tile[a - 2][b + 1] == '.') && tile[a][b] == 'X')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (tile[a - 1][b] == 'o' || tile[a - 1][b] == 'O') &&
                (tile[a - 2][b - 1] == ' ' || tile[a - 2][b - 1] == '.') && tile[a][b] == 'X')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (tile[a - 1][b] == 'o' || tile[a - 1][b] == 'O') &&
                (tile[a - 2][b + 1] == ' ' || tile[a - 2][b + 1] == '.') && tile[a][b] == 'X')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (tile[a - 1][b - 1] == 'o' || tile[a - 1][b - 1] == 'O') &&
                (tile[a - 2][b - 1] == ' ' || tile[a - 2][b - 1] == '.') && tile[a][b] == 'X')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
        }
    }
    return total;
}

int forced_knock_p2()
{
    int total = 0;
    for (int a = 0; a <= 7; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            // checking upwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (tile[a + 1][b + 1] == 'x' || tile[a + 1][b + 1] == 'X') &&
                (tile[a + 2][b + 1] == ' ' || tile[a + 2][b + 1] == '.') && tile[a][b] == 'O')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (tile[a + 1][b] == 'x' || tile[a + 1][b] == 'X') &&
                (tile[a + 2][b - 1] == ' ' || tile[a + 2][b - 1] == '.') && tile[a][b] == 'O')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (tile[a + 1][b] == 'x' || tile[a + 1][b] == 'X') &&
                (tile[a + 2][b + 1] == ' ' || tile[a + 2][b + 1] == '.') && tile[a][b] == 'O')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (tile[a + 1][b - 1] == 'x' || tile[a + 1][b - 1] == 'X') &&
                (tile[a + 2][b - 1] == ' ' || tile[a + 2][b - 1] == '.') && tile[a][b] == 'O')
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            // checking downwards
            if ((a == 6 || a == 2 || a == 4) && b != 3 && (tile[a - 1][b + 1] == 'x' || tile[a - 1][b + 1] == 'X') &&
                (tile[a - 2][b + 1] == ' ' || tile[a - 2][b + 1] == '.') && (tile[a][b] == 'o' || tile[a][b] == 'O'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (tile[a - 1][b] == 'x' || tile[a - 1][b] == 'X') &&
                (tile[a - 2][b - 1] == ' ' || tile[a - 2][b - 1] == '.') && (tile[a][b] == 'o' || tile[a][b] == 'O'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (tile[a - 1][b] == 'x' || tile[a - 1][b] == 'X') &&
                (tile[a - 2][b + 1] == ' ' || tile[a - 2][b + 1] == '.') && (tile[a][b] == 'o' || tile[a][b] == 'O'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (tile[a - 1][b - 1] == 'x' || tile[a - 1][b - 1] == 'X') &&
                (tile[a - 2][b - 1] == ' ' || tile[a - 2][b - 1] == '.') && (tile[a][b] == 'o' || tile[a][b] == 'O'))
            {
                row[0] = a;
                column[0] = b;
                total++;
            }
        }
    }
    return total;
}

void forced_move_p1()
{
    int total = forced_knock_p1();
    moved = 'N';
    proceed = 'N';
    if (total > 1)
    {
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        printf("        FORCED MOVE ACTIVATED, %s\n", player1_name);
        do
        {
            printf("        Enter piece row# column# e.g 12: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &choice);
            choice_processing(1);
            more_knocks_check();
            if (more_knocks == 'N')
            {
                print_board();
                printf("        TRY AGAIN %s\n", player1_name);
            }
        } while (more_knocks == 'N');
        row[0] = row[1];
        column[0] = column[1];

        // selecting
        if (tile[row[0]][column[0]] == 'x')
            tile[row[0]][column[0]] = 's';
        else
            tile[row[0]][column[0]] = 'S';
        print_board();
        printf("        ***  SELECTED %s  ***\n", player1_name);
    }
    else if (total == 1)
    {
        // selecting
        if (tile[row[0]][column[0]] == 'x')
            tile[row[0]][column[0]] = 's';
        else
            tile[row[0]][column[0]] = 'S';
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        printf("        FORCED MOVE ACTIVATED, %s\n", player1_name);
    }
    // moving players selected piece
    do
    {
        printf("        Enter target row# column# e.g 23: ");
        fgets(input, sizeof(input), stdin); // getting any input
        sscanf(input, "%d", &choice);       // making above input an integer
        choice_processing(1);

        // moving up with knock
        if (row[0] + 2 == row[1])
        {
            if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'o' || tile[row[0] + 1][column[0] - 1] == 'O') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] - 1] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'o' || tile[row[0] + 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'o' || tile[row[0] + 1][column[0] + 1] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'X';
                }
                else
                {
                    tile[row[1]][column[1]] = 'x';
                }
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] + 1] = '.';
            }
        }
        // moving down with knock
        else if (row[0] - 2 == row[1] && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'o' || tile[row[0] - 1][column[0] - 1] == 'O') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0] - 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'o' || tile[row[0] - 1][column[0]] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'o' || tile[row[0] - 1][column[0] + 1] == 'O') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'X';
                tile[row[0] - 1][column[0] + 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
        }
        if (moved == 'N')
        {
            print_board();
            printf("        TRY AGAIN %s\n", player1_name);
        }

    } while (moved == 'N');
    // king
    for (int v = 0; v < 4; v++)
    {
        if (tile[7][v] == 'x')
        {
            tile[7][v] = 'X';
        }
    }
    row[0] = row[1];
    column[0] = column[1];
}

void forced_move_p2()
{
    int total = forced_knock_p2();
    moved = 'N';
    proceed = 'N';
    if (total > 1)
    {
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        printf("        FORCED MOVE ACTIVATED, %s\n", player2_name);
        do
        {
            printf("        Enter piece row# column# e.g 12: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &choice);
            choice_processing(1);
            more_knocks_check();
            if (more_knocks == 'N')
            {
                print_board();
                printf("        TRY AGAIN %s\n", player2_name);
            }
        } while (more_knocks == 'N');
        row[0] = row[1];
        column[0] = column[1];

        // selecting
        if (tile[row[0]][column[0]] == 'o')
            tile[row[0]][column[0]] = 's';
        else
            tile[row[0]][column[0]] = 'S';
        print_board();
        printf("        ***  SELECTED %s  ***\n", player2_name);
    }
    if (total == 1)
    {
        // selecting
        if (tile[row[0]][column[0]] == 'o')
            tile[row[0]][column[0]] = 's';
        else
            tile[row[0]][column[0]] = 'S';
        print_board();
        // removing '.' from tile
        for (int h = 0; h < 8; h++)
        {
            for (int g = 0; g < 4; g++)
            {
                if (tile[h][g] == '.')
                {
                    tile[h][g] = ' ';
                }
            }
        }
        printf("        FORCED MOVE ACTIVATED, %s\n", player2_name);
    }
    // moving players selected piece
    do
    {
        printf("        Enter target row# column# e.g 23: ");
        fgets(input, sizeof(input), stdin); // getting any input
        sscanf(input, "%d", &choice);       // making above input an integer
        choice_processing(1);

        // moving up with knock
        if (row[0] + 2 == row[1] && tile[row[0]][column[0]] == 'S')
        {
            if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] + 1][column[0] - 1] == 'x' || tile[row[0] + 1][column[0] - 1] == 'X') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] - 1] = '.';
            }
            else if ((row[0] == 1 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] + 1][column[0]] == 'x' || tile[row[0] + 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0]] = '.';
            }
            else if ((row[0] == 0 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] + 1][column[0] + 1] == 'x' || tile[row[0] + 1][column[0] + 1] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                tile[row[1]][column[1]] = 'O';
                tile[row[0]][column[0]] = '.';
                tile[row[0] + 1][column[0] + 1] = '.';
            }
        }
        // moving down with knock
        else if (row[0] - 2 == row[1])
        {
            if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 0 && (tile[row[0] - 1][column[0] - 1] == 'x' || tile[row[0] - 1][column[0] - 1] == 'X') &&
                (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0] - 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 7 || row[0] == 3 || row[0] == 5) && column[0] != 3 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 0 && (tile[row[0] - 1][column[0]] == 'x' || tile[row[0] - 1][column[0]] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] - 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0]] = '.';
                tile[row[0]][column[0]] = '.';
            }
            else if ((row[0] == 6 || row[0] == 2 || row[0] == 4) && column[0] != 3 && (tile[row[0] - 1][column[0] + 1] == 'x' || tile[row[0] - 1][column[0] + 1] == 'X') &&
                     (tile[row[1]][column[1]] == ' ' || tile[row[1]][column[1]] == '.') && column[0] + 1 == column[1])
            {
                moved = 'Y';
                proceed = 'Y';
                if (tile[row[0]][column[0]] == 'S')
                {
                    tile[row[1]][column[1]] = 'O';
                }
                else
                {
                    tile[row[1]][column[1]] = 'o';
                }
                tile[row[0] - 1][column[0] + 1] = '.';
                tile[row[0]][column[0]] = '.';
            }
        }
        if (moved == 'N')
        {
            print_board();
            printf("        TRY AGAIN %s\n", player2_name);
        }
    } while (moved == 'N');
    // king
    for (int v = 0; v < 4; v++)
    {
        if (tile[0][v] == 'o')
        {
            tile[0][v] = 'O';
        }
    }
    row[0] = row[1];
    column[0] = column[1];
}

int check_winner()
{
    // checks winner
    int xCount = 0, XCount = 0, oCount = 0, OCount = 0, player1Sum = 0;
    int player2Sum = 0, player1Moves = 0, player2Moves = 0;
    // getting each player total pieces on tile
    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            if (tile[a][b] == 'x')
            {
                xCount++;
            }
            else if (tile[a][b] == 'X')
            {
                XCount++;
            }
            else if (tile[a][b] == 'o')
            {
                oCount++;
            }
            else if (tile[a][b] == 'O')
            {
                OCount++;
            }
        }
    }
    player1Sum = xCount + XCount;
    player2Sum = oCount + OCount;

    if (play_count[5] % 2 == 0)
    {
        play_count[1] = player1Sum;
        play_count[2] = player2Sum;
    }
    else if (play_count[5] % 2 != 0)
    {
        play_count[3] = player1Sum;
        play_count[4] = player2Sum;
    }
    if (play_count[1] == play_count[3] && play_count[2] == play_count[4] && play_count[1] < 4 && play_count[2] < 4)
    {
        play_count[0]++;
    }

    // counting number of moves for x

    for (int c = 0; c <= 7; c++)
    {
        for (int d = 0; d <= 3; d++)
        {
            if (tile[c][d] == 'x' || tile[c][d] == 'X')
            {
                // moving up without knock
                if ((c == 0 || c == 2 || c == 4 || c == 6) && (tile[c + 1][d] == ' ' || tile[c + 1][d] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 0 || c == 2 || c == 4 || c == 6) && d != 3 && (tile[c + 1][d + 1] == ' ' || tile[c + 1][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && (tile[c + 1][d] == ' ' || tile[c + 1][d] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 0 && (tile[c + 1][d - 1] == ' ' || tile[c + 1][d - 1] == '.'))
                {
                    player1Moves++;
                }
                // moving up with knock
                if ((c == 0 || c == 2 || c == 4) && d != 3 && (tile[c + 1][d + 1] == 'o' || tile[c + 1][d + 1] == 'O') &&
                    (tile[c + 2][d + 1] == ' ' || tile[c + 2][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 0 || c == 2 || c == 4) && d != 0 && (tile[c + 1][d] == 'o' || tile[c + 1][d] == 'O') &&
                    (tile[c + 2][d - 1] == ' ' || tile[c + 2][d - 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 3 && (tile[c + 1][d] == 'o' || tile[c + 1][d] == 'O') &&
                    (tile[c + 2][d + 1] == ' ' || tile[c + 2][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 0 && (tile[c + 1][d - 1] == 'o' || tile[c + 1][d - 1] == 'O') &&
                    (tile[c + 2][d - 1] == ' ' || tile[c + 2][d - 1] == '.'))
                {
                    player1Moves++;
                }
            }
            if (tile[c][d] == 'X')
            {
                // moving down without knock
                if ((c == 2 || c == 4 || c == 6) && (tile[c - 1][d] == ' ' || tile[c - 1][d] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 2 || c == 4 || c == 6) && d != 3 && (tile[c - 1][d + 1] == ' ' || tile[c - 1][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5 || c == 7) && (tile[c - 1][d] == ' ' || tile[c - 1][d] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 1 || c == 3 || c == 5 || c == 7) && d != 0 && (tile[c - 1][d - 1] == ' ' || tile[c - 1][d - 1] == '.'))
                {
                    player1Moves++;
                }
                // moving down with knock
                if ((c == 6 || c == 2 || c == 4) && d != 3 && (tile[c - 1][d + 1] == 'o' || tile[c - 1][d + 1] == 'O') &&
                    (tile[c - 2][d + 1] == ' ' || tile[c - 2][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 6 || c == 2 || c == 4) && d != 0 && (tile[c - 1][d] == 'o' || tile[c - 1][d] == 'O') &&
                    (tile[c - 2][d - 1] == ' ' || tile[c - 2][d - 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 7 || c == 3 || c == 5) && d != 3 && (tile[c - 1][d] == 'o' || tile[c - 1][d] == 'O') &&
                    (tile[c - 2][d + 1] == ' ' || tile[c - 2][d + 1] == '.'))
                {
                    player1Moves++;
                }
                if ((c == 7 || c == 3 || c == 5) && d != 0 && (tile[c - 1][d - 1] == 'o' || tile[c - 1][d - 1] == 'O') &&
                    (tile[c - 2][d - 1] == ' ' || tile[c - 2][d - 1] == '.'))
                {
                    player1Moves++;
                }
            }
            //
            if (tile[c][d] == 'O')
            {
                // moving up without knock
                if ((c == 0 || c == 2 || c == 4 || c == 6) && (tile[c + 1][d] == ' ' || tile[c + 1][d] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 0 || c == 2 || c == 4 || c == 6) && d != 3 && (tile[c + 1][d + 1] == ' ' || tile[c + 1][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && (tile[c + 1][d] == ' ' || tile[c + 1][d] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 0 && (tile[c + 1][d - 1] == ' ' || tile[c + 1][d - 1] == '.'))
                {
                    player2Moves++;
                }
                // moving up with knock
                if ((c == 0 || c == 2 || c == 4) && d != 3 && (tile[c + 1][d + 1] == 'x' || tile[c + 1][d + 1] == 'X') &&
                    (tile[c + 2][d + 1] == ' ' || tile[c + 2][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 0 || c == 2 || c == 4) && d != 0 && (tile[c + 1][d] == 'x' || tile[c + 1][d] == 'X') &&
                    (tile[c + 2][d - 1] == ' ' || tile[c + 2][d - 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 3 && (tile[c + 1][d] == 'x' || tile[c + 1][d] == 'X') &&
                    (tile[c + 2][d + 1] == ' ' || tile[c + 2][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5) && d != 0 && (tile[c + 1][d - 1] == 'x' || tile[c + 1][d - 1] == 'X') &&
                    (tile[c + 2][d - 1] == ' ' || tile[c + 2][d - 1] == '.'))
                {
                    player2Moves++;
                }
            }
            if (tile[c][d] == 'o' || tile[c][d] == 'O')
            {
                // moving down without knock
                if ((c == 2 || c == 4 || c == 6) && (tile[c - 1][d] == ' ' || tile[c - 1][d] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 2 || c == 4 || c == 6) && d != 3 && (tile[c - 1][d + 1] == ' ' || tile[c - 1][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5 || c == 7) && (tile[c - 1][d] == ' ' || tile[c - 1][d] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 1 || c == 3 || c == 5 || c == 7) && d != 0 && (tile[c - 1][d - 1] == ' ' || tile[c - 1][d - 1] == '.'))
                {
                    player2Moves++;
                }
                // moving down with knock
                if ((c == 6 || c == 2 || c == 4) && d != 3 && (tile[c - 1][d + 1] == 'x' || tile[c - 1][d + 1] == 'X') &&
                    (tile[c - 2][d + 1] == ' ' || tile[c - 2][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 6 || c == 2 || c == 4) && d != 0 && (tile[c - 1][d] == 'x' || tile[c - 1][d] == 'X') &&
                    (tile[c - 2][d - 1] == ' ' || tile[c - 2][d - 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 7 || c == 3 || c == 5) && d != 3 && (tile[c - 1][d] == 'x' || tile[c - 1][d] == 'X') &&
                    (tile[c - 2][d + 1] == ' ' || tile[c - 2][d + 1] == '.'))
                {
                    player2Moves++;
                }
                if ((c == 7 || c == 3 || c == 5) && d != 0 && (tile[c - 1][d - 1] == 'x' || tile[c - 1][d - 1] == 'X') &&
                    (tile[c - 2][d - 1] == ' ' || tile[c - 2][d - 1] == '.'))
                {
                    player2Moves++;
                }
            }
        }
    }
    // player2 has no pieces/comp cannot move all of their pieces --------> player1 wins
    if ((player2Sum == 0 && player1Sum != 0) || player2Moves == 0)
    {
        return 1;
    }
    // player1 has no pieces/player cannot move all of their pieces ------> player2 wins
    else if ((player1Sum == 0 && player2Sum != 0) || player1Moves == 0)
    {
        return 2;
    }
    // each player moves 10 times with the same number of pieces on board(less than 4) -----> Draw
    else if (play_count[0] >= 10)
    {
        return 3;
    }
    // no winner yet
    else
    {
        return 0;
    }
}

void print_winner()
{
    // prints winner
    int winner = check_winner();
    if (winner == 1)
    {
        print_board();
        printf("\n        -----------------------------------------");
        printf("\n           %s WINS!!", player1_name);
        printf("\n        -----------------------------------------\n");
    }
    else if (winner == 2)
    {
        print_board();
        printf("\n        -----------------------------------------");
        printf("\n           %s WINS!!", player2_name);
        printf("\n        -----------------------------------------\n");
    }
    else
    {
        print_board();
        printf("\n        -----------------------------------------");
        printf("\n                     GAME DRAW!!");
        printf("\n        -----------------------------------------\n");
    }
}