

/*
    AUTHOR:      JOHN KALOKI
    NATIONALITY: KENYAN
    GITHUB:      WebTweaks
    HANDLE:      @jonkaloki
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <cmath>

std::string player_name{};

char board[8][4]{};
char temp_board1[8][4]{};
char temp_board2[8][4]{};
char temp_board3[8][4]{};

short int play_mode{3};
short int choice[2]{};
short int y[4]{};
short int x[4]{};

short int source_y[35]{};
short int source_x[35]{};
short int target_y[35]{};
short int target_x[35]{};

short int draw_count[5]{};
short int rand_num{};

bool moved_by_knock{false};
bool knock_present{false};
bool selected{false};
bool removed_knock{false};
bool blocked_knock{false};
bool moved{false};
bool future_knock{false};
bool hunted{false};
bool knock_created{false};
bool knock_encounted{false};

void reset_board();
void print_board();

void player();
void choice_processing(short int);
void selectPiece_player();
void movePiece_player();
void moreKnocks_player();

void computer();
void knocks_checking(short int *index);
short int total_compMoves();
short int total_unknockMoves();
void selectPiece_comp();
void movePiece_comp(char knock);
void moreKnocks_comp();
void future_playersKnock(bool with_values);
short int maxKnocks_comp();
void future_more_knocks();
short int maxKnocks_player();
void best_move();
short int triple_play(short int *);
bool playerMove_prediction();
void playersKnock_remove();
void playersKnock_block();
void knock_antidote();
void player_hunt();
void knock_creation();

short int check_winner(bool sum_up);
void print_winner(short int winner);
void print_heart();

int main()
{
    srand(time(0));

    bool end{false};
    char play_again{};
    const short int max_length{20};

    std::cout << "\n        Enter your name dear: ";

    char temp_name1[max_length]{};
    char temp_name2[max_length]{};

    std::cin.getline(temp_name1, max_length);
    for (short int s = 0; s < std::size(temp_name1); ++s)
    {
        if (temp_name1[s] == ' ')
            break;

        temp_name1[s] = std::toupper(temp_name1[s]);
        temp_name2[s] = temp_name1[s];
    }

    player_name = temp_name2;

    while (!end)
    {
        std::cout << std::endl;
        std::cout << "                        ID  |  MODE" << std::endl;
        std::cout << "        --------------------|--------------------" << std::endl;
        std::cout << "                         1  |  Easy" << std::endl;
        std::cout << "                         2  |  Normal" << std::endl;
        std::cout << "                         3  |  Hard" << std::endl;
        std::cout << "        --------------------|--------------------" << std::endl;
        std::cout << std::endl;

        do
        {
            std::cout << "                     Enter mode ID: ";
            if (!(std::cin >> play_mode))
            {
                std::cout << "                 Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        } while (play_mode != 1 && play_mode != 2 && play_mode != 3);

        std::cout << '\n';
        reset_board();
        short int winner{};

        do
        {
            computer();
            winner = check_winner(false);
            if (winner != 0)
                break;

            player();
            winner = check_winner(true);

        } while (winner == 0);

        print_winner(winner);

        std::cout << "        Would You Like To Play Again? (Y/N) ";
        std::cin >> play_again;

        if (play_again == 'y' || play_again == 'Y')
            end = false;
        else
            end = true;
    }

    std::cout << "        Thank You " << player_name << " For Playing!" << std::endl;
    print_heart();

    std::cout << std::endl;
    return 0;
}

void reset_board()
{
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = ' ';
        }
    }

    // player
    for (s = 0; s < 3; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = 'x';
        }
    }

    // comp
    for (s = 5; s <= 7; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = 'o';
        }
    }
}

void print_board()
{
    std::cout << '\n';
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << '\n';
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        8   | " << board[7][0] << " |   | " << board[7][1] << " |   | " << board[7][2] << " |   | " << board[7][3] << " |   |   8" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        7   |   | " << board[6][0] << " |   | " << board[6][1] << " |   | " << board[6][2] << " |   | " << board[6][3] << " |   7" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        6   | " << board[5][0] << " |   | " << board[5][1] << " |   | " << board[5][2] << " |   | " << board[5][3] << " |   |   6" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        5   |   | " << board[4][0] << " |   | " << board[4][1] << " |   | " << board[4][2] << " |   | " << board[4][3] << " |   5" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        4   | " << board[3][0] << " |   | " << board[3][1] << " |   | " << board[3][2] << " |   | " << board[3][3] << " |   |   4" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        3   |   | " << board[2][0] << " |   | " << board[2][1] << " |   | " << board[2][2] << " |   | " << board[2][3] << " |   3" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        2   | " << board[1][0] << " |   | " << board[1][1] << " |   | " << board[1][2] << " |   | " << board[1][3] << " |   |   2" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        1   |   | " << board[0][0] << " |   | " << board[0][1] << " |   | " << board[0][2] << " |   | " << board[0][3] << " |   1" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << "" << std::endl;
}

void player()
{
    std::cout << "        =========================================" << std::endl;
    std::cout << "                       YOUR TURN" << std::endl;
    std::cout << "        =========================================" << std::endl;
    std::cout << '\n';

    char reselect_board[8][4]{};
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            reselect_board[s][t] = board[s][t];
            if (board[s][t] == '.')
            {
                board[s][t] = ' ';
            }
        }
    }

    switch (draw_count[4])
    {
    case 6:
        std::cout << "        6 More Non-Knock Moves To Draw!" << std::endl;
        break;
    case 9:
        std::cout << "        3 More Non-Knock Moves To Draw!" << std::endl;
        break;
    case 11:
        std::cout << "        1 More Non-Knock Move To Draw!" << std::endl;
        break;
    default:
        break;
    }

    selected = false;
    moved = false;

    do
    {
        do
        {
            std::cout << "        Enter piece row# column# e.g 32: ";

            if (!(std::cin >> choice[0]))
            {
                std::cout << "\n        Invalid input!" << std::endl;

                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        board[s][t] = reselect_board[s][t];
                    }
                }

                print_board();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                choice_processing(0);
                selectPiece_player();

                if (!selected)
                {
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            board[s][t] = reselect_board[s][t];
                        }
                    }

                    std::cout << "\n        Invalid input!";
                    print_board();
                }
            }

            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    if (board[s][t] == '.')
                    {
                        board[s][t] = ' ';
                    }
                }
            }

        } while (!selected);

        std::cout << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "        SELECTED " << player_name << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;
        print_board();

        std::cout << "        Enter 00 to reselect." << '\n';

        while (!moved && selected)
        {
            std::cout << "        Enter target row# column# e.g 43: ";

            if (!(std::cin >> choice[1]))
            {
                print_board();
                std::cout << "        Invalid input!! Enter 00 to reselect!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                if (choice[1] == 00)
                {
                    selected = false;
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            board[s][t] = reselect_board[s][t];
                        }
                    }
                }
                else
                {
                    choice_processing(1);
                    movePiece_player();

                    if (!moved)
                    {
                        print_board();
                        std::cout << "        Invalid input!! Enter 00 to reselect!" << std::endl;
                    }
                }
            }
        }
        if (!selected)
        {
            print_board();
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    if (board[s][t] == '.')
                    {
                        board[s][t] = ' ';
                    }
                }
            }
        }

    } while (!selected);
    moreKnocks_player();

    while (knock_present && moved_by_knock)
    {
        if (board[y[1]][x[1]] == 'X')
        {
            board[y[1]][x[1]] = 'S';
        }
        else if (board[y[1]][x[1]] == 'x')
        {
            board[y[1]][x[1]] = 's';
        }

        print_board();
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "               CONSECUTIVE KNOCK AVAILABLE " << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;

        do
        {
            std::cout << "        Enter target row# column# e.g 54: ";

            if (!(std::cin >> choice[1]))
            {
                std::cout << "        Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                print_board();
            }

            else
            {
                choice_processing(1);
                movePiece_player();

                if (!moved)
                {
                    std::cout << "        Invalid input! Try again!" << std::endl;
                    print_board();
                }
            }

        } while (!moved);
        moreKnocks_player();
    }

    print_board();
    std::cout << "        MOVED " << player_name << "." << std::endl;
    std::cout << std::endl;
}

void choice_processing(short int index)
{
    if (choice[index] == 11 || choice[index] == 13 || choice[index] == 15 || choice[index] == 17 || choice[index] == 22 || choice[index] == 24 || choice[index] == 26 || choice[index] == 28 || choice[index] == 31 || choice[index] == 33 || choice[index] == 35 || choice[index] == 37 || choice[index] == 42 || choice[index] == 44 || choice[index] == 46 || choice[index] == 48 ||
        choice[index] == 51 || choice[index] == 53 || choice[index] == 55 || choice[index] == 57 || choice[index] == 62 || choice[index] == 64 || choice[index] == 66 || choice[index] == 68 || choice[index] == 71 || choice[index] == 73 || choice[index] == 75 || choice[index] == 77 || choice[index] == 82 || choice[index] == 84 || choice[index] == 86 || choice[index] == 88)
    {
        y[index] = 9;
        x[index] = 9;
    }
    else if (choice[index] > 11 && choice[index] < 88)
    {
        y[index] = choice[index] / 10;
        x[index] = choice[index] % 10;

        if (y[index] == 8 || y[index] == 6 || y[index] == 4 || y[index] == 2)
        {
            if (x[index] == 1)
            {
                x[index] = 0;
            }
            else if (x[index] == 3)
            {
                x[index] = 1;
            }
            else if (x[index] == 5)
            {
                x[index] = 2;
            }
            else if (x[index] == 7)
            {
                x[index] = 3;
            }

            y[index] = y[index] - 1;
        }
        else if (y[index] == 7 || y[index] == 5 || y[index] == 3 || y[index] == 1)
        {
            if (x[index] == 2)
            {
                x[index] = 0;
            }
            else if (x[index] == 4)
            {
                x[index] = 1;
            }
            else if (x[index] == 6)
            {
                x[index] = 2;
            }
            else if (x[index] == 8)
            {
                x[index] = 3;
            }
            y[index] = y[index] - 1;
        }
    }
    else
    {
        y[index] = 9;
        x[index] = 9;
    }
}

void selectPiece_player()
{
    selected = false;

    if (board[y[0]][x[0]] == 'x' || board[y[0]][x[0]] == 'X')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == ' ' || board[y[0] + 1][x[0] + 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == ' ' || board[y[0] + 1][x[0] - 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == 'o' || board[y[0] + 1][x[0] + 1] == 'O') &&
                 (board[y[0] + 2][x[0] + 1] == ' ' || board[y[0] + 2][x[0] + 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[0] + 2][x[0] - 1] == ' ' || board[y[0] + 2][x[0] - 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[0] + 2][x[0] + 1] == ' ' || board[y[0] + 2][x[0] + 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == 'o' || board[y[0] + 1][x[0] - 1] == 'O') &&
                 (board[y[0] + 2][x[0] - 1] == ' ' || board[y[0] + 2][x[0] - 1] == '.'))
        {
            selected = true;
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }
        }
    }
    if (board[y[0]][x[0]] == 'X' && !selected)
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (board[y[0] - 1][x[0] + 1] == ' ' || board[y[0] - 1][x[0] + 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == ' ' || board[y[0] - 1][x[0] - 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] - 1][x[0] + 1] == 'o' || board[y[0] - 1][x[0] + 1] == 'O') &&
                 (board[y[0] - 2][x[0] + 1] == ' ' || board[y[0] - 2][x[0] + 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] - 1][x[0]] == 'o' || board[y[0] - 1][x[0]] == 'O') &&
                 (board[y[0] - 2][x[0] - 1] == ' ' || board[y[0] - 2][x[0] - 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] - 1][x[0]] == 'o' || board[y[0] - 1][x[0]] == 'O') &&
                 (board[y[0] - 2][x[0] + 1] == ' ' || board[y[0] - 2][x[0] + 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == 'o' || board[y[0] - 1][x[0] - 1] == 'O') &&
                 (board[y[0] - 2][x[0] - 1] == ' ' || board[y[0] - 2][x[0] - 1] == '.'))
        {
            board[y[0]][x[0]] = 'S';
            selected = true;
        }
    }
}

void movePiece_player()
{
    moved = false;
    moved_by_knock = false;

    if (y[0] + 1 == y[1] && (board[y[0]][x[0]] == 'S' || board[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            moved = true;
        }
    }
    else if (y[0] - 1 == y[1] && board[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'X';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'X';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'X';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'X';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
    }
    else if (y[0] + 2 == y[1] && (board[y[0]][x[0]] == 'S' || board[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == 'o' || board[y[0] + 1][x[0] - 1] == 'O') &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] - 1] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == 'o' || board[y[0] + 1][x[0] + 1] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (board[y[0]][x[0]] == 'S')
            {
                board[y[1]][x[1]] = 'X';
            }
            else
            {
                board[y[1]][x[1]] = 'x';
            }

            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] + 1] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }
    else if (y[0] - 2 == y[1] && board[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == 'o' || board[y[0] - 1][x[0] - 1] == 'O') &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'X';
            board[y[0] - 1][x[0] - 1] = '.';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] - 1][x[0]] == 'o' || board[y[0] - 1][x[0]] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'X';
            board[y[0] - 1][x[0]] = '.';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] - 1][x[0]] == 'o' || board[y[0] - 1][x[0]] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'X';
            board[y[0] - 1][x[0]] = '.';
            board[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] - 1][x[0] + 1] == 'o' || board[y[0] - 1][x[0] + 1] == 'O') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'X';
            board[y[0] - 1][x[0] + 1] = '.';
            board[y[0]][x[0]] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }

    for (short int t = 0; t < 4; t++)
    {
        if (board[7][t] == 'x')
        {
            board[7][t] = 'X';
        }
    }
}

void moreKnocks_player()
{
    knock_present = false;

    if ((board[y[1]][x[1]] == 'x' || board[y[1]][x[1]] == 'X'))
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] + 1][x[1] - 1] == 'o' || board[y[1] + 1][x[1] - 1] == 'O') &&
            (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] + 1][x[1]] == 'o' || board[y[1] + 1][x[1]] == 'O') &&
            (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] + 1][x[1]] == 'o' || board[y[1] + 1][x[1]] == 'O') &&
            (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] + 1][x[1] + 1] == 'o' || board[y[1] + 1][x[1] + 1] == 'O') &&
            (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (board[y[1]][x[1]] == 'X')
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] - 1][x[1] - 1] == 'o' || board[y[1] - 1][x[1] - 1] == 'O') &&
            (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] - 1][x[1]] == 'o' || board[y[1] - 1][x[1]] == 'O') &&
            (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] - 1][x[1]] == 'o' || board[y[1] - 1][x[1]] == 'O') &&
            (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] - 1][x[1] + 1] == 'o' || board[y[1] - 1][x[1] + 1] == 'O') &&
            (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if ((board[y[1]][x[1]] == 'o' || board[y[1]][x[1]] == 'O'))
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] - 1][x[1] - 1] == 'x' || board[y[1] - 1][x[1] - 1] == 'X') &&
            (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] - 1][x[1]] == 'x' || board[y[1] - 1][x[1]] == 'X') &&
            (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] - 1][x[1]] == 'x' || board[y[1] - 1][x[1]] == 'X') &&
            (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] - 1][x[1] + 1] == 'x' || board[y[1] - 1][x[1] + 1] == 'X') &&
            (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (board[y[1]][x[1]] == 'O')
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] + 1][x[1] - 1] == 'x' || board[y[1] + 1][x[1] - 1] == 'X') &&
            (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] + 1][x[1]] == 'x' || board[y[1] + 1][x[1]] == 'X') &&
            (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] + 1][x[1]] == 'x' || board[y[1] + 1][x[1]] == 'X') &&
            (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] + 1][x[1] + 1] == 'x' || board[y[1] + 1][x[1] + 1] == 'X') &&
            (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
}

void computer()
{
    std::cout << "        =========================================" << std::endl;
    std::cout << "                      COMP'S TURN" << std::endl;
    std::cout << "        ========================================= " << std::endl;
    std::cout << "        Thinking...";

    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if (board[s][t] == '.')
            {
                board[s][t] = ' ';
            }
        }
    }

    moved = false;
    selected = false;

    char temp_board[8][4]{};
    short int max_knocks{};
    short int index{};
    short int total_moves{};
    short int total_knocks{};
    short int total_comp_knocks{};
    short int total_player_knocks{};

    knocks_checking(&total_knocks);
    if (play_mode == 1)
    {
        rand_num = rand() % 3;
        total_moves = total_compMoves();

        if ((rand_num == 1 && knock_present) || (total_moves == 0 && knock_present))
        {
            knocks_checking(&total_knocks);
            rand_num = rand() % total_knocks;

            y[0] = source_y[rand_num];
            x[0] = source_x[rand_num];
            y[1] = target_y[rand_num];
            x[1] = target_x[rand_num];

            movePiece_comp('Y');
            moreKnocks_comp();

            while (knock_present)
            {
                movePiece_comp('Y');
                moreKnocks_comp();
            }

            moved = true;
        }

        if (!moved)
        {
            selectPiece_comp();
            movePiece_comp('N');
        }
    }
    else if (play_mode == 2)
    {
        if (knock_present)
        {
            rand_num = rand() % 3;
            if (rand_num == 0)
            {
                index = 0;

                do
                {
                    y[0] = source_y[index];
                    x[0] = source_x[index];

                    total_comp_knocks = maxKnocks_comp();
                    total_player_knocks = maxKnocks_player();

                    if ((total_comp_knocks >= total_player_knocks && !selected) ||
                        (total_comp_knocks >= total_player_knocks && total_comp_knocks > max_knocks))
                    {
                        max_knocks = total_comp_knocks;
                        for (s = 0; s < 8; s++)
                        {
                            for (t = 0; t < 4; t++)
                            {
                                temp_board[s][t] = temp_board2[s][t];
                            }
                        }

                        selected = true;
                    }

                    index++;

                } while (index < total_knocks);

                if (selected)
                {
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            board[s][t] = temp_board[s][t];
                        }
                    }

                    moved = true;
                }
            }
            else if (rand_num != 0)
            {
                knocks_checking(&total_knocks);
                rand_num = rand() % total_knocks;

                y[0] = source_y[rand_num];
                x[0] = source_x[rand_num];
                y[1] = target_y[rand_num];
                x[1] = target_x[rand_num];

                movePiece_comp('Y');
                moreKnocks_comp();

                while (knock_present)
                {
                    movePiece_comp('Y');
                    moreKnocks_comp();
                }

                moved = true;
            }
        }

        if (!moved)
        {
            playersKnock_remove();
            if (!removed_knock)
            {
                playersKnock_block();
                if (blocked_knock)
                {
                    moved = true;
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            board[s][t] = temp_board1[s][t];
                        }
                    }
                }
            }
            else if (removed_knock)
            {
                moved = true;
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        board[s][t] = temp_board1[s][t];
                    }
                }
            }

            if (!moved)
                knock_creation();

            if (!knock_created && !moved)
            {
                short int player_pieces{};
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        if (board[s][t] == 'x' || board[s][t] == 'X')
                        {
                            player_pieces++; /* player pieces count */
                        }
                    }
                }

                if (!blocked_knock && !removed_knock && player_pieces < 5)
                    player_hunt();

                while (!moved && !hunted)
                {
                    for (short int re_do = 0; re_do < 1000; re_do++)
                    {
                        selectPiece_comp();

                        y[2] = y[0];
                        x[2] = x[0];
                        y[3] = y[1];
                        x[3] = x[1];

                        future_playersKnock(true);

                        if (!future_knock)
                        {
                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    board[s][t] = temp_board1[s][t];
                                }
                            }

                            moved = true;
                        }

                        if (moved)
                            break;
                        else if (re_do == 75)
                        {
                            selectPiece_comp();
                            movePiece_comp('N');

                            moved = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (play_mode == 3)
    {
        if (knock_present)
        {
            index = 0;

            do
            {
                y[0] = source_y[index];
                x[0] = source_x[index];

                total_comp_knocks = maxKnocks_comp();
                total_player_knocks = maxKnocks_player();

                if ((total_comp_knocks >= total_player_knocks && !selected) ||
                    (total_comp_knocks >= total_player_knocks && total_comp_knocks > max_knocks))
                {
                    max_knocks = total_comp_knocks;
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            temp_board[s][t] = temp_board2[s][t];
                        }
                    }

                    selected = true;
                }

                index++;

            } while (index < total_knocks);

            if (selected)
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        board[s][t] = temp_board[s][t];
                    }
                }

                moved = true;
            }
        }

        if (!moved)
        {
            best_move();
        }
    }

    std::cout << std::endl;
    print_board();
}

void knocks_checking(short int *total_knocks)
{
    knock_present = false;
    *total_knocks = 0;

    for (short int s = 0; s <= 7; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && (board[s + 1][t + 1] == 'x' || board[s + 1][t + 1] == 'X') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && board[s][t] == 'O')
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s + 2;
                target_x[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (board[s + 1][t] == 'x' || board[s + 1][t] == 'X') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && board[s][t] == 'O')
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s + 2;
                target_x[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (board[s + 1][t] == 'x' || board[s + 1][t] == 'X') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && board[s][t] == 'O')
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s + 2;
                target_x[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (board[s + 1][t - 1] == 'x' || board[s + 1][t - 1] == 'X') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && board[s][t] == 'O')
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s + 2;
                target_x[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 3 && (board[s - 1][t + 1] == 'x' || board[s - 1][t + 1] == 'X') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s - 2;
                target_x[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (board[s - 1][t] == 'x' || board[s - 1][t] == 'X') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s - 2;
                target_x[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (board[s - 1][t] == 'x' || board[s - 1][t] == 'X') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s - 2;
                target_x[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (board[s - 1][t - 1] == 'x' || board[s - 1][t - 1] == 'X') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                source_y[*total_knocks] = s;
                source_x[*total_knocks] = t;
                target_y[*total_knocks] = s - 2;
                target_x[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
        }
    }

    if (*total_knocks > 0)
        knock_present = true;
}

short int total_compMoves()
{
    short int count{};
    for (short int s = 0; s < 8; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            // downwards rightwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && (board[s][t] == 'O' || board[s][t] == 'o') && (board[s - 1][t] == ' ' || board[s - 1][t] == '.'))
            {
                count++;
            }
            // downwards leftwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && t != 0 && (board[s][t] == 'O' || board[s][t] == 'o') && (board[s - 1][t - 1] == ' ' || board[s - 1][t - 1] == '.'))
            {
                count++;
            }
            // downwards rightwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 3 && (board[s][t] == 'O' || board[s][t] == 'o') && (board[s - 1][t + 1] == ' ' || board[s - 1][t + 1] == '.'))
            {
                count++;
            }
            // downwards leftwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 0 && (board[s][t] == 'O' || board[s][t] == 'o') && (board[s - 1][t] == ' ' || board[s - 1][t] == '.'))
            {
                count++;
            }
            // upwards rightwards - odd
            if ((s == 1 || s == 5 || s == 3) && board[s][t] == 'O' && (board[s + 1][t] == ' ' || board[s + 1][t] == '.'))
            {
                count++;
            }
            // upwards leftwards - odd
            if ((s == 1 || s == 5 || s == 3) && t != 0 && board[s][t] == 'O' && (board[s + 1][t - 1] == ' ' || board[s + 1][t - 1] == '.'))
            {
                count++;
            }
            // upwards rightwards - even
            if ((s == 0 || s == 4 || s == 2 || s == 6) && t != 3 && board[s][t] == 'O' && (board[s + 1][t + 1] == ' ' || board[s + 1][t + 1] == '.'))
            {
                count++;
            }
            // upwards leftwards - even
            if ((s == 0 || s == 4 || s == 2) && board[s][t] == 'O' && (board[s + 1][t] == ' ' || board[s + 1][t] == '.'))
            {
                count++;
            }
        }
    }

    return count;
}

short int total_unknockMoves()
{
    short int count{};
    for (short int s = 0; s < 8; s++)
    {
        for (short int t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && board[s + 1][t + 1] == ' ' && board[s + 2][t + 1] != 'X' &&
                ((board[s][t + 1] != 'x' && board[s][t + 1] != 'X') || ((board[s][t + 1] == 'x' || board[s][t + 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t + 1] != ' ')) && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t + 1;
                count++;
            }
            if (s == 6 && t != 3 && board[s + 1][t + 1] == ' ' && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t + 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && board[s + 1][t] == ' ' && board[s + 2][t + 1] != 'X' &&
                ((board[s][t + 1] != 'x' && board[s][t + 1] != 'X') || ((board[s][t + 1] == 'x' || board[s][t + 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t + 1] != ' ')) && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t == 3 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && board[s + 1][t] == ' ' && board[s + 2][t - 1] != 'X' &&
                ((board[s][t - 1] != 'x' && board[s][t - 1] != 'X') || ((board[s][t - 1] == 'x' || board[s][t - 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t - 1] != ' ')) && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t;
                count++;
            }
            if (s == 6 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t == 0 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && board[s + 2][t - 1] != 'X' &&
                ((board[s][t - 1] != 'x' && board[s][t - 1] != 'X') || ((board[s][t - 1] == 'x' || board[s][t - 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t - 1] != ' ')) && board[s][t] == 'O')
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s + 1;
                target_x[count] = t - 1;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t != 3 && board[s - 1][t] == ' ' && board[s - 2][t + 1] != 'X' && board[s - 2][t + 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'X' || (board[s][t + 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t == 3 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t;
                count++;
            }
            if (s == 1 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s - 1][t + 1] == ' ' && board[s - 2][t + 1] != 'X' && board[s - 2][t + 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'X' || (board[s][t + 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t + 1;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t != 0 && board[s - 1][t - 1] == ' ' && board[s - 2][t - 1] != 'X' && board[s - 2][t - 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'X' || (board[s][t - 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t - 1;
                count++;
            }
            if (s == 1 && t != 0 && board[s - 1][t - 1] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t - 1;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s - 1][t] == ' ' && board[s - 2][t - 1] != 'X' && board[s - 2][t - 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'X' || (board[s][t - 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t == 0 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                source_y[count] = s;
                source_x[count] = t;
                target_y[count] = s - 1;
                target_x[count] = t;
                count++;
            }
        }
    }

    return count;
}

void selectPiece_comp()
{
    selected = false;

    if (play_mode == 2)
    {
        short int total_moves{};
        total_moves = total_unknockMoves();

        if (total_moves > 0)
        {
            rand_num = rand() % total_moves;
            y[0] = source_y[rand_num];
            x[0] = source_x[rand_num];
            selected = true;
        }
    }

    short int count{};
    while (!selected)
    {
        y[0] = rand() % 8;

        for (short int s = 0; s < 75; s++)
        {
            x[0] = rand() % 4;
            choice[0] = rand() % 8;
            count = 0;

            do
            {
                if (choice[0] == 0 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.') && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 1 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == ' ' || board[y[0] + 1][x[0] + 1] == '.') && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 2 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.') && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 3 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == ' ' || board[y[0] + 1][x[0] - 1] == '.') && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 4 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.') && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 5 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (board[y[0] - 1][x[0] + 1] == ' ' || board[y[0] - 1][x[0] + 1] == '.') && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 6 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.') && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 7 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == ' ' || board[y[0] - 1][x[0] - 1] == '.') && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }

                count++;
                choice[0]++;
                if (choice[0] == 8)
                    choice[0] = 0;

            } while (count <= 8 && !selected);

            if (selected)
                break;
        }
    }

    count = 0;

    // downwards rightwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.'))
    {
        target_y[count] = y[0] - 1;
        target_x[count] = x[0];
        count++;
    }
    // downwards leftwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && (board[y[0] - 1][x[0] - 1] == ' ' || board[y[0] - 1][x[0] - 1] == '.'))
    {
        target_y[count] = y[0] - 1;
        target_x[count] = x[0] - 1;
        count++;
    }
    // downwards rightwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && (board[y[0] - 1][x[0] + 1] == ' ' || board[y[0] - 1][x[0] + 1] == '.'))
    {
        target_y[count] = y[0] - 1;
        target_x[count] = x[0] + 1;
        count++;
    }
    // downwards leftwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && (board[y[0] - 1][x[0]] == ' ' || board[y[0] - 1][x[0]] == '.'))
    {
        target_y[count] = y[0] - 1;
        target_x[count] = x[0];
        count++;
    }
    // upwards rightwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && board[y[0]][x[0]] == 'O' && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
    {
        target_y[count] = y[0] + 1;
        target_x[count] = x[0];
        count++;
    }
    // upwards leftwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && board[y[0]][x[0]] == 'O' && (board[y[0] + 1][x[0] - 1] == ' ' || board[y[0] + 1][x[0] - 1] == '.'))
    {
        target_y[count] = y[0] + 1;
        target_x[count] = x[0] - 1;
        count++;
    }
    // upwards rightwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && board[y[0]][x[0]] == 'O' && (board[y[0] + 1][x[0] + 1] == ' ' || board[y[0] + 1][x[0] + 1] == '.'))
    {
        target_y[count] = y[0] + 1;
        target_x[count] = x[0] + 1;
        count++;
    }
    // upwards leftwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && board[y[0]][x[0]] == 'O' && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
    {
        target_y[count] = y[0] + 1;
        target_x[count] = x[0];
        count++;
    }

    rand_num = rand() % count;
    y[1] = target_y[rand_num];
    x[1] = target_x[rand_num];
}

void movePiece_comp(char knock)
{
    if (y[0] + 1 == y[1] && knock == 'N' && board[y[0]][x[0]] == 'O')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
    }
    else if (y[0] - 1 == y[1] && knock == 'N' && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] && (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.'))
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0]][x[0]] = '.';
        }
    }
    else if (y[0] + 2 == y[1] && board[y[0]][x[0]] == 'O' && knock == 'Y')
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == 'x' || board[y[0] + 1][x[0] - 1] == 'X') &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] - 1] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] + 1][x[0]] == 'x' || board[y[0] + 1][x[0]] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] + 1][x[0]] == 'x' || board[y[0] + 1][x[0]] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == 'x' || board[y[0] + 1][x[0] + 1] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] + 1] = '.';
        }
    }
    else if (y[0] - 2 == y[1] && knock == 'Y' && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == 'x' || board[y[0] - 1][x[0] - 1] == 'X') &&
            (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0] - 1][x[0] - 1] = '.';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] - 1][x[0]] == 'x' || board[y[0] - 1][x[0]] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0] - 1][x[0]] = '.';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] - 1][x[0]] == 'x' || board[y[0] - 1][x[0]] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0] - 1][x[0]] = '.';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] - 1][x[0] + 1] == 'x' || board[y[0] - 1][x[0] + 1] == 'X') &&
                 (board[y[1]][x[1]] == ' ' || board[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            if (board[y[0]][x[0]] == 'O')
            {
                board[y[1]][x[1]] = 'O';
            }
            else
            {
                board[y[1]][x[1]] = 'o';
            }

            board[y[0] - 1][x[0] + 1] = '.';
            board[y[0]][x[0]] = '.';
        }
    }

    for (short int s = 0; s < 4; s++)
    {
        if (board[0][s] == 'o')
        {
            board[0][s] = 'O';
        }
    }
}

void moreKnocks_comp()
{
    knock_present = false;
    choice[0] = rand() % 8;

    short int count{};
    if (board[y[1]][x[1]] == 'O' || board[y[1]][x[1]] == 'o')
    {
        y[0] = y[1];
        x[0] = x[1];

        count = 0;
        while (count < 8)
        {
            if (choice[0] == 0 && (y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] - 1][x[1] - 1] == 'x' || board[y[1] - 1][x[1] - 1] == 'X') &&
                (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.') && (board[y[1]][x[1]] == 'O' || board[y[1]][x[1]] == 'o'))
            {
                knock_present = true;
                y[1] = y[1] - 2;
                x[1] = x[1] - 1;
                break;
            }
            if (choice[0] == 1 && (y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] - 1][x[1]] == 'x' || board[y[1] - 1][x[1]] == 'X') &&
                (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.') && (board[y[1]][x[1]] == 'O' || board[y[1]][x[1]] == 'o'))
            {
                knock_present = true;
                y[1] = y[1] - 2;
                x[1] = x[1] + 1;
                break;
            }
            if (choice[0] == 2 && (y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] - 1][x[1]] == 'x' || board[y[1] - 1][x[1]] == 'X') &&
                (board[y[1] - 2][x[1] - 1] == ' ' || board[y[1] - 2][x[1] - 1] == '.') && (board[y[1]][x[1]] == 'O' || board[y[1]][x[1]] == 'o'))
            {
                knock_present = true;
                y[1] = y[1] - 2;
                x[1] = x[1] - 1;
                break;
            }
            if (choice[0] == 3 && (y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] - 1][x[1] + 1] == 'x' || board[y[1] - 1][x[1] + 1] == 'X') &&
                (board[y[1] - 2][x[1] + 1] == ' ' || board[y[1] - 2][x[1] + 1] == '.') && (board[y[1]][x[1]] == 'O' || board[y[1]][x[1]] == 'o'))
            {
                knock_present = true;
                y[1] = y[1] - 2;
                x[1] = x[1] + 1;
                break;
            }
            if (choice[0] == 4 && (y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (board[y[1] + 1][x[1] - 1] == 'x' || board[y[1] + 1][x[1] - 1] == 'X') &&
                (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.') && board[y[1]][x[1]] == 'O')
            {
                knock_present = true;
                y[1] = y[1] + 2;
                x[1] = x[1] - 1;
                break;
            }
            if (choice[0] == 5 && (y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (board[y[1] + 1][x[1]] == 'x' || board[y[1] + 1][x[1]] == 'X') &&
                (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.') && board[y[1]][x[1]] == 'O')
            {
                knock_present = true;
                y[1] = y[1] + 2;
                x[1] = x[1] + 1;
                break;
            }
            if (choice[0] == 6 && (y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (board[y[1] + 1][x[1]] == 'x' || board[y[1] + 1][x[1]] == 'X') &&
                (board[y[1] + 2][x[1] - 1] == ' ' || board[y[1] + 2][x[1] - 1] == '.') && board[y[1]][x[1]] == 'O')
            {
                knock_present = true;
                y[1] = y[1] + 2;
                x[1] = x[1] - 1;
                break;
            }
            if (choice[0] == 7 && (y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (board[y[1] + 1][x[1] + 1] == 'x' || board[y[1] + 1][x[1] + 1] == 'X') &&
                (board[y[1] + 2][x[1] + 1] == ' ' || board[y[1] + 2][x[1] + 1] == '.') && board[y[1]][x[1]] == 'O')
            {
                knock_present = true;
                y[1] = y[1] + 2;
                x[1] = x[1] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }
}

void future_playersKnock(bool with_values)
{
    future_knock = false;
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board1[s][t] = board[s][t];
        }
    }

    if (with_values)
    {
        if (y[2] - 1 == y[3])
        {
            if ((y[2] == 7 || y[2] == 5 || y[2] == 3 || y[2] == 1) && (temp_board1[y[2]][x[2]] == 'O' || temp_board1[y[2]][x[2]] == 'o') && temp_board1[y[3]][x[3]] == ' ' && x[2] == x[3])
            {
                if (temp_board1[y[2]][x[2]] == 'O')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                }
                else
                {
                    temp_board1[y[3]][x[3]] = 'o';
                }

                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 7 || y[2] == 5 || y[2] == 3 || y[2] == 1) && x[2] != 0 && (temp_board1[y[2]][x[2]] == 'O' || temp_board1[y[2]][x[2]] == 'o') && temp_board1[y[3]][x[3]] == ' ' && x[2] - 1 == x[3])
            {
                if (temp_board1[y[2]][x[2]] == 'O')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                }
                else
                {
                    temp_board1[y[3]][x[3]] = 'o';
                }

                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 6 || y[2] == 4 || y[2] == 2) && x[2] != 3 && (temp_board1[y[2]][x[2]] == 'O' || temp_board1[y[2]][x[2]] == 'o') && temp_board1[y[3]][x[3]] == ' ' && x[2] + 1 == x[3])
            {
                if (temp_board1[y[2]][x[2]] == 'O')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                }
                else
                {
                    temp_board1[y[3]][x[3]] = 'o';
                }

                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 6 || y[2] == 4 || y[2] == 2) && (temp_board1[y[2]][x[2]] == 'O' || temp_board1[y[2]][x[2]] == 'o') && temp_board1[y[3]][x[3]] == ' ' && x[2] == x[3])
            {
                if (temp_board1[y[2]][x[2]] == 'O')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                }
                else
                {
                    temp_board1[y[3]][x[3]] = 'o';
                }

                temp_board1[y[2]][x[2]] = '.';
            }
        }
        else if (y[2] + 1 == y[3])
        {
            if ((y[2] == 1 || y[2] == 5 || y[2] == 3) && temp_board1[y[2]][x[2]] == 'O' && temp_board1[y[3]][x[3]] == ' ' && x[2] == x[3])
            {
                temp_board1[y[3]][x[3]] = 'O';
                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 1 || y[2] == 5 || y[2] == 3) && x[2] != 0 && temp_board1[y[2]][x[2]] == 'O' && temp_board1[y[3]][x[3]] == ' ' && x[2] - 1 == x[3])
            {
                temp_board1[y[3]][x[3]] = 'O';
                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 0 || y[2] == 4 || y[2] == 2 || y[2] == 6) && x[2] != 3 && temp_board1[y[2]][x[2]] == 'O' && temp_board1[y[3]][x[3]] == ' ' && x[2] + 1 == x[3])
            {
                temp_board1[y[3]][x[3]] = 'O';
                temp_board1[y[2]][x[2]] = '.';
            }
            else if ((y[2] == 0 || y[2] == 4 || y[2] == 2) && temp_board1[y[2]][x[2]] == 'O' && temp_board1[y[3]][x[3]] == ' ' && x[2] == x[3])
            {
                temp_board1[y[3]][x[3]] = 'O';
                temp_board1[y[2]][x[2]] = '.';
            }
        }

        for (t = 0; t < 4; t++)
        {
            if (temp_board1[0][t] == 'o')
            {
                temp_board1[0][t] = 'O';
            }
        }
    }

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && (temp_board1[s + 1][t + 1] == 'o' || temp_board1[s + 1][t + 1] == 'O') &&
                (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                future_knock = true;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                future_knock = true;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                future_knock = true;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (temp_board1[s + 1][t - 1] == 'o' || temp_board1[s + 1][t - 1] == 'O') &&
                (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                future_knock = true;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 3 && (temp_board1[s - 1][t + 1] == 'o' || temp_board1[s - 1][t + 1] == 'O') &&
                (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
            {
                future_knock = true;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
            {
                future_knock = true;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
            {
                future_knock = true;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (temp_board1[s - 1][t - 1] == 'o' || temp_board1[s - 1][t - 1] == 'O') &&
                (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
            {
                future_knock = true;
            }
        }
    }
}

short int maxKnocks_comp()
{
    short int max_knocks{};
    bool proceed{false};

    short int s{};
    short int t{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        short int total_knocks{};
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                temp_board1[s][t] = board[s][t];
            }
        }

        const short int initial_Y = y[0];
        const short int initial_X = x[0];

        for (y[3] = 0; y[3] < 8; y[3]++)
        {
            const short int temp_y3 = y[3];
            for (x[3] = 0; x[3] < 4; x[3]++)
            {
                const short int temp_x3 = x[3];
                knock_present = false;

                do
                {
                    proceed = false;
                    if (y[2] + 2 == y[3] && temp_board1[y[2]][x[2]] == 'O')
                    {
                        if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') &&
                            (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                        {
                            proceed = true;
                            temp_board1[y[3]][x[3]] = 'O';
                            temp_board1[y[2]][x[2]] = '.';
                            temp_board1[y[2] + 1][x[2] - 1] = '.';
                        }
                        else if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                        {
                            proceed = true;
                            temp_board1[y[3]][x[3]] = 'O';
                            temp_board1[y[2]][x[2]] = '.';
                            temp_board1[y[2] + 1][x[2]] = '.';
                        }
                        else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                        {
                            proceed = true;
                            temp_board1[y[3]][x[3]] = 'O';
                            temp_board1[y[2]][x[2]] = '.';
                            temp_board1[y[2] + 1][x[2]] = '.';
                        }
                        else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                        {
                            proceed = true;
                            temp_board1[y[3]][x[3]] = 'O';
                            temp_board1[y[2]][x[2]] = '.';
                            temp_board1[y[2] + 1][x[2] + 1] = '.';
                        }
                    }
                    else if (y[2] - 2 == y[3])
                    {
                        if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') &&
                            (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                        {
                            proceed = true;
                            if (temp_board1[y[2]][x[2]] == 'O')
                            {
                                temp_board1[y[3]][x[3]] = 'O';
                            }
                            else
                            {
                                temp_board1[y[3]][x[3]] = 'o';
                            }

                            temp_board1[y[2] - 1][x[2] - 1] = '.';
                            temp_board1[y[2]][x[2]] = '.';
                        }
                        else if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                        {
                            proceed = true;
                            if (temp_board1[y[2]][x[2]] == 'O')
                            {
                                temp_board1[y[3]][x[3]] = 'O';
                            }
                            else
                            {
                                temp_board1[y[3]][x[3]] = 'o';
                            }

                            temp_board1[y[2] - 1][x[2]] = '.';
                            temp_board1[y[2]][x[2]] = '.';
                        }
                        else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                        {
                            proceed = true;
                            if (temp_board1[y[2]][x[2]] == 'O')
                            {
                                temp_board1[y[3]][x[3]] = 'O';
                            }
                            else
                            {
                                temp_board1[y[3]][x[3]] = 'o';
                            }

                            temp_board1[y[2] - 1][x[2]] = '.';
                            temp_board1[y[2]][x[2]] = '.';
                        }
                        else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] - 1][x[2] + 1] == 'x' || temp_board1[y[2] - 1][x[2] + 1] == 'X') &&
                                 (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                        {
                            proceed = true;
                            if (temp_board1[y[2]][x[2]] == 'O')
                            {
                                temp_board1[y[3]][x[3]] = 'O';
                            }
                            else
                            {
                                temp_board1[y[3]][x[3]] = 'o';
                            }

                            temp_board1[y[2] - 1][x[2] + 1] = '.';
                            temp_board1[y[2]][x[2]] = '.';
                        }
                    }

                    if (proceed)
                    {
                        for (s = 0; s < 4; s++)
                        {
                            if (temp_board1[0][s] == 'o')
                            {
                                temp_board1[0][s] = 'O';
                            }
                        }

                        total_knocks++;

                        if (total_knocks > max_knocks)
                        {
                            max_knocks = total_knocks;
                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    temp_board2[s][t] = temp_board1[s][t];
                                }
                            }
                        }

                        future_more_knocks();
                    }

                } while (knock_present);

                total_knocks = 0;

                y[2] = initial_Y;
                x[2] = initial_X;

                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = board[s][t];
                    }
                }

                x[3] = temp_x3;
            }

            y[3] = temp_y3;
        }
    }

    return max_knocks;
}

void future_more_knocks()
{
    knock_present = false;
    choice[0] = rand() % 8;

    short int count{};
    if (temp_board1[y[3]][x[3]] == 'O' || temp_board1[y[3]][x[3]] == 'o')
    {
        y[2] = y[3];
        x[2] = x[3];

        count = 0;
        while (count < 8)
        {
            if (choice[0] == 0 && (y[2] == 7 || y[2] == 3 || y[2] == 5) && x[3] != 0 && (temp_board1[y[2] - 1][x[3] - 1] == 'x' || temp_board1[y[2] - 1][x[3] - 1] == 'X') &&
                (temp_board1[y[2] - 2][x[3] - 1] == ' ' || temp_board1[y[2] - 2][x[3] - 1] == '.') && (temp_board1[y[2]][x[3]] == 'O' || temp_board1[y[2]][x[3]] == 'o'))
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 1 && (y[2] == 7 || y[2] == 3 || y[2] == 5) && x[3] != 3 && (temp_board1[y[2] - 1][x[3]] == 'x' || temp_board1[y[2] - 1][x[3]] == 'X') &&
                (temp_board1[y[2] - 2][x[3] + 1] == ' ' || temp_board1[y[2] - 2][x[3] + 1] == '.') && (temp_board1[y[2]][x[3]] == 'O' || temp_board1[y[2]][x[3]] == 'o'))
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] + 1;
                break;
            }
            if (choice[0] == 2 && (y[2] == 6 || y[2] == 2 || y[2] == 4) && x[3] != 0 && (temp_board1[y[2] - 1][x[3]] == 'x' || temp_board1[y[2] - 1][x[3]] == 'X') &&
                (temp_board1[y[2] - 2][x[3] - 1] == ' ' || temp_board1[y[2] - 2][x[3] - 1] == '.') && (temp_board1[y[2]][x[3]] == 'O' || temp_board1[y[2]][x[3]] == 'o'))
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 3 && (y[2] == 6 || y[2] == 2 || y[2] == 4) && x[3] != 3 && (temp_board1[y[2] - 1][x[3] + 1] == 'x' || temp_board1[y[2] - 1][x[3] + 1] == 'X') &&
                (temp_board1[y[2] - 2][x[3] + 1] == ' ' || temp_board1[y[2] - 2][x[3] + 1] == '.') && (temp_board1[y[2]][x[3]] == 'O' || temp_board1[y[2]][x[3]] == 'o'))
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] + 1;
                break;
            }
            if (choice[0] == 4 && (y[2] == 1 || y[2] == 3 || y[2] == 5) && x[3] != 0 && (temp_board1[y[2] + 1][x[3] - 1] == 'x' || temp_board1[y[2] + 1][x[3] - 1] == 'X') &&
                (temp_board1[y[2] + 2][x[3] - 1] == ' ' || temp_board1[y[2] + 2][x[3] - 1] == '.') && temp_board1[y[2]][x[3]] == 'O')
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 5 && (y[2] == 1 || y[2] == 3 || y[2] == 5) && x[3] != 3 && (temp_board1[y[2] + 1][x[3]] == 'x' || temp_board1[y[2] + 1][x[3]] == 'X') &&
                (temp_board1[y[2] + 2][x[3] + 1] == ' ' || temp_board1[y[2] + 2][x[3] + 1] == '.') && temp_board1[y[2]][x[3]] == 'O')
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] + 1;
                break;
            }
            if (choice[0] == 6 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && x[3] != 0 && (temp_board1[y[2] + 1][x[3]] == 'x' || temp_board1[y[2] + 1][x[3]] == 'X') &&
                (temp_board1[y[2] + 2][x[3] - 1] == ' ' || temp_board1[y[2] + 2][x[3] - 1] == '.') && temp_board1[y[2]][x[3]] == 'O')
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 7 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && x[3] != 3 && (temp_board1[y[2] + 1][x[3] + 1] == 'x' || temp_board1[y[2] + 1][x[3] + 1] == 'X') &&
                (temp_board1[y[2] + 2][x[3] + 1] == ' ' || temp_board1[y[2] + 2][x[3] + 1] == '.') && temp_board1[y[2]][x[3]] == 'O')
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }
    else if (temp_board1[y[3]][x[3]] == 'X' || temp_board1[y[3]][x[3]] == 'x')
    {
        y[2] = y[3];
        x[2] = x[3];

        count = 0;
        while (count < 8)
        {
            if (choice[0] == 0 && (y[2] == 1 || y[2] == 3 || y[2] == 5) && x[3] != 0 && (temp_board1[y[2] + 1][x[3] - 1] == 'o' || temp_board1[y[2] + 1][x[3] - 1] == 'O') &&
                (temp_board1[y[2] + 2][x[3] - 1] == ' ' || temp_board1[y[2] + 2][x[3] - 1] == '.') && (temp_board1[y[2]][x[3]] == 'x' || temp_board1[y[2]][x[3]] == 'X'))
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 1 && (y[2] == 1 || y[2] == 3 || y[2] == 5) && x[3] != 3 && (temp_board1[y[2] + 1][x[3]] == 'o' || temp_board1[y[2] + 1][x[3]] == 'O') &&
                (temp_board1[y[2] + 2][x[3] + 1] == ' ' || temp_board1[y[2] + 2][x[3] + 1] == '.') && (temp_board1[y[2]][x[3]] == 'x' || temp_board1[y[2]][x[3]] == 'X'))
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] + 1;
                break;
            }
            if (choice[0] == 2 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && x[3] != 0 && (temp_board1[y[2] + 1][x[3]] == 'o' || temp_board1[y[2] + 1][x[3]] == 'O') &&
                (temp_board1[y[2] + 2][x[3] - 1] == ' ' || temp_board1[y[2] + 2][x[3] - 1] == '.') && (temp_board1[y[2]][x[3]] == 'x' || temp_board1[y[2]][x[3]] == 'X'))
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 3 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && x[3] != 3 && (temp_board1[y[2] + 1][x[3] + 1] == 'o' || temp_board1[y[2] + 1][x[3] + 1] == 'O') &&
                (temp_board1[y[2] + 2][x[3] + 1] == ' ' || temp_board1[y[2] + 2][x[3] + 1] == '.') && (temp_board1[y[2]][x[3]] == 'x' || temp_board1[y[2]][x[3]] == 'X'))
            {
                knock_present = true;
                y[3] = y[2] + 2;
                x[3] = x[3] + 1;
                break;
            }

            if (choice[0] == 4 && (y[2] == 7 || y[2] == 3 || y[2] == 5) && x[3] != 0 && (temp_board1[y[2] - 1][x[3] - 1] == 'o' || temp_board1[y[2] - 1][x[3] - 1] == 'O') &&
                (temp_board1[y[2] - 2][x[3] - 1] == ' ' || temp_board1[y[2] - 2][x[3] - 1] == '.') && temp_board1[y[2]][x[3]] == 'X')
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 5 && (y[2] == 7 || y[2] == 3 || y[2] == 5) && x[3] != 3 && (temp_board1[y[2] - 1][x[3]] == 'o' || temp_board1[y[2] - 1][x[3]] == 'O') &&
                (temp_board1[y[2] - 2][x[3] + 1] == ' ' || temp_board1[y[2] - 2][x[3] + 1] == '.') && temp_board1[y[2]][x[3]] == 'X')
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] + 1;
                break;
            }
            if (choice[0] == 6 && (y[2] == 6 || y[2] == 2 || y[2] == 4) && x[3] != 0 && (temp_board1[y[2] - 1][x[3]] == 'o' || temp_board1[y[2] - 1][x[3]] == 'O') &&
                (temp_board1[y[2] - 2][x[3] - 1] == ' ' || temp_board1[y[2] - 2][x[3] - 1] == '.') && temp_board1[y[2]][x[3]] == 'X')
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] - 1;
                break;
            }
            if (choice[0] == 7 && (y[2] == 6 || y[2] == 2 || y[2] == 4) && x[3] != 3 && (temp_board1[y[2] - 1][x[3] + 1] == 'o' || temp_board1[y[2] - 1][x[3] + 1] == 'O') &&
                (temp_board1[y[2] - 2][x[3] + 1] == ' ' || temp_board1[y[2] - 2][x[3] + 1] == '.') && temp_board1[y[2]][x[3]] == 'X')
            {
                knock_present = true;
                y[3] = y[2] - 2;
                x[3] = x[3] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }
}

short int maxKnocks_player()
{
    short int max_knocks{};
    short int total_knocks{};

    short int s{};
    short int t{};

    bool proceed = false;

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (y[2] = 0; y[2] < 8; y[2]++)
        {
            for (x[2] = 0; x[2] < 4; x[2]++)
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = temp_board2[s][t];
                    }
                }

                if (temp_board1[y[2]][x[2]] == 'x' || temp_board1[y[2]][x[2]] == 'X')
                {
                    const short int initial_Y = y[2];
                    const short int initial_X = x[2];

                    total_knocks = 0;

                    for (y[3] = 0; y[3] < 8; y[3]++)
                    {
                        const short int temp_y3 = y[3];

                        for (x[3] = 0; x[3] < 4; x[3]++)
                        {
                            const short int temp_x3 = x[3];
                            knock_present = false;

                            do
                            {
                                proceed = false;
                                if (y[2] + 2 == y[3])
                                {
                                    if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] + 1][x[2] - 1] == 'o' || temp_board1[y[2] + 1][x[2] - 1] == 'O') &&
                                        (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;

                                        if (temp_board1[y[2]][x[2]] == 'X')
                                        {
                                            temp_board1[y[3]][x[3]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'x';
                                        }

                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                                    }
                                    else if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] + 1][x[2]] == 'o' || temp_board1[y[2] + 1][x[2]] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;

                                        if (temp_board1[y[2]][x[2]] == 'X')
                                        {
                                            temp_board1[y[3]][x[3]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'x';
                                        }

                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2]] = '.';
                                    }
                                    else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] + 1][x[2]] == 'o' || temp_board1[y[2] + 1][x[2]] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;

                                        if (temp_board1[y[2]][x[2]] == 'X')
                                        {
                                            temp_board1[y[3]][x[3]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'x';
                                        }

                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2]] = '.';
                                    }
                                    else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] + 1][x[2] + 1] == 'o' || temp_board1[y[2] + 1][x[2] + 1] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;

                                        if (temp_board1[y[2]][x[2]] == 'X')
                                        {
                                            temp_board1[y[3]][x[3]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'x';
                                        }

                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                                    }
                                }
                                else if (y[2] - 2 == y[3] && temp_board1[y[2]][x[2]] == 'X')
                                {
                                    if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] - 1][x[2] - 1] == 'o' || temp_board1[y[2] - 1][x[2] - 1] == 'O') &&
                                        (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'X';
                                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] - 1][x[2]] == 'o' || temp_board1[y[2] - 1][x[2]] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'X';
                                        temp_board1[y[2] - 1][x[2]] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] - 1][x[2]] == 'o' || temp_board1[y[2] - 1][x[2]] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'X';
                                        temp_board1[y[2] - 1][x[2]] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] - 1][x[2] + 1] == 'o' || temp_board1[y[2] - 1][x[2] + 1] == 'O') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'X';
                                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    for (t = 0; t < 4; t++)
                                    {
                                        if (temp_board1[7][t] == 'x')
                                        {
                                            temp_board1[7][t] = 'X';
                                        }
                                    }

                                    total_knocks++;

                                    if (total_knocks > max_knocks)
                                    {
                                        max_knocks = total_knocks;

                                        for (s = 0; s < 8; s++)
                                        {
                                            for (t = 0; t < 4; t++)
                                            {
                                                temp_board3[s][t] = temp_board1[s][t];
                                            }
                                        }
                                    }

                                    future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            y[2] = initial_Y;
                            x[2] = initial_X;

                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    temp_board1[s][t] = temp_board2[s][t];
                                }
                            }

                            x[3] = temp_x3;
                        }

                        y[3] = temp_y3;
                    }
                }
            }
        }
    }

    return max_knocks;
}

void best_move()
{
    char final_board[8][4]{};
    bool target_chosen{false};

    short int total_comp_knocks[2]{};
    short int total_player_knocks[2]{};

    short int s{};
    short int t{};

    short int temp_y0[35]{};
    short int temp_x0[35]{};
    short int temp_y1[35]{};
    short int temp_x1[35]{};

    knock_antidote();
    if (knock_encounted)
    {
        target_chosen = true;
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                final_board[s][t] = temp_board1[s][t];
            }
        }

        total_comp_knocks[0] = triple_play(&total_player_knocks[0]);
        std::cout << "\n        target chosen[0]: " << target_chosen;
    }

    short int total_moves = total_unknockMoves();
    short int count{};

    if (total_moves != 0)
    {
        for (s = 0; s < total_moves; s++)
        {
            temp_y0[s] = source_y[s];
            temp_x0[s] = source_x[s];
            temp_y1[s] = target_y[s];
            temp_x1[s] = target_x[s];
        }

        if (target_chosen)
        {
            while (count < total_moves)
            {
                y[2] = temp_y0[count];
                x[2] = temp_x0[count];
                y[3] = temp_y1[count];
                x[3] = temp_x1[count];

                future_playersKnock(true);
                total_comp_knocks[1] = triple_play(&total_player_knocks[0]);
                if (total_comp_knocks[1] > total_comp_knocks[0] && total_comp_knocks[1] > total_player_knocks[0])
                {
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            final_board[s][t] = temp_board2[s][t];
                        }
                    }
                }

                count++;
            }
        }
        else if (!target_chosen)
        {
            knock_creation();
            if (!knock_created)
            {
                player_hunt();
                if (!hunted)
                {
                    rand_num = rand() % total_moves;
                    while (count <= total_moves)
                    {
                        y[2] = temp_y0[rand_num];
                        x[2] = temp_x0[rand_num];
                        y[3] = temp_y1[rand_num];
                        x[3] = temp_x1[rand_num];

                        future_playersKnock(true);
                        total_comp_knocks[0] = triple_play(&total_player_knocks[0]);

                        count++;
                        rand_num++;
                        if (rand_num == total_moves)
                            rand_num = 0;

                        y[2] = temp_y0[rand_num];
                        x[2] = temp_x0[rand_num];
                        y[3] = temp_y1[rand_num];
                        x[3] = temp_x1[rand_num];

                        future_playersKnock(true);
                        total_comp_knocks[1] = triple_play(&total_player_knocks[0]);

                        if (total_comp_knocks[1] > total_comp_knocks[0] && total_comp_knocks[1] > total_player_knocks[0])
                        {
                            target_chosen = true;
                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    final_board[s][t] = temp_board2[s][t];
                                }
                            }
                            std::cout << "\n        target chosen[1]: " << target_chosen;
                        }
                    }

                    if (!target_chosen)
                    {
                        for (short int re_do = 0; re_do < 100; re_do++)
                        {
                            rand_num = rand() % total_moves;

                            y[2] = temp_y0[rand_num];
                            x[2] = temp_x0[rand_num];
                            y[3] = temp_y1[rand_num];
                            x[3] = temp_x1[rand_num];

                            future_playersKnock(true);

                            if (!future_knock)
                            {
                                for (s = 0; s < 8; s++)
                                {
                                    for (t = 0; t < 4; t++)
                                    {
                                        board[s][t] = temp_board1[s][t];
                                    }
                                }

                                break;
                            }

                            if (re_do == 50)
                            {
                                rand_num = rand() % total_moves;

                                y[0] = temp_y0[rand_num];
                                x[0] = temp_x0[rand_num];
                                y[1] = temp_y1[rand_num];
                                x[1] = temp_x1[rand_num];

                                movePiece_comp('N');

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (total_moves == 0)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                if ((s == 0 || s == 2 || s == 4 || s == 6) && board[s + 1][t] == ' ' && board[s][t] == 'O')
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s + 1;
                    temp_x1[total_moves] = t;
                    total_moves++;
                }
                if ((s == 0 || s == 2 || s == 4 || s == 6) && t != 3 && board[s + 1][t + 1] == ' ' && board[s][t] == 'O')
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s + 1;
                    temp_x1[total_moves] = t + 1;
                    total_moves++;
                }
                if ((s == 1 || s == 3 || s == 5) && board[s + 1][t] == ' ' && board[s][t] == 'O')
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s + 1;
                    temp_x1[total_moves] = t;
                    total_moves++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && board[s][t] == 'O')
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s + 1;
                    temp_x1[total_moves] = t - 1;
                    total_moves++;
                }
                if ((s == 2 || s == 4 || s == 6) && board[s - 1][t] == ' ' && (board[s][t] == 'o' || board[s][t] == 'O'))
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s - 1;
                    temp_x1[total_moves] = t;
                    total_moves++;
                }
                if ((s == 2 || s == 4 || s == 6) && t != 3 && board[s - 1][t + 1] == ' ' && (board[s][t] == 'o' || board[s][t] == 'O'))
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s - 1;
                    temp_x1[total_moves] = t + 1;
                    total_moves++;
                }
                if ((s == 1 || s == 3 || s == 5 || s == 7) && board[s - 1][t] == ' ' && (board[s][t] == 'o' || board[s][t] == 'O'))
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s - 1;
                    temp_x1[total_moves] = t;
                    total_moves++;
                }
                if ((s == 1 || s == 3 || s == 5 || s == 7) && t != 0 && board[s - 1][t - 1] == ' ' && (board[s][t] == 'o' || board[s][t] == 'O'))
                {
                    temp_y0[total_moves] = s;
                    temp_x0[total_moves] = t;
                    temp_y1[total_moves] = s - 1;
                    temp_x1[total_moves] = t - 1;
                    total_moves++;
                }
            }
        }

        rand_num = rand() % total_moves;
        while (count <= total_moves)
        {
            y[2] = temp_y0[rand_num];
            x[2] = temp_x0[rand_num];
            y[3] = temp_y1[rand_num];
            x[3] = temp_x1[rand_num];

            future_playersKnock(true);
            triple_play(&total_player_knocks[0]);

            count++;
            rand_num++;
            if (rand_num == total_moves)
                rand_num = 0;

            y[2] = temp_y0[rand_num];
            x[2] = temp_x0[rand_num];
            y[3] = temp_y1[rand_num];
            x[3] = temp_x1[rand_num];

            future_playersKnock(true);
            triple_play(&total_player_knocks[1]);

            if (total_player_knocks[1] < total_player_knocks[0])
            {
                target_chosen = true;
                std::cout << "\n        target chosen[2]: " << target_chosen;
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_board2[s][t];
                    }
                }
            }
        }

        if (!target_chosen)
        {
            rand_num = rand() % total_moves;

            y[0] = temp_y0[rand_num];
            x[0] = temp_x0[rand_num];
            y[1] = temp_y1[rand_num];
            x[1] = temp_x1[rand_num];

            movePiece_comp('N');
        }

        std::cout << "\n        target chosen[3]: " << target_chosen;
    }

    if (target_chosen)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                board[s][t] = final_board[s][t];
                if (board[0][t] == 'o')
                {
                    board[0][t] = 'O';
                }
            }
        }
    }
}

short int triple_play(short int *total_player_knocks)
{
    short int s{};
    short int t{};

    bool proceed{false};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board2[s][t] = temp_board1[s][t];
        }
    }

    *total_player_knocks = maxKnocks_player();
    if (*total_player_knocks == 0)
    {
        proceed = playerMove_prediction();
        if (!proceed)
        {
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board3[s][t] = temp_board2[s][t];
                }
            }
        }
    }

    //* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    short int total_comp_knocks{};
    short int total_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (y[2] = 0; y[2] < 8; y[2]++)
        {
            for (x[2] = 0; x[2] < 4; x[2]++)
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = temp_board3[s][t];
                    }
                }

                if (temp_board1[y[2]][x[2]] == 'O' || temp_board1[y[2]][x[2]] == 'o')
                {
                    const short int initial_Y = y[2];
                    const short int initial_X = x[2];

                    total_knocks = 0;

                    for (y[3] = 0; y[3] < 8; y[3]++)
                    {
                        const unsigned short int temp_y3 = y[3];

                        for (x[3] = 0; x[3] < 4; x[3]++)
                        {
                            const unsigned short int temp_x3 = x[3];
                            knock_present = false;

                            do
                            {
                                proceed = false;
                                if (y[2] + 2 == y[3] && temp_board1[y[2]][x[2]] == 'O')
                                {
                                    if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') &&
                                        (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'O';
                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                                    }
                                    else if ((y[2] == 1 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'O';
                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2]] = '.';
                                    }
                                    else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'O';
                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2]] = '.';
                                    }
                                    else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        temp_board1[y[3]][x[3]] = 'O';
                                        temp_board1[y[2]][x[2]] = '.';
                                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                                    }
                                }
                                else if (y[2] - 2 == y[3])
                                {
                                    if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 0 && (temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') &&
                                        (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        if (temp_board1[y[2]][x[2]] == 'O')
                                        {
                                            temp_board1[y[3]][x[3]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'o';
                                        }

                                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 7 || y[2] == 3 || y[2] == 5) && x[2] != 3 && (temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        if (temp_board1[y[2]][x[2]] == 'O')
                                        {
                                            temp_board1[y[3]][x[3]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'o';
                                        }

                                        temp_board1[y[2] - 1][x[2]] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 0 && (temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] - 1 == x[3])
                                    {
                                        proceed = true;
                                        if (temp_board1[y[2]][x[2]] == 'O')
                                        {
                                            temp_board1[y[3]][x[3]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'o';
                                        }

                                        temp_board1[y[2] - 1][x[2]] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                    else if ((y[2] == 6 || y[2] == 2 || y[2] == 4) && x[2] != 3 && (temp_board1[y[2] - 1][x[2] + 1] == 'x' || temp_board1[y[2] - 1][x[2] + 1] == 'X') &&
                                             (temp_board1[y[3]][x[3]] == ' ' || temp_board1[y[3]][x[3]] == '.') && x[2] + 1 == x[3])
                                    {
                                        proceed = true;
                                        if (temp_board1[y[2]][x[2]] == 'O')
                                        {
                                            temp_board1[y[3]][x[3]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[y[3]][x[3]] = 'o';
                                        }

                                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                                        temp_board1[y[2]][x[2]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    for (t = 0; t < 4; t++)
                                    {
                                        if (temp_board1[0][t] == 'o')
                                        {
                                            temp_board1[0][t] = 'O';
                                        }
                                    }

                                    total_knocks++;

                                    y[2] = y[3];
                                    x[2] = x[3];

                                    total_comp_knocks = (total_knocks > total_comp_knocks) ? total_knocks : total_comp_knocks;

                                    future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            y[2] = initial_Y;
                            x[2] = initial_X;

                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    temp_board1[s][t] = temp_board3[s][t];
                                }
                            }

                            x[3] = temp_x3;
                        }

                        y[3] = temp_y3;
                    }
                }
            }
        }
    }

    //* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return total_comp_knocks;
}

bool playerMove_prediction()
{

    bool proceed = false;
    char org_board[8][4]{};

    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board3[s][t] = temp_board1[s][t];
        }
    }

    short int count{};

    short int temp_y0[20]{};
    short int temp_x0[20]{};
    short int temp_y1[20]{};
    short int temp_x1[20]{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && temp_board1[s + 1][t + 1] == ' ' && temp_board1[s + 2][t + 1] != 'O' && temp_board1[s + 2][t + 1] != 'o' &&
                ((temp_board1[s + 2][t] != 'o' && temp_board1[s + 2][t] != 'O') || ((temp_board1[s + 2][t] == 'o' || temp_board1[s + 2][t] == 'O') && temp_board1[s][t + 1] != ' ')) &&
                (temp_board1[s][t + 1] != 'O' || (temp_board1[s][t + 1] == 'O' && temp_board1[s + 2][t] != ' ')) && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t + 1;
                count++;
            }
            if (s == 6 && t != 3 && temp_board1[s + 1][t + 1] == ' ' && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && temp_board1[s + 1][t] == ' ' && temp_board1[s + 2][t + 1] != 'o' && temp_board1[s + 2][t + 1] != 'O' &&
                ((temp_board1[s + 2][t] != 'o' && temp_board1[s + 2][t] != 'O') || ((temp_board1[s + 2][t] == 'o' || temp_board1[s + 2][t] == 'O') && temp_board1[s][t + 1] != ' ')) &&
                (temp_board1[s][t + 1] != 'O' || (temp_board1[s][t + 1] == 'O' && temp_board1[s + 2][t] != ' ')) && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t == 3 && temp_board1[s + 1][t] == ' ' && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && temp_board1[s + 1][t] == ' ' && temp_board1[s + 2][t - 1] != 'O' && temp_board1[s + 2][t - 1] != 'o' &&
                ((temp_board1[s + 2][t] != 'o' && temp_board1[s + 2][t] != 'O') || ((temp_board1[s + 2][t] == 'o' || temp_board1[s + 2][t] == 'O') && temp_board1[s][t - 1] != ' ')) &&
                (temp_board1[s][t - 1] != 'O' || (temp_board1[s][t - 1] == 'O' && temp_board1[s + 2][t] != ' ')) && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t;
                count++;
            }
            if (s == 6 && temp_board1[s + 1][t] == ' ' && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t == 0 && temp_board1[s + 1][t] == ' ' && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && temp_board1[s + 1][t - 1] == ' ' && temp_board1[s + 2][t - 1] != 'O' && temp_board1[s + 2][t - 1] != 'o' &&
                ((temp_board1[s + 2][t] != 'o' && temp_board1[s + 2][t] != 'O') || ((temp_board1[s + 2][t] == 'o' || temp_board1[s + 2][t] == 'O') && temp_board1[s][t - 1] != ' ')) &&
                (temp_board1[s][t - 1] != 'O' || (temp_board1[s][t - 1] == 'O' && temp_board1[s + 2][t] != ' ')) && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 1;
                temp_x1[count] = t - 1;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t != 3 && temp_board1[s - 1][t] == ' ' && temp_board1[s - 2][t + 1] != 'O' &&
                ((temp_board1[s][t + 1] != 'o' && temp_board1[s][t + 1] != 'O') || ((temp_board1[s][t + 1] == 'o' || temp_board1[s][t + 1] == 'O') && temp_board1[s - 2][t] != ' ')) &&
                (temp_board1[s - 2][t] != 'O' || (temp_board1[s - 2][t] == 'O' && temp_board1[s][t + 1] != ' ')) && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t == 3 && temp_board1[s - 1][t] == ' ' && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t;
                count++;
            }
            if (s == 1 && temp_board1[s - 1][t] == ' ' && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && temp_board1[s - 1][t + 1] == ' ' && temp_board1[s - 2][t + 1] != 'O' &&
                ((temp_board1[s][t + 1] != 'o' && temp_board1[s][t + 1] != 'O') || ((temp_board1[s][t + 1] == 'o' || temp_board1[s][t + 1] == 'O') && temp_board1[s - 2][t] != ' ')) &&
                (temp_board1[s - 2][t] != 'O' || (temp_board1[s - 2][t] == 'O' && temp_board1[s][t + 1] != ' ')) && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t != 0 && temp_board1[s - 1][t - 1] == ' ' && temp_board1[s - 2][t - 1] != 'O' &&
                ((temp_board1[s][t - 1] != 'o' && temp_board1[s][t - 1] != 'O') || ((temp_board1[s][t - 1] == 'o' || temp_board1[s][t - 1] == 'O') && temp_board1[s - 2][t] != ' ')) &&
                (temp_board1[s - 2][t] != 'O' || (temp_board1[s - 2][t] == 'O' && temp_board1[s][t - 1] != ' ')) && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t - 1;
                count++;
            }
            if (s == 1 && t != 0 && temp_board1[s - 1][t - 1] == ' ' && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t - 1;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && temp_board1[s - 1][t] == ' ' && temp_board1[s - 2][t - 1] != 'O' &&
                ((temp_board1[s][t - 1] != 'o' && temp_board1[s][t - 1] != 'O') || ((temp_board1[s][t - 1] == 'o' || temp_board1[s][t - 1] == 'O') && temp_board1[s - 2][t] != ' ')) &&
                (temp_board1[s - 2][t] != 'O' || (temp_board1[s - 2][t] == 'O' && temp_board1[s][t - 1] != ' ')) && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t == 0 && temp_board1[s - 1][t] == ' ' && temp_board1[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 1;
                temp_x1[count] = t;
                count++;
            }
        }
    }

    if (count > 0)
    {
        proceed = true;
        rand_num = rand() % count;

        y[0] = temp_y0[rand_num];
        x[0] = temp_x0[rand_num];
        y[1] = temp_y1[rand_num];
        x[1] = temp_x1[rand_num];

        if (y[0] + 1 == y[1] && (temp_board3[y[0]][x[0]] == 'X' || temp_board3[y[0]][x[0]] == 'x'))
        {
            if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
                (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
            {
                if (temp_board3[y[0]][x[0]] == 'X')
                {
                    temp_board3[y[1]][x[1]] = 'X';
                }
                else
                {
                    temp_board3[y[1]][x[1]] = 'x';
                }

                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {

                if (temp_board3[y[0]][x[0]] == 'X')
                {
                    temp_board3[y[1]][x[1]] = 'X';
                }
                else
                {
                    temp_board3[y[1]][x[1]] = 'x';
                }

                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
            {

                if (temp_board3[y[0]][x[0]] == 'X')
                {
                    temp_board3[y[1]][x[1]] = 'X';
                }
                else
                {
                    temp_board3[y[1]][x[1]] = 'x';
                }

                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {

                if (temp_board3[y[0]][x[0]] == 'X')
                {
                    temp_board3[y[1]][x[1]] = 'X';
                }
                else
                {
                    temp_board3[y[1]][x[1]] = 'x';
                }

                temp_board3[y[0]][x[0]] = '.';
            }
        }
        else if (y[0] - 1 == y[1] && temp_board3[y[0]][x[0]] == 'X')
        {
            if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
                (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {
                temp_board3[y[1]][x[1]] = 'X';
                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {
                temp_board3[y[1]][x[1]] = 'X';
                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {
                temp_board3[y[1]][x[1]] = 'X';
                temp_board3[y[0]][x[0]] = '.';
            }
            else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                     (temp_board3[y[1]][x[1]] == ' ' || temp_board3[y[1]][x[1]] == '.'))
            {
                temp_board3[y[1]][x[1]] = 'X';
                temp_board3[y[0]][x[0]] = '.';
            }
        }
    }

    return proceed;
}

void playersKnock_remove()
{
    removed_knock = false;

    short int temp_y0[35]{};
    short int temp_x0[35]{};
    short int temp_y1[35]{};
    short int temp_x1[35]{};

    short int s{};
    short int t{};
    short int count{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board1[s][t] = board[s][t];
        }
    }

    if (play_mode != 3)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                if ((s == 0 || s == 2 || s == 4) && t != 3 && (temp_board1[s + 1][t + 1] == 'o' || temp_board1[s + 1][t + 1] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 0 || s == 2 || s == 4) && t != 0 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 3 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 0 && (temp_board1[s + 1][t - 1] == 'o' || temp_board1[s + 1][t - 1] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t - 1;
                    count++;
                }

                if ((s == 6 || s == 2 || s == 4) && t != 3 && (temp_board1[s - 1][t + 1] == 'o' || temp_board1[s - 1][t + 1] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 6 || s == 2 || s == 4) && t != 0 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 3 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 0 && (temp_board1[s - 1][t - 1] == 'o' || temp_board1[s - 1][t - 1] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {

            rand_num = rand() % count;

            y[2] = temp_y0[rand_num];
            x[2] = temp_x0[rand_num];
            y[3] = temp_y1[rand_num];
            x[3] = temp_x1[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7
        if (y[2] == 7 && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 0)
            {
                choice[0] = rand() % 3;

                do
                {

                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O')
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 1] != 'X' || (temp_board1[y[2] - 1][x[2] + 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O')
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 1] != 'X' || (temp_board1[y[2] - 1][x[2] + 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 7
        else if (y[2] == 7 && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X') || ((temp_board1[y[2] - 3][x[2] - 1] == 'x' || temp_board1[y[2] - 3][x[2] - 1] == 'X') && temp_board1[y[2] - 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2]] != 'X' || (temp_board1[y[2] - 1][x[2]] == 'X' && temp_board1[y[2] - 3][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 2 || x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 2] != 'x' && temp_board1[y[2] - 3][x[2] - 2] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X') || ((temp_board1[y[2] - 3][x[2] - 1] == 'x' || temp_board1[y[2] - 3][x[2] - 1] == 'X') && temp_board1[y[2] - 1][x[2] - 2] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 2] != 'X' || (temp_board1[y[2] - 1][x[2] - 2] == 'X' && temp_board1[y[2] - 3][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X') || ((temp_board1[y[2] - 3][x[2] - 1] == 'x' || temp_board1[y[2] - 3][x[2] - 1] == 'X') && temp_board1[y[2] - 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2]] != 'X' || (temp_board1[y[2] - 1][x[2]] == 'X' && temp_board1[y[2] - 3][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 6/4
        else if ((y[2] == 6 || y[2] == 4) && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X') || ((temp_board1[y[2] - 3][x[2] + 1] == 'x' || temp_board1[y[2] - 3][x[2] + 1] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2] + 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] + 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] + 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] == 'O')
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2)
                    {
                        if (temp_board1[y[2] - 1][x[2] + 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] + 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 0 || x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X') || ((temp_board1[y[2] - 3][x[2] + 1] == 'x' || temp_board1[y[2] - 3][x[2] + 1] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2] + 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] + 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] + 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] == 'O' && temp_board1[y[2] + 1][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] + 2] != 'x' && temp_board1[y[2] - 1][x[2] + 2] != 'X') || ((temp_board1[y[2] - 1][x[2] + 2] == 'x' || temp_board1[y[2] - 1][x[2] + 2] == 'X') && temp_board1[y[2] + 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] + 1] != 'X' || (temp_board1[y[2] + 1][x[2] + 1] == 'X' && temp_board1[y[2] - 1][x[2] + 2] != ' ')))
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 2] != 'x' && temp_board1[y[2] - 3][x[2] + 2] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X') || ((temp_board1[y[2] - 3][x[2] + 1] == 'x' || temp_board1[y[2] - 3][x[2] + 1] == 'X') && temp_board1[y[2] - 1][x[2] + 2] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 2] != 'X' || (temp_board1[y[2] - 1][x[2] + 2] == 'X' && temp_board1[y[2] - 3][x[2] + 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] + 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] + 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 6/4
        else if ((y[2] == 6 || y[2] == 4) && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O' && temp_board1[y[2] + 1][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] - 1] != 'x' && temp_board1[y[2] - 1][x[2] - 1] != 'X') || ((temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') && temp_board1[y[2] + 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2]] != 'X' || (temp_board1[y[2] + 1][x[2]] == 'X' && temp_board1[y[2] - 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2)
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X' &&
                        ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O' && temp_board1[y[2] + 1][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] - 1] != 'x' && temp_board1[y[2] - 1][x[2] - 1] != 'X') || ((temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') && temp_board1[y[2] + 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2]] != 'X' || (temp_board1[y[2] + 1][x[2]] == 'X' && temp_board1[y[2] - 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 1] != 'X' && temp_board1[y[2] - 3][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 1] != 'X' || (temp_board1[y[2] - 1][x[2] + 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 5/3
        else if ((y[2] == 5 || y[2] == 3) && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O' && temp_board1[y[2] + 1][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] + 1] != 'x' && temp_board1[y[2] - 1][x[2] + 1] != 'X') || ((temp_board1[y[2] - 1][x[2] + 1] == 'x' || temp_board1[y[2] - 1][x[2] + 1] == 'X') && temp_board1[y[2] + 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2]] != 'X' || (temp_board1[y[2] + 1][x[2]] == 'X' && temp_board1[y[2] - 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 1] != 'X' && temp_board1[y[2] - 3][x[2] + 1] != 'x' &&
                             ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 1] != 'X' || (temp_board1[y[2] - 1][x[2] + 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 1] != 'X' && temp_board1[y[2] - 3][x[2] - 1] != 'x' &&
                        ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O' && temp_board1[y[2] + 1][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] + 1] != 'x' && temp_board1[y[2] - 1][x[2] + 1] != 'X') || ((temp_board1[y[2] - 1][x[2] + 1] == 'x' || temp_board1[y[2] - 1][x[2] + 1] == 'X') && temp_board1[y[2] + 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2]] != 'X' || (temp_board1[y[2] + 1][x[2]] == 'X' && temp_board1[y[2] - 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2] + 1] != 'X' && temp_board1[y[2] - 3][x[2] + 1] != 'x' &&
                             ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2] + 1] != 'X' || (temp_board1[y[2] - 1][x[2] + 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2]] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2]] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 5/3
        else if ((y[2] == 5 || y[2] == 3) && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2]] != 'X' && temp_board1[y[2] - 3][x[2]] != 'x' &&
                             ((temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X') || ((temp_board1[y[2] - 3][x[2] - 1] == 'x' || temp_board1[y[2] - 3][x[2] - 1] == 'X') && temp_board1[y[2] - 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2]] != 'X' || (temp_board1[y[2] - 1][x[2]] == 'X' && temp_board1[y[2] - 3][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 2 || x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0 && temp_board1[y[2] - 3][x[2] - 2] != 'X' && temp_board1[y[2] - 3][x[2] - 2] != 'x' &&
                        ((temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X') || ((temp_board1[y[2] - 3][x[2]] == 'x' || temp_board1[y[2] - 3][x[2]] == 'X') && temp_board1[y[2] - 1][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] - 1][x[2] - 1] != 'X' || (temp_board1[y[2] - 1][x[2] - 1] == 'X' && temp_board1[y[2] - 3][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] == 'O' && temp_board1[y[2] + 1][x[2] - 2] != 'X' && temp_board1[y[2] + 1][x[2] - 2] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2] - 2] != 'x' && temp_board1[y[2] - 1][x[2] - 2] != 'X') || ((temp_board1[y[2] - 1][x[2] - 2] == 'x' || temp_board1[y[2] - 1][x[2] - 2] == 'X') && temp_board1[y[2] + 1][x[2] - 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] - 1] != 'X' || (temp_board1[y[2] + 1][x[2] - 1] == 'X' && temp_board1[y[2] - 1][x[2] - 2] != ' ')))
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2 && temp_board1[y[2] - 3][x[2]] != 'X' && temp_board1[y[2] - 3][x[2]] != 'x' &&
                             ((temp_board1[y[2] - 3][x[2] - 1] != 'x' && temp_board1[y[2] - 3][x[2] - 1] != 'X') || ((temp_board1[y[2] - 3][x[2] - 1] == 'x' || temp_board1[y[2] - 3][x[2] - 1] == 'X') && temp_board1[y[2] - 1][x[2]] != ' ')) &&
                             (temp_board1[y[2] - 1][x[2]] != 'X' || (temp_board1[y[2] - 1][x[2]] == 'X' && temp_board1[y[2] - 3][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'O';
                        }
                        else if (temp_board1[y[2] - 1][x[2] - 1] == 'o')
                        {
                            temp_board1[y[2] - 2][x[2]] = 'o';
                        }

                        temp_board1[y[2] - 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards rightwards... y0 --> 2
        else if (y[2] == 2 && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0)
                    {
                        temp_board1[y[2] - 2][x[2]] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] == 'O')
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 0 || x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 0)
                    {
                        temp_board1[y[2] - 2][x[2]] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] == 'O' && temp_board1[y[2] + 1][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] - 1][x[2] + 2] != 'x' && temp_board1[y[2] - 1][x[2] + 2] != 'X') || ((temp_board1[y[2] - 1][x[2] + 2] == 'x' || temp_board1[y[2] - 1][x[2] + 2] == 'X') && temp_board1[y[2] + 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] + 1] != 'X' || (temp_board1[y[2] + 1][x[2] + 1] == 'X' && temp_board1[y[2] - 1][x[2] + 2] != ' ')))
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] - 2][x[2] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_board1[y[2] - 2][x[2] + 1] = 'O';
                        temp_board1[y[2] - 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        // downwards leftwards... y0 --> 2
        else if (y[2] == 2 && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            choice[0] = rand() % 3;

            while (count < 4 && !removed_knock)
            {
                if (temp_board1[y[2] - 2][x[2] - 1] == ' ' && choice[0] == 0)
                {
                    temp_board1[y[2] - 2][x[2] - 1] = 'O';
                    temp_board1[y[2] - 1][x[2]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2]] == 'O' && temp_board1[y[2] + 1][x[2] - 1] != 'X' &&
                         ((temp_board1[y[2] - 1][x[2] - 1] != 'x' && temp_board1[y[2] - 1][x[2] - 1] != 'X') || ((temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') && temp_board1[y[2] + 1][x[2]] != ' ')) &&
                         (temp_board1[y[2] + 1][x[2]] != 'X' || (temp_board1[y[2] + 1][x[2]] == 'X' && temp_board1[y[2] - 1][x[2] - 1] != ' ')))
                {
                    temp_board1[y[2]][x[2] - 1] = 'O';
                    temp_board1[y[2] - 1][x[2]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[y[2] - 2][x[2]] == ' ' && choice[0] == 2)
                {
                    temp_board1[y[2] - 2][x[2]] = 'O';
                    temp_board1[y[2] - 1][x[2]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        //  upwards rightwards --> 0
        else if (y[2] == 0 && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'x' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] + 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 0 || x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'x' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[y[2]][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2] + 2] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] + 2] != 'x' && temp_board1[y[2] + 1][x[2] + 2] != 'X') || ((temp_board1[y[2] + 1][x[2] + 2] == 'x' || temp_board1[y[2] + 1][x[2] + 2] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2] + 2] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 0
        else if (y[2] == 0 && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] - 1] != 'x' && temp_board1[y[2] + 1][x[2] - 1] != 'X') || ((temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] + 1] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2] + 1] != 'x' && temp_board1[y[2] + 1][x[2] + 1] != 'X') || ((temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[y[2]][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] - 1] != 'x' && temp_board1[y[2] + 1][x[2] - 1] != 'X') || ((temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 1/3
        else if ((y[2] == 1 || y[2] == 3) && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] != 'X' && temp_board1[y[2] - 1][x[2] + 1] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2]] != 'x' && temp_board1[y[2] - 1][x[2]] != 'X') || ((temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') && temp_board1[y[2] + 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] + 1] != 'X' || (temp_board1[y[2] + 1][x[2] + 1] == 'X' && temp_board1[y[2] - 1][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2]] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2]] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] + 1] != 'x' && temp_board1[y[2] + 1][x[2] + 1] != 'X') || ((temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] - 1] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2] - 1] != 'x' && temp_board1[y[2] + 1][x[2] - 1] != 'X') || ((temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] != 'X' && temp_board1[y[2] - 1][x[2] + 1] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2]] != 'x' && temp_board1[y[2] - 1][x[2]] != 'X') || ((temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') && temp_board1[y[2] + 1][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] + 1] != 'X' || (temp_board1[y[2] + 1][x[2] + 1] == 'X' && temp_board1[y[2] - 1][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2]] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2]] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] + 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] + 1] != 'x' && temp_board1[y[2] + 1][x[2] + 1] != 'X') || ((temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 1/3
        else if ((y[2] == 1 || y[2] == 3) && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] - 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] - 1] != 'X' || (temp_board1[y[2] + 3][x[2] - 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[y[2] + 1][x[2] - 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] - 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 2 || x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] - 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] - 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] - 1] != 'X' || (temp_board1[y[2] + 3][x[2] - 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 2] != 'X' && temp_board1[y[2] - 1][x[2] - 2] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2] - 1] != 'x' && temp_board1[y[2] - 1][x[2] - 1] != 'X') || ((temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') && temp_board1[y[2] + 1][x[2] - 2] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] - 2] != 'X' || (temp_board1[y[2] + 1][x[2] - 2] == 'X' && temp_board1[y[2] - 1][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2] - 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] - 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] - 1] == 'O' && temp_board1[y[2] + 3][x[2] - 2] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] - 2] != 'x' && temp_board1[y[2] + 1][x[2] - 2] != 'X') || ((temp_board1[y[2] + 1][x[2] - 2] == 'x' || temp_board1[y[2] + 1][x[2] - 2] == 'X') && temp_board1[y[2] + 3][x[2] - 1] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2] - 1] != 'X' || (temp_board1[y[2] + 3][x[2] - 1] == 'X' && temp_board1[y[2] + 1][x[2] - 2] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 2/4
        else if ((y[2] == 2 || y[2] == 4) && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            if (x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[y[2] + 1][x[2] + 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] + 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] + 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2]] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2]] != 'x' && temp_board1[y[2] + 1][x[2]] != 'X') || ((temp_board1[y[2] + 1][x[2]] == 'x' || temp_board1[y[2] + 1][x[2]] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2]] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 2] != 'X' && temp_board1[y[2] - 1][x[2] + 2] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2] + 1] != 'x' && temp_board1[y[2] - 1][x[2] + 1] != 'X') || ((temp_board1[y[2] - 1][x[2] + 1] == 'x' || temp_board1[y[2] - 1][x[2] + 1] == 'X') && temp_board1[y[2] + 1][x[2] + 2] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] + 2] != 'X' || (temp_board1[y[2] + 1][x[2] + 2] == 'X' && temp_board1[y[2] - 1][x[2] + 1] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2] + 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] + 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] + 1] == 'O' && temp_board1[y[2] + 3][x[2] + 2] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] + 2] != 'x' && temp_board1[y[2] + 1][x[2] + 2] != 'X') || ((temp_board1[y[2] + 1][x[2] + 2] == 'x' || temp_board1[y[2] + 1][x[2] + 2] == 'X') && temp_board1[y[2] + 3][x[2] + 1] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2] + 1] != 'X' || (temp_board1[y[2] + 3][x[2] + 1] == 'X' && temp_board1[y[2] + 1][x[2] + 2] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] + 1] = 'O';
                        temp_board1[y[2] + 1][x[2] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards leftwards --> 2/4
        else if ((y[2] == 2 || y[2] == 4) && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] != 'X' && temp_board1[y[2] - 1][x[2] - 1] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2]] != 'x' && temp_board1[y[2] - 1][x[2]] != 'X') || ((temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') && temp_board1[y[2] + 1][x[2] - 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] - 1] != 'X' || (temp_board1[y[2] + 1][x[2] - 1] == 'X' && temp_board1[y[2] - 1][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2]] == 'O')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2]] == 'o')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] - 1] != 'x' && temp_board1[y[2] + 1][x[2] - 1] != 'X') || ((temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 1 || x[2] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] + 1] != 'X' &&
                        ((temp_board1[y[2] + 1][x[2] + 1] != 'x' && temp_board1[y[2] + 1][x[2] + 1] != 'X') || ((temp_board1[y[2] + 1][x[2] + 1] == 'x' || temp_board1[y[2] + 1][x[2] + 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                        (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] + 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 1] != 'X' && temp_board1[y[2] - 1][x[2] - 1] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2]] != 'x' && temp_board1[y[2] - 1][x[2]] != 'X') || ((temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') && temp_board1[y[2] + 1][x[2] - 1] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] - 1] != 'X' || (temp_board1[y[2] + 1][x[2] - 1] == 'X' && temp_board1[y[2] - 1][x[2]] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2]] == 'O')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2]] == 'o')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O' && temp_board1[y[2] + 3][x[2] - 1] != 'X' &&
                             ((temp_board1[y[2] + 1][x[2] - 1] != 'x' && temp_board1[y[2] + 1][x[2] - 1] != 'X') || ((temp_board1[y[2] + 1][x[2] - 1] == 'x' || temp_board1[y[2] + 1][x[2] - 1] == 'X') && temp_board1[y[2] + 3][x[2]] != ' ')) &&
                             (temp_board1[y[2] + 3][x[2]] != 'X' || (temp_board1[y[2] + 3][x[2]] == 'X' && temp_board1[y[2] + 1][x[2] - 1] != ' ')))
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }

        //  upwards rightwards --> 5
        else if (y[2] == 5 && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            choice[0] = rand() % 3;

            while (count < 4 && !removed_knock)
            {
                if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2]] == 'O')
                {
                    temp_board1[y[2] + 2][x[2]] = 'O';
                    temp_board1[y[2] + 1][x[2]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[y[2]][x[2] + 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] != 'X' && temp_board1[y[2] - 1][x[2] + 1] != 'x' &&
                         ((temp_board1[y[2] - 1][x[2]] != 'x' && temp_board1[y[2] - 1][x[2]] != 'X') || ((temp_board1[y[2] - 1][x[2]] == 'x' || temp_board1[y[2] - 1][x[2]] == 'X') && temp_board1[y[2] + 1][x[2] + 1] != ' ')) &&
                         (temp_board1[y[2] + 1][x[2] + 1] != 'X' || (temp_board1[y[2] + 1][x[2] + 1] == 'X' && temp_board1[y[2] - 1][x[2]] != ' ')))
                {
                    if (temp_board1[y[2] + 1][x[2]] == 'O')
                    {

                        temp_board1[y[2]][x[2] + 1] = 'O';
                    }
                    else if (temp_board1[y[2] + 1][x[2]] == 'o')
                    {

                        temp_board1[y[2]][x[2] + 1] = 'o';
                    }

                    temp_board1[y[2] + 1][x[2]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[y[2] + 2][x[2] + 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2]] == 'O')
                {
                    temp_board1[y[2] + 2][x[2] + 1] = 'O';
                    temp_board1[y[2] + 1][x[2]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        //  upwards leftwards --> 5
        else if (y[2] == 5 && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            if (x[2] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[y[2] + 1][x[2] - 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] - 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] + 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (x[2] == 2 || x[2] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[y[2] + 2][x[2]] == ' ' && choice[0] == 0 && temp_board1[y[2] + 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2]] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2]][x[2] - 1] == ' ' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] - 2] != 'X' && temp_board1[y[2] - 1][x[2] - 2] != 'x' &&
                             ((temp_board1[y[2] - 1][x[2] - 1] != 'x' && temp_board1[y[2] - 1][x[2] - 1] != 'X') || ((temp_board1[y[2] - 1][x[2] - 1] == 'x' || temp_board1[y[2] - 1][x[2] - 1] == 'X') && temp_board1[y[2] + 1][x[2] - 2] != ' ')) &&
                             (temp_board1[y[2] + 1][x[2] - 2] != 'X' || (temp_board1[y[2] + 1][x[2] - 2] == 'X' && temp_board1[y[2] - 1][x[2] - 1] != ' ')))
                    {
                        if (temp_board1[y[2] + 1][x[2] - 1] == 'O')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'O';
                        }
                        else if (temp_board1[y[2] + 1][x[2] - 1] == 'o')
                        {

                            temp_board1[y[2]][x[2] - 1] = 'o';
                        }

                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[y[2] + 2][x[2] - 1] == ' ' && choice[0] == 2 && temp_board1[y[2] + 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[2] + 2][x[2] - 1] = 'O';
                        temp_board1[y[2] + 1][x[2] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
        }
    }

    for (t = 0; t < 4; t++)
    {
        if (temp_board1[0][t] == 'o')
        {
            temp_board1[0][t] = 'O';
        }
    }
}

void playersKnock_block()
{
    blocked_knock = false;

    short int temp_y0[35]{};
    short int temp_x0[35]{};
    short int temp_y1[35]{};
    short int temp_x1[35]{};

    short int count{};
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board1[s][t] = board[s][t];
        }
    }

    if (play_mode != 3)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                if ((s == 0 || s == 2 || s == 4) && t != 3 && (temp_board1[s + 1][t + 1] == 'o' || temp_board1[s + 1][t + 1] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 0 || s == 2 || s == 4) && t != 0 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 3 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 0 && (temp_board1[s + 1][t - 1] == 'o' || temp_board1[s + 1][t - 1] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s + 2;
                    temp_x1[count] = t - 1;
                    count++;
                }

                if ((s == 6 || s == 2 || s == 4) && t != 3 && (temp_board1[s - 1][t + 1] == 'o' || temp_board1[s - 1][t + 1] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 6 || s == 2 || s == 4) && t != 0 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 3 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t + 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 0 && (temp_board1[s - 1][t - 1] == 'o' || temp_board1[s - 1][t - 1] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y0[count] = s;
                    temp_x0[count] = t;
                    temp_y1[count] = s - 2;
                    temp_x1[count] = t - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {
            rand_num = rand() % count;

            y[2] = temp_y0[rand_num];
            x[2] = temp_x0[rand_num];
            y[3] = temp_y1[rand_num];
            x[3] = temp_x1[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7/5/3
        if ((y[2] == 7 || y[2] == 5 || y[2] == 3) && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            choice[0] = rand() % 2;

            while (count < 3 && !blocked_knock)
            {
                if ((temp_board1[y[2] - 1][x[2] + 1] == 'o' || temp_board1[y[2] - 1][x[2] + 1] == 'O') && choice[0] == 0 && temp_board1[y[2] - 3][x[2]] != 'x' && temp_board1[y[2] - 3][x[2]] != 'X')
                {
                    if (temp_board1[y[2] - 1][x[2] + 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] - 1][x[2] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] - 3][x[2]] == 'O' && choice[0] == 1 && temp_board1[y[2] - 1][x[2] + 1] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;
            }
        }

        // downwards leftwards... y0 --> 7/5/3
        else if ((y[2] == 7 || y[2] == 5 || y[2] == 3) && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            choice[0] = rand() % 3;

            while (count < 4 && !blocked_knock)
            {
                if (temp_board1[y[2] - 3][x[2] - 1] == 'O' && choice[0] == 0 && x[3] == 0)
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] - 3][x[2] - 1] == 'O' && choice[0] == 1 && x[3] != 0 && temp_board1[y[2] - 1][x[2] - 2] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[y[2] - 1][x[2] - 2] == 'O' || temp_board1[y[2] - 1][x[2] - 2] == 'o') && choice[0] == 2 && x[3] != 0 && temp_board1[y[2] - 3][x[2] - 1] != 'X' && temp_board1[y[2] - 3][x[2] - 1] != 'x')
                {
                    if (temp_board1[y[2] - 1][x[2] - 2] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] - 1][x[2] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        // downwards rightwards... y0 --> 6/4
        else if ((y[2] == 6 || y[2] == 4) && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            choice[0] = rand() % 3;

            while (count < 4 && !blocked_knock)
            {
                if ((temp_board1[y[2] - 1][x[2] + 2] == 'o' || temp_board1[y[2] - 1][x[2] + 2] == 'O') && choice[0] == 0 && x[3] != 3 && temp_board1[y[2] - 3][x[2] + 1] != 'x' && temp_board1[y[2] - 3][x[2] + 1] != 'X')
                {
                    if (temp_board1[y[2] - 1][x[2] + 2] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] - 1][x[2] + 2] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] - 3][x[2] + 1] == 'O' && choice[0] == 1 && x[3] != 3 && temp_board1[y[2] - 1][x[2] + 2] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] - 3][x[2] + 1] == 'O' && choice[0] == 2 && x[3] == 3)
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2] + 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        // downwards leftwards... y0 --> 6/4
        else if ((y[2] == 6 || y[2] == 4) && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            choice[0] = rand() % 2;

            while (count < 3 && !blocked_knock)
            {
                if (temp_board1[y[2] - 3][x[2]] == 'O' && choice[0] == 0 && temp_board1[y[2] - 1][x[2] - 1] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] - 3][x[2]] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[y[2] - 1][x[2] - 1] == 'O' || temp_board1[y[2] - 1][x[2] - 1] == 'o') && choice[0] == 1 && temp_board1[y[2] - 3][x[2]] != 'X' && temp_board1[y[2] - 3][x[2]] != 'x')
                {
                    if (temp_board1[y[2] - 1][x[2] - 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] - 1][x[2] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;
            }
        }

        // downwards rightwards... y0 --> 2
        else if (y[2] == 2 && y[3] == y[2] - 2 && x[3] == x[2] + 1 && x[2] != 3 && x[2] != 2 &&
                 (temp_board1[y[2] - 1][x[2] + 2] == 'o' || temp_board1[y[2] - 1][x[2] + 2] == 'O'))
        {
            temp_board1[y[3]][x[3]] = 'O';
            temp_board1[y[2] - 1][x[2] + 2] = '.';
            blocked_knock = true;
        }

        // downwards leftwards... y0 --> 2
        else if (y[2] == 2 && y[3] == y[2] - 2 && x[3] == x[2] - 1 && x[2] != 0 &&
                 (temp_board1[y[2] - 1][x[2] - 1] == 'O' || temp_board1[y[2] - 1][x[2] - 1] == 'o'))
        {
            temp_board1[y[3]][x[3]] = 'O';
            temp_board1[y[2] - 1][x[2] - 1] = '.';
            blocked_knock = true;
        }

        //  upwards rightwards --> 0/2/4
        else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            choice[0] = rand() % 3;

            while (count < 4 && !blocked_knock)
            {
                if ((temp_board1[y[2] + 3][x[2] + 1] == 'o' || temp_board1[y[2] + 3][x[2] + 1] == 'O') && choice[0] == 0 && x[3] != 3 && temp_board1[y[2] + 1][x[2] + 2] != 'x' && temp_board1[y[2] + 1][x[2] + 2] != 'X')
                {
                    if (temp_board1[y[2] + 3][x[2] + 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[y[2] + 3][x[2] + 1] == 'o' || temp_board1[y[2] + 3][x[2] + 1] == 'O') && choice[0] == 1 && x[3] == 3)
                {
                    if (temp_board1[y[2] + 3][x[2] + 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] + 1][x[2] + 2] == 'O' && choice[0] == 2 && x[3] != 3 && temp_board1[y[2] + 3][x[2] + 1] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] + 1][x[2] + 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        //  upwards leftwards --> 0/2/4
        else if ((y[2] == 0 || y[2] == 2 || y[2] == 4) && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            choice[0] = rand() % 2;

            while (count < 3 && !blocked_knock)
            {
                if ((temp_board1[y[2] + 3][x[2]] == 'O' || temp_board1[y[2] + 3][x[2]] == 'o') && choice[0] == 0 && temp_board1[y[2] + 1][x[2] - 1] != 'X' && temp_board1[y[2] + 1][x[2] - 1] != 'x')
                {
                    if (temp_board1[y[2] + 3][x[2]] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2]] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] + 1][x[2] - 1] == 'O' && choice[0] == 1 && temp_board1[y[2] + 3][x[2]] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] + 1][x[2] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;
            }
        }

        //  upwards rightwards --> 1/3
        else if ((y[2] == 1 || y[2] == 3) && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3)
        {
            choice[0] = rand() % 2;

            while (count < 3 && !blocked_knock)
            {
                if (temp_board1[y[2] + 1][x[2] + 1] == 'O' && choice[0] == 0 && temp_board1[y[2] + 3][x[2]] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] + 1][x[2] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[y[2] + 3][x[2]] == 'o' || temp_board1[y[2] + 3][x[2]] == 'O') && choice[0] == 1 && temp_board1[y[2] + 1][x[2] + 1] != 'X' && temp_board1[y[2] + 1][x[2] + 1] != 'x')
                {
                    if (temp_board1[y[2] + 3][x[2]] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;
            }
        }

        //  upwards leftwards --> 1/3
        else if ((y[2] == 1 || y[2] == 3) && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0)
        {
            choice[0] = rand() % 3;

            while (count < 3 && !blocked_knock)
            {
                if ((temp_board1[y[2] + 3][x[2] - 1] == 'O' || temp_board1[y[2] + 3][x[2] - 1] == 'o') && choice[0] == 0 && x[3] != 0 && temp_board1[y[2] + 1][x[2] - 2] != 'X' && temp_board1[y[2] + 1][x[2] - 2] != 'x')
                {
                    if (temp_board1[y[2] + 3][x[2] - 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[y[2] + 3][x[2] - 1] == 'O' || temp_board1[y[2] + 3][x[2] - 1] == 'o') && choice[0] == 1 && x[3] == 0)
                {
                    if (temp_board1[y[2] + 3][x[2] - 1] == 'O')
                    {
                        temp_board1[y[3]][x[3]] = 'O';
                    }
                    else
                    {
                        temp_board1[y[3]][x[3]] = 'o';
                    }

                    temp_board1[y[2] + 3][x[2] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[y[2] + 1][x[2] - 2] == 'O' && choice[0] == 2 && x[3] != 0 && temp_board1[y[2] + 3][x[2] - 1] != 'X')
                {
                    temp_board1[y[3]][x[3]] = 'O';
                    temp_board1[y[2] + 1][x[2] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;
            }
        }

        //  upwards rightwards --> 5
        else if (y[2] == 5 && y[3] == y[2] + 2 && x[3] == x[2] + 1 && x[2] != 3 &&
                 temp_board1[y[2] + 1][x[2] + 1] == 'O')
        {
            temp_board1[y[3]][x[3]] = 'O';
            temp_board1[y[2] + 1][x[2] + 1] = '.';
            blocked_knock = true;
        }

        //  upwards leftwards --> 5
        else if (y[2] == 5 && y[3] == y[2] + 2 && x[3] == x[2] - 1 && x[2] != 0 && x[2] != 1 &&
                 temp_board1[y[2] + 1][x[2] - 2] == 'O')
        {
            temp_board1[y[3]][x[3]] = 'O';
            temp_board1[y[2] + 1][x[2] - 2] = '.';
            blocked_knock = true;
        }
    }

    for (t = 0; t < 4; t++)
    {
        if (temp_board1[0][t] == 'o')
        {
            temp_board1[0][t] = 'O';
        }
    }
}

void knock_antidote()
{
    knock_encounted = false;

    short int temp_y0[35]{};
    short int temp_x0[35]{};
    short int temp_y1[35]{};
    short int temp_x1[35]{};

    short int count{};
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && (board[s + 1][t + 1] == 'o' || board[s + 1][t + 1] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 2;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 2;
                temp_x1[count] = t - 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 2;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (board[s + 1][t - 1] == 'o' || board[s + 1][t - 1] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s + 2;
                temp_x1[count] = t - 1;
                count++;
            }

            if ((s == 6 || s == 2 || s == 4) && t != 3 && (board[s - 1][t + 1] == 'o' || board[s - 1][t + 1] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 2;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 2;
                temp_x1[count] = t - 1;
                count++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 2;
                temp_x1[count] = t + 1;
                count++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (board[s - 1][t - 1] == 'o' || board[s - 1][t - 1] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                temp_y0[count] = s;
                temp_x0[count] = t;
                temp_y1[count] = s - 2;
                temp_x1[count] = t - 1;
                count++;
            }
        }
    }

    if (count > 0)
    {
        short int index{};
        short int totalKnocks_b{};
        short int totalKnocks_r{};
        char final_board[8][4]{};

        while (index < count)
        {
            y[2] = temp_y0[index];
            x[2] = temp_x0[index];
            y[3] = temp_y1[index];
            x[3] = temp_x1[index];

            playersKnock_block();
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board2[s][t] = temp_board1[s][t];
                }
            }

            totalKnocks_b = maxKnocks_player();

            if ((blocked_knock && !knock_encounted) || totalKnocks_b < totalKnocks_r)
            {
                knock_encounted = true;
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_board2[s][t];
                    }
                }
            }

            playersKnock_remove();
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board2[s][t] = temp_board1[s][t];
                }
            }

            totalKnocks_r = maxKnocks_player();

            if ((removed_knock && !knock_encounted) || totalKnocks_r < totalKnocks_b)
            {
                knock_encounted = true;
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_board2[s][t];
                    }
                }
            }

            index++;
        }

        if (knock_encounted)
        {
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board1[s][t] = final_board[s][t];
                }
            }
        }
    }
    std::cout << "\n        knock antidote: " << knock_encounted;
}

void player_hunt()
{
    hunted = false;

    short int temp_y0[35]{};
    short int temp_y1[35]{};
    short int temp_x0[35]{};
    short int temp_x1[35]{};

    short int row_o[20]{};
    short int column_o[20]{};
    short int count[4]{};
    short int section{};

    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // upwards rightwards
            if ((s == 0 || s == 2 || s == 4) && t != 3 && board[s + 1][t + 1] == ' ' && board[s + 2][t + 1] != 'O' && board[s + 2][t + 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'O' || (board[s][t + 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t + 1;
                count[0]++;
                section = 1;
            }

            //* ////////////////////////////
            if (section != 1 && (s == 0 || s == 2 || s == 4) && t != 3 && board[s + 1][t + 1] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row_o[count[1]] = s + 2;
                column_o[count[1]] = t + 1;
                count[1]++;
            }
            // * ///////////////////////////

            if (s == 6 && t != 3 && board[s + 1][t + 1] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t + 1;
                count[0]++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && board[s + 1][t] == ' ' && board[s + 2][t + 1] != 'o' && board[s + 2][t + 1] != 'O' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'O' || (board[s][t + 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t;
                count[0]++;
                section = 2;
            }

            //* /////////////////////////////
            if (section != 2 && (s == 1 || s == 3 || s == 5) && t != 3 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row_o[count[1]] = s + 2;
                column_o[count[1]] = t + 1;
                count[1]++;
            }
            //* ////////////////////////////

            if ((s == 1 || s == 3 || s == 5) && t == 3 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }

            // upwards leftwards
            if ((s == 0 || s == 2 || s == 4) && t != 0 && board[s + 1][t] == ' ' && board[s + 2][t - 1] != 'O' && board[s + 2][t - 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'O' || (board[s][t - 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t;
                count[0]++;
                section = 3;
            }

            //* //////////////////////////////
            if (section != 3 && (s == 0 || s == 2 || s == 4) && t != 0 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row_o[count[1]] = s + 2;
                column_o[count[1]] = t - 1;
                count[1]++;
            }
            //* //////////////////////////////

            if (s == 6 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }
            if ((s == 0 || s == 2 || s == 4) && t == 0 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && board[s + 2][t - 1] != 'O' && board[s + 2][t - 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'O' || (board[s][t - 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s + 1;
                temp_x1[count[0]] = t - 1;
                count[0]++;
                section = 4;
            }

            //* ///////////////////////////////
            if (section != 4 && (s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row_o[count[1]] = s + 2;
                column_o[count[1]] = t - 1;
                count[1]++;
            }
            //* ///////////////////////////////

            // downwards rightwards
            if ((s == 7 || s == 5 || s == 3) && t != 3 && board[s - 1][t] == ' ' && board[s - 2][t + 1] != 'O' &&
                ((board[s][t + 1] != 'o' && board[s][t + 1] != 'O') || ((board[s][t + 1] == 'o' || board[s][t + 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t + 1] != ' ')) && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t;
                count[0]++;
                section = 5;
            }

            //* ///////////////////////////////
            if (section != 5 && (s == 7 || s == 5 || s == 3) && t != 3 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                row_o[count[1]] = s - 2;
                column_o[count[1]] = t + 1;
                count[1]++;
            }
            //* ///////////////////////////////

            if ((s == 7 || s == 5 || s == 3) && t == 3 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }
            if (s == 1 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s - 1][t + 1] == ' ' && board[s - 2][t + 1] != 'O' &&
                ((board[s][t + 1] != 'o' && board[s][t + 1] != 'O') || ((board[s][t + 1] == 'o' || board[s][t + 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t + 1] != ' ')) && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t + 1;
                count[0]++;
                section = 6;
            }

            //* ///////////////////////////////
            if (section != 6 && (s == 6 || s == 4 || s == 2) && t != 3 && board[s - 1][t + 1] == ' ' && board[s][t] == 'X')
            {
                row_o[count[1]] = s - 2;
                column_o[count[1]] = t + 1;
                count[1]++;
            }
            //* ///////////////////////////////

            // downwards leftwards
            if ((s == 7 || s == 5 || s == 3) && t != 0 && board[s - 1][t - 1] == ' ' && board[s - 2][t - 1] != 'O' &&
                ((board[s][t - 1] != 'o' && board[s][t - 1] != 'O') || ((board[s][t - 1] == 'o' || board[s][t - 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t - 1] != ' ')) && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t - 1;
                count[0]++;
                section = 7;
            }

            //* ///////////////////////////////
            if (section != 7 && (s == 7 || s == 5 || s == 3) && t != 0 && board[s - 1][t - 1] == ' ' && board[s][t] == 'X')
            {
                row_o[count[1]] = s - 2;
                column_o[count[1]] = t - 1;
                count[1]++;
            }
            //* ///////////////////////////////

            if (s == 1 && t != 0 && board[s - 1][t - 1] == ' ' && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t - 1;
                count[0]++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s - 1][t] == ' ' && board[s - 2][t - 1] != 'O' &&
                ((board[s][t - 1] != 'o' && board[s][t - 1] != 'O') || ((board[s][t - 1] == 'o' || board[s][t - 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t - 1] != ' ')) && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t;
                count[0]++;
                section = 8;
            }

            //* ///////////////////////////////
            if (section != 8 && (s == 6 || s == 4 || s == 2) && t != 0 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                row_o[count[1]] = s - 2;
                column_o[count[1]] = t - 1;
                count[1]++;
            }
            //* ///////////////////////////////

            if ((s == 6 || s == 4 || s == 2) && t == 0 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                temp_y0[count[0]] = s;
                temp_x0[count[0]] = t;
                temp_y1[count[0]] = s - 1;
                temp_x1[count[0]] = t;
                count[0]++;
            }
        }
    }

    short int free_y0[20]{};
    short int free_y1[20]{};
    short int free_x0[20]{};
    short int free_x1[20]{};

    bool pass{false};

    short int total_moves = total_unknockMoves();
    for (s = 0; s < total_moves; s++)
    {
        for (t = 0; t < count[1]; t++)
        {
            if (source_y[s] == row_o[t] && source_x[s] == column_o[t])
                pass = true;
        }
        if (!pass)
        {
            free_y0[count[2]] = source_y[s];
            free_x0[count[2]] = source_x[s];
            free_y1[count[2]] = target_y[s];
            free_x1[count[2]] = target_x[s];
            count[2]++;
        }
    }

    short int round{};
    short int number{};

    while (round < count[0] && count[0] > 0 && count[2] > 0 && !hunted)
    {
        y[2] = temp_y0[round];
        y[3] = temp_y1[round];
        x[2] = temp_x0[round];
        x[3] = temp_x1[round];

        for (t = 0; t < count[2]; t++)
        {
            choice[0] = rand() % 20;
            number = 0;

            do
            {
                // downwards rightwards... y0 --> 7/5/3
                if (choice[0] == 0 && (y[2] == 7 || y[2] == 5 || y[2] == 3) && y[3] == y[2] - 1 && x[3] == x[2] && x[2] != 3 && board[y[2] - 2][x[2] + 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // downwards leftwards... y0 --> 7/5/3
                else if (choice[0] == 1 && (y[2] == 7 || y[2] == 5 || y[2] == 3) && y[3] == y[2] - 1 && x[3] == x[2] - 1 && x[2] != 0 && board[y[2] - 2][x[2] - 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // downwards rightwards... y0 --> 6/4
                else if (choice[0] == 2 && (y[2] == 6 || y[2] == 4) && y[3] == y[2] - 1 && x[3] == x[2] + 1 && x[2] != 3 && board[y[2] - 2][x[2] + 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                // downwards leftwards... y0 --> 6/4
                else if (choice[0] == 3 && (y[2] == 6 || y[2] == 4) && y[3] == y[2] - 1 && x[3] == x[2] && x[2] != 0 && board[y[2] - 2][x[2] - 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                // downwards rightwards... y0 --> 2
                else if (choice[0] == 4 && y[2] == 2 && y[3] == y[2] - 1 && x[3] == x[2] + 1 && x[2] != 3 && x[2] != 2 && board[y[2] - 2][x[2] + 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                // downwards leftwards... y0 --> 2
                else if (choice[0] == 5 && y[2] == 2 && y[3] == y[2] - 1 && x[3] == x[2] && x[2] != 0 && board[y[2] - 2][x[2] - 1] == ' ' && y[2] - 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards rightwards --> 0/2/4
                else if (choice[0] == 6 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && y[3] == y[2] + 1 && x[3] == x[2] + 1 && x[2] != 3 && board[y[2] + 2][x[2] + 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards leftwards --> 0/2/4
                else if (choice[0] == 7 && (y[2] == 0 || y[2] == 2 || y[2] == 4) && y[3] == y[2] + 1 && x[3] == x[2] && x[2] != 0 && board[y[2] + 2][x[2] - 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards rightwards --> 1/3
                else if (choice[0] == 8 && (y[2] == 1 || y[2] == 3) && y[3] == y[2] + 1 && x[3] == x[2] && x[2] != 3 && board[y[2] + 2][x[2] + 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards leftwards --> 1/3
                else if (choice[0] == 9 && (y[2] == 1 || y[2] == 3) && y[3] == y[2] + 1 && x[3] == x[2] - 1 && x[2] != 0 && board[y[2] + 2][x[2] - 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards rightwards --> 5
                else if (choice[0] == 10 && y[2] == 5 && y[3] == y[2] + 1 && x[3] == x[2] && x[2] != 3 && board[y[2] + 2][x[2] + 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] + 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                //  upwards leftwards --> 5
                else if (choice[0] == 11 && y[2] == 5 && y[3] == y[2] + 1 && x[3] == x[2] - 1 && x[2] != 0 && x[2] != 1 && board[y[2] + 2][x[2] - 1] == ' ' && y[2] + 2 == free_y1[t] && x[2] - 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                // ------------------------------------------------------------------------- //

                // downwards rightwards 7/5/3
                else if (choice[0] == 12 && (y[2] == 7 || y[2] == 5 || y[2] == 3) && y[3] == y[2] - 1 && x[2] == 3 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // upwards rightwards 6
                else if (choice[0] == 13 && choice[0] == 1 && y[2] == 6 && y[3] == y[2] + 1 && x[2] != 3 && x[3] == x[2] + 1 && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // downwards rightwards 1
                else if (choice[0] == 14 && y[2] == 1 && y[3] == y[2] - 1 && x[2] != 3 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // downwards leftwards 6/4/2
                else if (choice[0] == 15 && (y[2] == 6 || y[2] == 4 || y[2] == 2) && y[3] == y[2] - 1 && x[2] == 0 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // downwards leftwards 1
                else if (choice[0] == 16 && y[2] == 1 && y[3] == y[2] - 1 && x[2] != 0 && x[3] == x[2] - 1 && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // upwards rightwards 1/3/5
                else if (choice[0] == 17 && (y[2] == 1 || y[2] == 5 || y[2] == 3) && y[3] == y[2] + 1 && x[2] == 3 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // upwards leftwards 0/2/4
                else if (choice[0] == 18 && (y[2] == 0 || y[2] == 4 || y[2] == 2) && y[3] == y[2] + 1 && x[2] == 0 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }
                // upwards leftwards 6
                else if (choice[0] == 19 && choice[0] == 0 && y[2] == 6 && y[3] == y[2] + 1 && x[2] != 0 && x[3] == x[2] && free_y1[t] == y[3] && free_x1[t] == x[3])
                {
                    if (board[free_y0[t]][free_x0[t]] == 'O')
                    {
                        board[free_y1[t]][free_x1[t]] = 'O';
                    }
                    else if (board[free_y0[t]][free_x0[t]] == 'o')
                    {
                        board[free_y1[t]][free_x1[t]] = 'o';
                    }

                    board[free_y0[t]][free_x0[t]] = '.';
                    hunted = true;
                }

                if (hunted)
                {
                    future_playersKnock(false);
                    if (future_knock)
                    {
                        if (board[free_y1[t]][free_x1[t]] == 'O')
                        {
                            board[free_y0[t]][free_x0[t]] = 'O';
                        }
                        else
                        {
                            board[free_y0[t]][free_x0[t]] = 'o';
                        }

                        board[free_y1[t]][free_x1[t]] = ' ';
                        hunted = false;
                    }
                }

                number++;
                choice[0]++;
                if (choice[0] == 20)
                    choice[0] = 0;

            } while (number < 21 && !hunted);
            if (hunted)
                break;
        }

        round++;
    }

    for (t = 0; t < 4; t++)
    {
        if (board[0][t] == 'o')
        {
            board[0][t] = 'O';
        }
    }

    std::cout << "\n        hunted: " << hunted;
}

void knock_creation()
{
    knock_created = false;

    short int index{};
    short int comp_knocks{};
    short int player_knocks{};
    short int total_moves{};
    short int total_knocks[2]{};

    short int s{};
    short int t{};

    knocks_checking(&total_knocks[0]);
    total_moves = total_unknockMoves();

    if (total_moves > 0)
    {
        while (index < total_moves)
        {
            y[2] = source_y[index];
            x[2] = source_x[index];
            y[3] = target_y[index];
            x[3] = target_x[index];

            future_playersKnock(true);
            comp_knocks = triple_play(&player_knocks);

            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board1[s][t] = board[s][t];
                    board[s][t] = temp_board2[s][t];
                }
            }

            knocks_checking(&total_knocks[1]);

            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    board[s][t] = temp_board1[s][t];
                }
            }

            if (comp_knocks > player_knocks && total_knocks[1] > total_knocks[0])
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        board[s][t] = temp_board2[s][t];
                    }
                }

                knock_created = true;
                break;
            }

            index++;
        }
    }

    std::cout << "\n        knock created: " << knock_created;
}

short int check_winner(bool sum_up)
{
    short int player_moves{};
    short int s{};
    short int t{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if ((s == 7 || s == 5 || s == 3 || s == 1) && board[s][t] == 'X' && (board[s - 1][t] == ' ' || board[s - 1][t] == '.'))
            {
                player_moves++;
            }
            if ((s == 7 || s == 5 || s == 3 || s == 1) && t != 0 && board[s][t] == 'X' && (board[s - 1][t - 1] == ' ' || board[s - 1][t - 1] == '.'))
            {
                player_moves++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s][t] == 'X' && (board[s - 1][t + 1] == ' ' || board[s - 1][t + 1] == '.'))
            {
                player_moves++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s][t] == 'X' && (board[s - 1][t] == ' ' || board[s - 1][t] == '.'))
            {
                player_moves++;
            }
            if ((s == 1 || s == 5 || s == 3) && (board[s][t] == 'X' || board[s][t] == 'x') && (board[s + 1][t] == ' ' || board[s + 1][t] == '.'))
            {
                player_moves++;
            }
            if ((s == 1 || s == 5 || s == 3) && t != 0 && (board[s][t] == 'X' || board[s][t] == 'x') && (board[s + 1][t - 1] == ' ' || board[s + 1][t - 1] == '.'))
            {
                player_moves++;
            }
            if ((s == 0 || s == 4 || s == 2 || s == 6) && t != 3 && (board[s][t] == 'X' || board[s][t] == 'x') && (board[s + 1][t + 1] == ' ' || board[s + 1][t + 1] == '.'))
            {
                player_moves++;
            }
            if ((s == 0 || s == 4 || s == 2) && (board[s][t] == 'X' || board[s][t] == 'x') && (board[s + 1][t] == ' ' || board[s + 1][t] == '.'))
            {
                player_moves++;
            }

            if ((s == 0 || s == 2 || s == 4) && t != 3 && (board[s + 1][t + 1] == 'o' || board[s + 1][t + 1] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                player_moves++;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                player_moves++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                player_moves++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (board[s + 1][t - 1] == 'o' || board[s + 1][t - 1] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                player_moves++;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 3 && (board[s - 1][t + 1] == 'o' || board[s - 1][t + 1] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                player_moves++;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                player_moves++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                player_moves++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (board[s - 1][t - 1] == 'o' || board[s - 1][t - 1] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                player_moves++;
            }
        }
    }

    // -------------------------------------------------------------------------------------------------------------------------- //

    short int comp_moves{};
    short int comp_knocks{};
    short int total_knocks{};

    auto unknock_compMoves = total_compMoves();
    knocks_checking(&total_knocks);
    comp_moves = unknock_compMoves + total_knocks;

    // -------------------------------------------------------------------------------------------------------------------------- //

    short int total_comp_pieces{};
    short int total_player_pieces{};

    draw_count[2] = draw_count[0];
    draw_count[3] = draw_count[1];

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            if (board[s][t] == 'O' || board[s][t] == 'o')
                total_comp_pieces++;

            else if (board[s][t] == 'X' || board[s][t] == 'x')
                total_player_pieces++;
        }
    }

    draw_count[0] = total_comp_pieces;
    draw_count[1] = total_player_pieces;

    if ((draw_count[2] == draw_count[0] && draw_count[3] == draw_count[0]) && total_comp_pieces < 4 && total_player_pieces < 4 && sum_up)
    {
        draw_count[4]++;
    }
    else if (((draw_count[2] != draw_count[0] && draw_count[3] == draw_count[0]) || (draw_count[2] == draw_count[0] && draw_count[3] != draw_count[0]) || (draw_count[2] != draw_count[0] && draw_count[3] != draw_count[0])) && total_comp_pieces < 4 && total_player_pieces < 4 && sum_up)
    {
        draw_count[4] = 0;
    }

    // ------------------------------------------------------------------------------------------------------------------------------- //
    std::cout << "\n        player moves:" << player_moves;
    std::cout << "\n        comp moves:  \n" << comp_moves;

    if (draw_count[4] == 12)
    {
        return 3;
    }
    else if (player_moves == 0 && comp_moves > 0)
    {
        return 2;
    }
    else if (comp_moves == 0 && player_moves > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_winner(short int winner)
{
    if (winner == 1)
    {
        std::cout << "        =========================================\n";
        std::cout << "                     HURRAY! YOU WIN!\n";
        std::cout << "        =========================================\n";
        std::cout << std::endl;
    }
    else if (winner == 2)
    {
        std::cout << "        =========================================\n";
        std::cout << "                       COMP WINS!\n";
        std::cout << "        =========================================\n";
        std::cout << std::endl;
    }
    else if (winner == 3)
    {
        std::cout << "        =========================================\n";
        std::cout << "                      GAME DRAW! :)!\n";
        std::cout << "        =========================================\n";
        std::cout << std::endl;
    }
}

void print_heart()
{
    float x, y, size = 6;
    int print_line = 4;

    // ------------------------------- 1st half ------------------------------ //

    std::cout << "\n                ";

    for (x = 0; x < size; x++)
    {
        for (y = 0; y <= 4 * size; y++)
        {
            float distance1 = sqrt(pow(x - size, 2) + pow(y - size, 2));
            float distance2 = sqrt(pow(x - size, 2) + pow(y - 3 * size, 2));

            if (distance1 < size + 0.5 || distance2 < size + 0.5)
            {
                std::cout << "*";
            }
            else
                std::cout << " ";
        }

        std::cout << "\n                ";
    }

    // -------------------------------- 2nd half ----------------------------- //

    for (x = 1; x < 2 * size; x++)
    {
        for (y = 0; y < x; y++)
            std::cout << " ";

        for (y = 0; y < 4 * size + 1 - 2 * x; y++)
        {
            std::cout << "*";
        }

        std::cout << "\n                ";
    }

    std::cout << "            *" << std::endl;

    // ----------------------------------------------------------------------- //
}