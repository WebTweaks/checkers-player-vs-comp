

/*
    AUTHOR: JOHN KALOKI
    ORIGIN: KENYA
    EMAIL:  me.johnkaloki@gmail.com
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <cmath>

char board[8][4]{};
char temp_board1[8][4]{};
char temp_board2[8][4]{};
char temp_board3[8][4]{};
std::string player_name{};
short int play_mode{};
short int choice[2]{};
short int y[4]{};
short int x[4]{};
bool moved_by_knock{false};
short int temp_y[30]{};
short int temp_x[30]{};
short int y1_store[30]{};
short int x1_store[30]{};
short int s{};
short int t{};
short int draw_count[5]{};

void reset_board();
void print_board();

void player();
bool choice_processing(int);
bool select_piece_player();
bool move_piece_player();
bool more_knocks();

void computer();
bool knocks_checking(int *);
short int total_compMoves();
short int total_unknock_moves();
void select_piece_comp();
void move_piece_comp(char knock);
void best_move();
short int triple_play();
bool future_playersKnock();
int maxKnocks_comp();
bool future_more_knocks();
int maxKnocks_player();
bool playersKnock_remove();
bool playersKnock_block();
bool knock_antidote();
bool x_chase();

short int check_winner(bool count);
void print_winner(int winner);
void print_heart();

int main()
{
    srand(time(0));

    bool end{false};
    char play_again{};
    short int winner{};
    const unsigned short int max_length{20};

    std::cout << "\n        Enter your name dear: ";

    char temp_name1[max_length]{};
    char temp_name2[max_length]{};

    std::cin.getline(temp_name1, max_length);
    for (s = 0; s < std::size(temp_name1); ++s)
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
    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = ' ';
            temp_board1[s][t] = ' ';
            temp_board2[s][t] = ' ';
            temp_board3[s][t] = ' ';
        }
    }

    // player
    for (s = 0; s < 3; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = ' ';
        }
    }

    // comp
    for (s = 5; s <= 7; s++)
    {
        for (t = 0; t < 4; t++)
        {
            board[s][t] = ' ';
        }
    }

    board[1][1] = 'X';
    board[0][0] = 'O';
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
        std::cout << "        Six More Non-Knock Moves To Draw!!!" << std::endl;
        break;
    case 9:
        std::cout << "        Three More Non-Knock Moves To Draw!!!" << std::endl;
        break;
    case 11:
        std::cout << "        One More Non-Knock Move To Draw!!!" << std::endl;
        break;
    default:
        break;
    }

    bool moved{false};
    bool knock_available{false};
    bool selected{false};
    bool invalid_input{false};

    do
    {
        do
        {
            do
            {
                std::cout << "           Enter piece row# column# e.g 32: ";

                if (!(std::cin >> choice[0]))
                {
                    print_board();
                    std::cout << "           Invalid input! Try again!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else
                {
                    invalid_input = choice_processing(0);
                    if (invalid_input)
                    {
                        print_board();
                        std::cout << "           Invalid input! Try again!" << std::endl;
                    }
                }

            } while (invalid_input);

            selected = select_piece_player();

            if (!selected)
            {
                print_board();
                std::cout << "           Invalid piece entry! Try again!" << std::endl;
            }

        } while (!selected);

        print_board();
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "           SELECTED " << player_name << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;

        while (!moved && selected)
        {
            do
            {
                std::cout << "             --> Enter 00 to reselect <--" << '\n';
                std::cout << "           Enter target row# column# e.g 43: ";

                if (!(std::cin >> choice[1]))
                {
                    print_board();
                    std::cout << "           Invalid input! Try again!" << std::endl;
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
                        invalid_input = choice_processing(1);
                        if (invalid_input)
                        {
                            print_board();
                            std::cout << "           Invalid input! Try again!" << std::endl;
                        }
                    }
                }

            } while (invalid_input && selected);

            if (selected && !invalid_input)
            {
                moved = move_piece_player();
                if (!moved)
                {
                    print_board();
                    std::cout << "           Invalid input! Try again!" << std::endl;
                }
            }
            else
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
        }

    } while (!selected);

    while ((knock_available = more_knocks()) && moved_by_knock)
    {
        if (board[y[1]][x[1]] == 'X')
        {
            board[y[1]][x[1]] = 'S';
        }
        else if (board[y[1]][x[1]] == 'x')
        {
            board[y[1]][x[1]] = 's';
        }

        y[0] = y[1];
        x[0] = x[1];

        print_board();
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "               CONSECUTIVE KNOCK AVAILABLE " << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;

        do
        {
            do
            {
                std::cout << "           Enter target row# column# e.g 54: ";

                if (!(std::cin >> choice[1]))
                {
                    std::cout << "           Invalid input! Try again!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    print_board();
                }

                else
                {
                    invalid_input = choice_processing(1);
                    if (invalid_input)
                    {
                        std::cout << "           Invalid input! Try again!" << std::endl;
                        print_board();
                    }
                }

            } while (invalid_input);

            moved = move_piece_player();
            if (!moved)
            {
                std::cout << "           Invalid input! Try again!" << std::endl;
                print_board();
            }

        } while (!moved);
    }

    print_board();
    std::cout << "        MOVED " << player_name << "." << std::endl;
    std::cout << std::endl;
}

bool choice_processing(int index)
{
    bool invalid_choice{true};

    if (choice[index] == 11 || choice[index] == 13 || choice[index] == 15 || choice[index] == 17 || choice[index] == 22 || choice[index] == 24 || choice[index] == 26 || choice[index] == 28 || choice[index] == 31 || choice[index] == 33 || choice[index] == 35 || choice[index] == 37 || choice[index] == 42 || choice[index] == 44 || choice[index] == 46 || choice[index] == 48)
    {
        invalid_choice = true;
    }
    else if (choice[index] == 51 || choice[index] == 53 || choice[index] == 55 || choice[index] == 57 || choice[index] == 62 || choice[index] == 64 || choice[index] == 66 || choice[index] == 68 || choice[index] == 71 || choice[index] == 73 || choice[index] == 75 || choice[index] == 77 || choice[index] == 82 || choice[index] == 84 || choice[index] == 86 || choice[index] == 88)
    {
        invalid_choice = true;
    }
    else if (choice[index] >= 12 && choice[index] <= 87)
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
            invalid_choice = false;
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

            invalid_choice = false;
        }
    }

    return invalid_choice;
}

bool select_piece_player()
{
    bool selected{false};

    if (board[y[0]][x[0]] == 'x' || board[y[0]][x[0]] == 'X')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == ' ' || board[y[0] + 1][x[0] + 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && (board[y[0] + 1][x[0]] == ' ' || board[y[0] + 1][x[0]] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == ' ' || board[y[0] + 1][x[0] - 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == 'o' || board[y[0] + 1][x[0] + 1] == 'O') &&
                 (board[y[0] + 2][x[0] + 1] == ' ' || board[y[0] + 2][x[0] + 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[0] + 2][x[0] - 1] == ' ' || board[y[0] + 2][x[0] - 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] + 1][x[0]] == 'o' || board[y[0] + 1][x[0]] == 'O') &&
                 (board[y[0] + 2][x[0] + 1] == ' ' || board[y[0] + 2][x[0] + 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] + 1][x[0] - 1] == 'o' || board[y[0] + 1][x[0] - 1] == 'O') &&
                 (board[y[0] + 2][x[0] - 1] == ' ' || board[y[0] + 2][x[0] - 1] == '.'))
        {
            if (board[y[0]][x[0]] == 'x')
            {
                board[y[0]][x[0]] = 's';
            }
            else
            {
                board[y[0]][x[0]] = 'S';
            }

            selected = true;
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

    return selected;
}

bool move_piece_player()
{
    bool moved{false};

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
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
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

        moved_by_knock = false;
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

        moved_by_knock = false;
    }

    // up --> knock
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

    // down --> knock
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

    for (t = 0; t < 4; t++)
    {
        if (board[7][t] == 'x')
        {
            board[7][t] = 'X';
        }
    }

    return moved;
}

bool more_knocks()
{
    bool knock_present{false};

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

    return knock_present;
}

void computer()
{
    std::cout << "        =========================================" << std::endl;
    std::cout << "                      COMP'S TURN" << std::endl;
    std::cout << "        ========================================= ";

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

    bool selected{false};
    bool moved{false};
    bool future_knock{false};
    bool removed_knock{false};
    bool blocked_knock{false};
    bool chased{false};
    char temp_board[8][4]{};

    int total_knocks{};
    short int rand_num{};
    short int max_knocks{};
    short int index{};
    short total_comp_knocks{};
    short total_player_knocks{};

    bool knock_present = knocks_checking(&total_knocks);

    if (play_mode == 1)
    {
        rand_num = rand() % 3;
        auto total_moves = total_compMoves();

        if (total_moves == 0 && knock_present)
        {
            rand_num = 1;
        }

        if (rand_num == 1 && knock_present)
        {
            knocks_checking(&total_knocks);
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
            y[1] = y1_store[rand_num];
            x[1] = x1_store[rand_num];

            move_piece_comp('Y');

            while (knock_present = knocks_checking(&total_knocks))
            {
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                move_piece_comp('Y');
            }

            moved = true;
        }

        if (!moved)
        {
            select_piece_comp();
            move_piece_comp('N');
        }
    }
    else if (play_mode == 2)
    {
        if (knock_present)
        {
            rand_num = rand() % 4;
            if (rand_num == 0)
            {
                max_knocks = 0;
                index = 0;

                do
                {
                    y[0] = temp_y[index];
                    x[0] = temp_x[index];

                    total_comp_knocks = maxKnocks_comp();
                    total_player_knocks = maxKnocks_player();

                    if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
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
            else if (rand_num == 1 || rand_num == 2 || rand_num == 3)
            {
                knocks_checking(&total_knocks);
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                move_piece_comp('Y');

                while (knock_present = knocks_checking(&total_knocks))
                {
                    rand_num = rand() % total_knocks;

                    y[0] = temp_y[rand_num];
                    x[0] = temp_x[rand_num];
                    y[1] = y1_store[rand_num];
                    x[1] = x1_store[rand_num];

                    move_piece_comp('Y');
                }

                moved = true;
            }
        }

        if (!moved)
        {
            removed_knock = playersKnock_remove();
            if (!removed_knock)
            {
                blocked_knock = playersKnock_block();
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

            if (!blocked_knock && !removed_knock)
                chased = x_chase();

            while (!moved && !chased)
            {
                for (short int re_do = 0; re_do < 100000; re_do++)
                {
                    select_piece_comp();
                    future_knock = future_playersKnock();

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
                    else if (!moved && re_do == 100)
                    {
                        select_piece_comp();
                        move_piece_comp('N');

                        moved = true;
                        break;
                    }
                }
            }
        }
    }
    else if (play_mode == 3)
    {
        if (knock_present)
        {
            max_knocks = 0;
            index = 0;

            while (index < total_knocks)
            {
                y[0] = temp_y[index];
                x[0] = temp_x[index];

                total_comp_knocks = maxKnocks_comp();
                total_player_knocks = maxKnocks_player();

                if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
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
            }

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

bool knocks_checking(int *total_knocks)
{
    bool knock_present{false};
    *total_knocks = 0;

    for (s = 0; s <= 7; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // ^^^

            if ((s == 0 || s == 2 || s == 4) && t != 3 && (board[s + 1][t + 1] == 'x' || board[s + 1][t + 1] == 'X') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && board[s][t] == 'O')
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s + 2;
                x1_store[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (board[s + 1][t] == 'x' || board[s + 1][t] == 'X') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && board[s][t] == 'O')
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s + 2;
                x1_store[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (board[s + 1][t] == 'x' || board[s + 1][t] == 'X') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && board[s][t] == 'O')
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s + 2;
                x1_store[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (board[s + 1][t - 1] == 'x' || board[s + 1][t - 1] == 'X') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && board[s][t] == 'O')
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s + 2;
                x1_store[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            // vv

            if ((s == 6 || s == 2 || s == 4) && t != 3 && (board[s - 1][t + 1] == 'x' || board[s - 1][t + 1] == 'X') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s - 2;
                x1_store[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (board[s - 1][t] == 'x' || board[s - 1][t] == 'X') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s - 2;
                x1_store[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (board[s - 1][t] == 'x' || board[s - 1][t] == 'X') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s - 2;
                x1_store[*total_knocks] = t + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (board[s - 1][t - 1] == 'x' || board[s - 1][t - 1] == 'X') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && (board[s][t] == 'o' || board[s][t] == 'O'))
            {
                temp_y[*total_knocks] = s;
                temp_x[*total_knocks] = t;
                y1_store[*total_knocks] = s - 2;
                x1_store[*total_knocks] = t - 1;
                *total_knocks = *total_knocks + 1;
            }
        }
    }

    if (*total_knocks > 0)
        knock_present = true;

    return knock_present;
}

short int total_compMoves()
{
    int count{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // downwards rightwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && (board[s][t] == 'O' || board[s][t] == 'o') && board[s - 1][t] == ' ')
            {
                count++;
            }

            // downwards leftwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && t != 0 && (board[s][t] == 'O' || board[s][t] == 'o') && board[s - 1][t - 1] == ' ')
            {
                count++;
            }

            // downwards rightwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 3 && (board[s][t] == 'O' || board[s][t] == 'o') && board[s - 1][t + 1] == ' ')
            {
                count++;
            }

            // downwards leftwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 0 && (board[s][t] == 'O' || board[s][t] == 'o') && board[s - 1][t] == ' ')
            {
                count++;
            }

            // upwards rightwards - odd
            if ((s == 1 || s == 5 || s == 3) && board[s][t] == 'O' && board[s + 1][t] == ' ')
            {
                count++;
            }

            // upwards leftwards - odd
            if ((s == 1 || s == 5 || s == 3) && t != 0 && board[s][t] == 'O' && board[s + 1][t - 1] == ' ')
            {
                count++;
            }

            // upwards rightwards - even
            if ((s == 0 || s == 4 || s == 2 || s == 6) && t != 3 && board[s][t] == 'O' && board[s + 1][t + 1] == ' ')
            {
                count++;
            }

            // upwards leftwards - even
            if ((s == 0 || s == 4 || s == 2) && board[s][t] == 'O' && board[s + 1][t] == ' ')
            {
                count++;
            }
        }
    }

    return count;
}

short int total_unknock_moves()
{
    short int count{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // upwards rightwards
            if ((s == 0 || s == 2 || s == 4) && t != 3 && board[s + 1][t + 1] == ' ' && board[s + 2][t + 1] != 'X' &&
                ((board[s][t + 1] != 'x' && board[s][t + 1] != 'X') || ((board[s][t + 1] == 'x' || board[s][t + 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t + 1] != ' ')) && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t + 1;
                count++;
            }
            if (s == 6 && t != 3 && board[s + 1][t + 1] == ' ' && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t + 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && board[s + 1][t] == ' ' && board[s + 2][t + 1] != 'X' &&
                ((board[s][t + 1] != 'x' && board[s][t + 1] != 'X') || ((board[s][t + 1] == 'x' || board[s][t + 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t + 1] != ' ')) && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t == 3 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t;
                count++;
            }

            // upwards leftwards
            if ((s == 0 || s == 2 || s == 4) && t != 0 && board[s + 1][t] == ' ' && board[s + 2][t - 1] != 'X' &&
                ((board[s][t - 1] != 'x' && board[s][t - 1] != 'X') || ((board[s][t - 1] == 'x' || board[s][t - 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t - 1] != ' ')) && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t;
                count++;
            }
            if (s == 6 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t == 0 && board[s + 1][t] == ' ' && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && board[s + 2][t - 1] != 'X' &&
                ((board[s][t - 1] != 'x' && board[s][t - 1] != 'X') || ((board[s][t - 1] == 'x' || board[s][t - 1] == 'X') && board[s + 2][t] != ' ')) &&
                (board[s + 2][t] != 'X' || (board[s + 2][t] == 'X' && board[s][t - 1] != ' ')) && board[s][t] == 'O')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 1;
                x1_store[count] = t - 1;
                count++;
            }

            // downwards rightwards
            if ((s == 7 || s == 5 || s == 3) && t != 3 && board[s - 1][t] == ' ' && board[s - 2][t + 1] != 'X' && board[s - 2][t + 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'X' || (board[s][t + 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 7 || s == 5 || s == 3) && t == 3 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t;
                count++;
            }
            if (s == 1 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s - 1][t + 1] == ' ' && board[s - 2][t + 1] != 'X' && board[s - 2][t + 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'X' || (board[s][t + 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t + 1;
                count++;
            }

            // downwards leftwards
            if ((s == 7 || s == 5 || s == 3) && t != 0 && board[s - 1][t - 1] == ' ' && board[s - 2][t - 1] != 'X' && board[s - 2][t - 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'X' || (board[s][t - 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t - 1;
                count++;
            }
            if (s == 1 && t != 0 && board[s - 1][t - 1] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t - 1;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s - 1][t] == ' ' && board[s - 2][t - 1] != 'X' && board[s - 2][t - 1] != 'x' &&
                ((board[s - 2][t] != 'x' && board[s - 2][t] != 'X') || ((board[s - 2][t] == 'x' || board[s - 2][t] == 'X') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'X' || (board[s][t - 1] == 'X' && board[s - 2][t] != ' ')) && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t;
                count++;
            }
            if ((s == 6 || s == 4 || s == 2) && t == 0 && board[s - 1][t] == ' ' && (board[s][t] == 'O' || board[s][t] == 'o'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 1;
                x1_store[count] = t;
                count++;
            }
        }
    }

    return count;
}

void select_piece_comp()
{
    auto temp_play_mode{play_mode};

    if (play_mode == 2)
    {
        auto total_moves{total_unknock_moves()};
        // std::cout << "total_moves: " << total_moves;

        if (total_moves == 0)
            temp_play_mode = 1;

        else if (total_moves > 0)
        {
            auto rand_num{rand() % total_moves};
            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
        }
        // std::cout << " y[0]:" << y[0] << " x[0]:" << x[0] << '\n';
    }

    int count{};
    bool selected{false};

    while (!selected && temp_play_mode == 1)
    {
        y[0] = rand() % 8;

        for (s = 0; s < 500; s++)
        {
            x[0] = rand() % 4;
            choice[0] = rand() % 8;
            count = 0;

            do
            {
                // moving up without knock
                if (choice[0] == 0 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && board[y[0] + 1][x[0]] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 1 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && board[y[0] + 1][x[0] + 1] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 2 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && board[y[0] + 1][x[0]] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 3 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && board[y[0] + 1][x[0] - 1] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }

                // moving down without knock
                else if (choice[0] == 4 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && board[y[0] - 1][x[0]] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 5 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && board[y[0] - 1][x[0] + 1] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 6 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && board[y[0] - 1][x[0]] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 7 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && board[y[0] - 1][x[0] - 1] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
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

    // Available targets
    // downwards rightwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && board[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // downwards leftwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && board[y[0] - 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // downwards rightwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && board[y[0] - 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // downwards leftwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o') && board[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards rightwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && board[y[0]][x[0]] == 'O' && board[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards leftwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && board[y[0]][x[0]] == 'O' && board[y[0] + 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // upwards rightwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && board[y[0]][x[0]] == 'O' && board[y[0] + 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // upwards leftwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && board[y[0]][x[0]] == 'O' && board[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    short int rand_num = rand() % count;
    y[1] = temp_y[rand_num];
    x[1] = temp_x[rand_num];
}

void move_piece_comp(char knock)
{
    if (y[0] + 1 == y[1] && knock == 'N' && board[y[0]][x[0]] == 'O')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            board[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && board[y[1]][x[1]] == ' ')
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && board[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 board[y[1]][x[1]] == ' ')
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
        }
    }

    else if (y[0] - 1 == y[1] && knock == 'N' && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) && board[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && board[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) && board[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] && board[y[1]][x[1]] == ' ')
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
            board[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] - 1] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (board[y[0] + 1][x[0]] == 'x' || board[y[0] + 1][x[0]] == 'X') &&
                 board[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (board[y[0] + 1][x[0]] == 'x' || board[y[0] + 1][x[0]] == 'X') &&
                 board[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (board[y[0] + 1][x[0] + 1] == 'x' || board[y[0] + 1][x[0] + 1] == 'X') &&
                 board[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            board[y[1]][x[1]] = 'O';
            board[y[0]][x[0]] = '.';
            board[y[0] + 1][x[0] + 1] = '.';
        }
    }
    else if (y[0] - 2 == y[1] && knock == 'Y' && (board[y[0]][x[0]] == 'O' || board[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (board[y[0] - 1][x[0] - 1] == 'x' || board[y[0] - 1][x[0] - 1] == 'X') &&
            board[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
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
                 board[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
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
                 board[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
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
                 board[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
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

    for (s = 0; s < 4; s++)
    {
        if (board[0][s] == 'o')
        {
            board[0][s] = 'O';
        }
    }
}

void best_move()
{
    char final_board[8][4]{};
    bool target_chosen{false};
    short int total_comp_knocks[2]{};

    bool knock_chosen = knock_antidote();
    std::cout << "\n        knock_chosen: " << std::boolalpha << knock_chosen;
    if (knock_chosen)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                final_board[s][t] = temp_board1[s][t];
            }
        }

        y[0] = 0;
        y[1] = 0;
        x[0] = 0;
        x[1] = 0;

        total_comp_knocks[0] = triple_play();
        target_chosen = true;
    }

    auto total_moves = total_unknock_moves();
    if (total_moves == 0)
    {
        for (y[0] = 0; y[0] < 8; y[0]++)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && board[y[0] + 1][x[0]] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && board[y[0] + 1][x[0] + 1] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0] + 1;
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && board[y[0] + 1][x[0]] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && board[y[0] + 1][x[0] - 1] == ' ' && board[y[0]][x[0]] == 'O')
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] + 1;
                    x1_store[total_moves] = x[0] - 1;
                    total_moves++;
                }
                if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && board[y[0] - 1][x[0]] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && board[y[0] - 1][x[0] + 1] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0] + 1;
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && board[y[0] - 1][x[0]] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0];
                    total_moves++;
                }
                if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && board[y[0] - 1][x[0] - 1] == ' ' && (board[y[0]][x[0]] == 'o' || board[y[0]][x[0]] == 'O'))
                {
                    temp_y[total_moves] = y[0];
                    temp_x[total_moves] = x[0];
                    y1_store[total_moves] = y[0] - 1;
                    x1_store[total_moves] = x[0] - 1;
                    total_moves++;
                }
            }
        }
    }
    std::cout << "\n        total_moves: " << total_moves;

    short int count{};
    bool chased{false};

    if (target_chosen)
    {
        while (count < total_moves)
        {
            y[0] = temp_y[count];
            x[0] = temp_x[count];
            y[1] = y1_store[count];
            x[1] = x1_store[count];

            total_comp_knocks[1] = triple_play();
            if (total_comp_knocks[1] > total_comp_knocks[0])
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
        chased = x_chase();

        if (!chased)
        {
            auto index{rand() % total_moves};
            while (count <= total_moves)
            {
                y[0] = temp_y[index];
                x[0] = temp_x[index];
                y[1] = y1_store[index];
                x[1] = x1_store[index];

                total_comp_knocks[0] = triple_play();
                if (total_comp_knocks[0] > total_comp_knocks[1])
                {
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            final_board[s][t] = temp_board2[s][t];
                            target_chosen = true;
                        }
                    }
                }

                count++;
                index++;
                if (index == total_moves)
                    index = 0;

                y[0] = temp_y[index];
                x[0] = temp_x[index];
                y[1] = y1_store[index];
                x[1] = x1_store[index];

                total_comp_knocks[1] = triple_play();
                if (total_comp_knocks[1] > total_comp_knocks[0])
                {
                    for (s = 0; s < 8; s++)
                    {
                        for (t = 0; t < 4; t++)
                        {
                            final_board[s][t] = temp_board2[s][t];
                            target_chosen = true;
                        }
                    }
                }

                count++;
            }
        }
        else
        {
            for (s = 0; s < 4; s++)
            {
                if (board[0][s] == 'o')
                {
                    board[0][s] = 'O';
                }
            }
        }

        if (!target_chosen && !chased)
        {
            short int rand_num{};
            bool future_knock{false};

            for (short int re_do = 0; re_do < 10000; re_do++)
            {
                rand_num = rand() % total_moves;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                future_knock = future_playersKnock();

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

                if (re_do == 30)
                {
                    rand_num = rand() % total_moves;

                    y[0] = temp_y[rand_num];
                    x[0] = temp_x[rand_num];
                    y[1] = y1_store[rand_num];
                    x[1] = x1_store[rand_num];

                    move_piece_comp('N');

                    break;
                }
            }
        }
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

    std::cout << "\n        target_chosen: " << std::boolalpha << target_chosen;
}

short int triple_play()
{
    bool knock_available{false};
    future_playersKnock();

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board2[s][t] = temp_board1[s][t];
        }
    }

    maxKnocks_player();

    //* /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    short int total_comp_knocks{};
    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (temp_y[28] = 0; temp_y[28] < 8; temp_y[28]++)
        {
            for (temp_x[28] = 0; temp_x[28] < 4; temp_x[28]++)
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = temp_board3[s][t];
                    }
                }

                if (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o')
                {
                    const unsigned short int initial_Y = temp_y[28];
                    const unsigned short int initial_X = temp_x[28];

                    int total_knocks{};

                    for (temp_y[29] = 0; temp_y[29] < 8; temp_y[29]++)
                    {
                        const unsigned short int temp_y19 = temp_y[29];

                        for (temp_x[29] = 0; temp_x[29] < 4; temp_x[29]++)
                        {
                            const unsigned short int temp_x19 = temp_x[29];

                            bool knock_present{false};
                            bool proceed{false};

                            do
                            {
                                if (temp_y[28] + 2 == temp_y[29] && temp_board1[temp_y[28]][temp_x[28]] == 'O')
                                {
                                    if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') &&
                                        (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                                    }
                                    else if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                                    }
                                }
                                else if (temp_y[28] - 2 == temp_y[29])
                                {
                                    if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') &&
                                        (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'o';
                                        }
                                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'o';
                                        }
                                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'o';
                                        }
                                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'o';
                                        }
                                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    total_knocks++;

                                    temp_y[28] = temp_y[29];
                                    temp_x[28] = temp_x[29];

                                    total_comp_knocks = (total_knocks > total_comp_knocks) ? total_knocks : total_comp_knocks;

                                    for (t = 0; t < 4; t++)
                                    {
                                        if (temp_board1[0][t] == 'o')
                                        {
                                            temp_board1[0][t] = 'O';
                                        }
                                    }

                                    knock_present = future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            temp_y[28] = initial_Y;
                            temp_x[28] = initial_X;

                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    temp_board1[s][t] = temp_board3[s][t];
                                }
                            }

                            temp_x[29] = temp_x19;
                        }

                        temp_y[29] = temp_y19;
                    }
                }
            }
        }
    }

    //* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return total_comp_knocks;
}
bool future_playersKnock()
{
    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            temp_board1[s][t] = board[s][t];
        }
    }

    temp_y[28] = y[0];
    temp_x[28] = x[0];
    temp_y[29] = y[1];
    temp_x[29] = x[1];

    if (temp_y[28] - 1 == temp_y[29])
    {
        if ((temp_y[28] == 7 || temp_y[28] == 5 || temp_y[28] == 3 || temp_y[28] == 1) && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o') && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] == temp_x[29])
        {
            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'O';
            }
            else
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'o';
            }

            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 7 || temp_y[28] == 5 || temp_y[28] == 3 || temp_y[28] == 1) && temp_x[28] != 0 && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o') && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] - 1 == temp_x[29])
        {
            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'O';
            }
            else
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'o';
            }

            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 6 || temp_y[28] == 4 || temp_y[28] == 2) && temp_x[28] != 3 && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o') && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] + 1 == temp_x[29])
        {
            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'O';
            }
            else
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'o';
            }

            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 6 || temp_y[28] == 4 || temp_y[28] == 2) && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o') && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] == temp_x[29])
        {
            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'O';
            }
            else
            {
                temp_board1[temp_y[29]][temp_x[29]] = 'o';
            }

            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
    }
    else if (temp_y[28] + 1 == temp_y[29])
    {
        if ((temp_y[28] == 1 || temp_y[28] == 5 || temp_y[28] == 3) && temp_board1[temp_y[28]][temp_x[28]] == 'O' && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] == temp_x[29])
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 1 || temp_y[28] == 5 || temp_y[28] == 3) && temp_x[28] != 0 && temp_board1[temp_y[28]][temp_x[28]] == 'O' && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] - 1 == temp_x[29])
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 0 || temp_y[28] == 4 || temp_y[28] == 2 || temp_y[28] == 6) && temp_x[28] != 3 && temp_board1[temp_y[28]][temp_x[28]] == 'O' && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] + 1 == temp_x[29])
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
        else if ((temp_y[28] == 0 || temp_y[28] == 4 || temp_y[28] == 2) && temp_board1[temp_y[28]][temp_x[28]] == 'O' && temp_board1[temp_y[29]][temp_x[29]] == ' ' && temp_x[28] == temp_x[29])
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28]][temp_x[28]] = '.';
        }
    }

    for (t = 0; t < 4; t++)
    {
        if (temp_board1[0][t] == 'o')
        {
            temp_board1[0][t] = 'O';
        }
    }

    bool future_knock{false};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // ^^
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

            // vv
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

    return future_knock;
}

int maxKnocks_comp()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {

        int total_knocks{};

        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                temp_board1[s][t] = board[s][t];
            }
        }

        temp_y[28] = y[0];
        temp_x[28] = x[0];

        const unsigned short int initial_Y = y[0];
        const unsigned short int initial_X = x[0];

        for (temp_y[29] = 0; temp_y[29] < 8; temp_y[29]++)
        {
            const unsigned short int temp_y19 = temp_y[29];

            for (temp_x[29] = 0; temp_x[29] < 4; temp_x[29]++)
            {
                const unsigned short int temp_x19 = temp_x[29];

                bool knock_present{false};
                bool proceed{false};

                do
                {
                    if (temp_y[28] + 2 == temp_y[29] && temp_board1[temp_y[28]][temp_x[28]] == 'O')
                    {
                        if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') &&
                            (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                        {
                            proceed = true;
                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                            temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        }
                        else if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                        {
                            proceed = true;
                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                            temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        }
                        else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                        {
                            proceed = true;
                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                            temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        }
                        else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                        {
                            proceed = true;
                            temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                            temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        }
                    }
                    else if (temp_y[28] - 2 == temp_y[29])
                    {
                        if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') &&
                            (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                        {
                            proceed = true;
                            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            }
                            else
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'o';
                            }

                            temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                        }
                        else if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                        {
                            proceed = true;
                            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            }
                            else
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'o';
                            }

                            temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                        }
                        else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                        {
                            proceed = true;
                            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            }
                            else
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'o';
                            }

                            temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                        }
                        else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') &&
                                 (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                        {
                            proceed = true;
                            if (temp_board1[temp_y[28]][temp_x[28]] == 'O')
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'O';
                            }
                            else
                            {
                                temp_board1[temp_y[29]][temp_x[29]] = 'o';
                            }

                            temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                            temp_board1[temp_y[28]][temp_x[28]] = '.';
                        }
                    }

                    if (proceed)
                    {
                        total_knocks++;

                        temp_y[28] = temp_y[29];
                        temp_x[28] = temp_x[29];

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

                        for (s = 0; s < 4; s++)
                        {
                            if (temp_board1[0][s] == 'o')
                            {
                                temp_board1[0][s] = 'O';
                                temp_board2[0][s] = 'O';
                            }
                        }

                        knock_present = future_more_knocks();
                    }

                } while (knock_present);

                total_knocks = 0;

                temp_y[28] = initial_Y;
                temp_x[28] = initial_X;

                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = board[s][t];
                    }
                }

                temp_x[29] = temp_x19;
            }

            temp_y[29] = temp_y19;
        }
    }

    return max_knocks;
}

bool future_more_knocks()
{
    bool knock_present{false};

    choice[0] = rand() % 8;

    if (choice[1] == choice[0])
    {
        choice[0]++;
        if (choice[0] == 8)
            choice[0] = 0;
    }

    choice[1] = choice[0];

    if (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // downwards

            if (choice[0] == 0 && (temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] - 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] + 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] - 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] + 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'O' || temp_board1[temp_y[28]][temp_x[28]] == 'o'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }

            // upwards

            if (choice[0] == 4 && (temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] - 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] + 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] - 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] + 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'O')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }

    else if (temp_board1[temp_y[28]][temp_x[28]] == 'X' || temp_board1[temp_y[28]][temp_x[28]] == 'x')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // upwards

            if (choice[0] == 0 && (temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] - 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'x' || temp_board1[temp_y[28]][temp_x[28]] == 'X'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'O') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] + 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'x' || temp_board1[temp_y[28]][temp_x[28]] == 'X'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'O') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] - 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'x' || temp_board1[temp_y[28]][temp_x[28]] == 'X'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O') &&
                (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] + 2][temp_x[28] + 1] == '.') && (temp_board1[temp_y[28]][temp_x[28]] == 'x' || temp_board1[temp_y[28]][temp_x[28]] == 'X'))
            {
                knock_present = true;
                temp_y[29] = temp_y[28] + 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }

            // downwards

            if (choice[0] == 4 && (temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] - 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'X')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'O') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] + 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'X')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'O') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] - 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'X')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O') &&
                (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' || temp_board1[temp_y[28] - 2][temp_x[28] + 1] == '.') && temp_board1[temp_y[28]][temp_x[28]] == 'X')
            {
                knock_present = true;
                temp_y[29] = temp_y[28] - 2;
                temp_x[29] = temp_x[28] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }

    return knock_present;
}

int maxKnocks_player()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (temp_y[28] = 0; temp_y[28] < 8; temp_y[28]++)
        {
            for (temp_x[28] = 0; temp_x[28] < 4; temp_x[28]++)
            {
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        temp_board1[s][t] = temp_board2[s][t];
                    }
                }

                if (temp_board1[temp_y[28]][temp_x[28]] == 'x' || temp_board1[temp_y[28]][temp_x[28]] == 'X')
                {
                    const unsigned short int initial_Y = temp_y[28];
                    const unsigned short int initial_X = temp_x[28];

                    int total_knocks{};

                    for (temp_y[29] = 0; temp_y[29] < 8; temp_y[29]++)
                    {
                        const unsigned short int temp_y19 = temp_y[29];

                        for (temp_x[29] = 0; temp_x[29] < 4; temp_x[29]++)
                        {
                            const unsigned short int temp_x19 = temp_x[29];

                            bool knock_present{false};
                            bool proceed{false};

                            do
                            {
                                if (temp_y[28] + 2 == temp_y[29])
                                {
                                    if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O') &&
                                        (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;

                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'X')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'x';
                                        }

                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                                    }
                                    else if ((temp_y[28] == 1 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;

                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'X')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'x';
                                        }

                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;

                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'X')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'x';
                                        }

                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;

                                        if (temp_board1[temp_y[28]][temp_x[28]] == 'X')
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        }
                                        else
                                        {
                                            temp_board1[temp_y[29]][temp_x[29]] = 'x';
                                        }

                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                                    }
                                }
                                else if (temp_y[28] - 2 == temp_y[29] && temp_board1[temp_y[28]][temp_x[28]] == 'X')
                                {
                                    if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O') &&
                                        (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 7 || temp_y[28] == 3 || temp_y[28] == 5) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 0 && (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] - 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                    else if ((temp_y[28] == 6 || temp_y[28] == 2 || temp_y[28] == 4) && temp_x[28] != 3 && (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O') &&
                                             (temp_board1[temp_y[29]][temp_x[29]] == ' ' || temp_board1[temp_y[29]][temp_x[29]] == '.') && temp_x[28] + 1 == temp_x[29])
                                    {
                                        proceed = true;
                                        temp_board1[temp_y[29]][temp_x[29]] = 'X';
                                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                                        temp_board1[temp_y[28]][temp_x[28]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    total_knocks++;

                                    temp_y[28] = temp_y[29];
                                    temp_x[28] = temp_x[29];

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

                                    // king
                                    for (t = 0; t < 4; t++)
                                    {
                                        if (temp_board1[7][t] == 'x')
                                        {
                                            temp_board1[7][t] = 'X';
                                            temp_board3[7][t] = 'X';
                                        }
                                    }

                                    knock_present = future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            temp_y[28] = initial_Y;
                            temp_x[28] = initial_X;

                            for (s = 0; s < 8; s++)
                            {
                                for (t = 0; t < 4; t++)
                                {
                                    temp_board1[s][t] = temp_board2[s][t];
                                }
                            }

                            temp_x[29] = temp_x19;
                        }

                        temp_y[29] = temp_y19;
                    }
                }
            }
        }
    }

    return max_knocks;
}

bool playersKnock_remove()
{
    bool removed_knock{false};
    short int count{};

    if (play_mode != 3)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                temp_board1[s][t] = board[s][t];
            }
        }

        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                if ((s == 0 || s == 2 || s == 4) && t != 3 && (temp_board1[s + 1][t + 1] == 'o' || temp_board1[s + 1][t + 1] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 0 || s == 2 || s == 4) && t != 0 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t - 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 3 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 0 && (temp_board1[s + 1][t - 1] == 'o' || temp_board1[s + 1][t - 1] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t - 1;
                    count++;
                }

                if ((s == 6 || s == 2 || s == 4) && t != 3 && (temp_board1[s - 1][t + 1] == 'o' || temp_board1[s - 1][t + 1] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 6 || s == 2 || s == 4) && t != 0 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t - 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 3 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 0 && (temp_board1[s - 1][t - 1] == 'o' || temp_board1[s - 1][t - 1] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {

            auto rand_num{rand() % count};

            temp_y[28] = temp_y[rand_num];
            temp_x[28] = temp_x[rand_num];
            temp_y[29] = y1_store[rand_num];
            temp_x[29] = x1_store[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7
        if (temp_y[28] == 7 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
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
        else if (temp_y[28] == 7 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 2 || temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 2] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 2] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
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
        else if ((temp_y[28] == 6 || temp_y[28] == 4) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 0 || temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 2] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
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
        else if ((temp_y[28] == 6 || temp_y[28] == 4) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
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
        else if ((temp_y[28] == 5 || temp_y[28] == 3) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28]] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
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
        else if ((temp_y[28] == 5 || temp_y[28] == 3) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0)
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 2 || temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 2] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 2] != 'x' &&
                        ((temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28]] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' &&
                             ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] - 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] - 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        }
                        else if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o')
                        {
                            temp_board1[temp_y[28] - 2][temp_x[28]] = 'o';
                        }

                        temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
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
        else if (temp_y[28] == 2 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0)
                    {
                        temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 0 || temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 0)
                    {
                        temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != ' ')))
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] - 2][temp_x[28] + 1] == ' ' && choice[0] == 2)
                    {
                        temp_board1[temp_y[28] - 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
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
        else if (temp_y[28] == 2 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_board1[temp_y[28] - 2][temp_x[28] - 1] == ' ' && choice[0] == 0)
                {
                    temp_board1[temp_y[28] - 2][temp_x[28] - 1] = 'O';
                    temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' &&
                         ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')) &&
                         (temp_board1[temp_y[28] + 1][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28]] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')))
                {
                    temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                    temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[temp_y[28] - 2][temp_x[28]] == ' ' && choice[0] == 2)
                {
                    temp_board1[temp_y[28] - 2][temp_x[28]] = 'O';
                    temp_board1[temp_y[28] - 1][temp_x[28]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !removed_knock);
        }

        //  upwards rightwards --> 0
        else if (temp_y[28] == 0 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 0 || temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 2] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
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
        else if (temp_y[28] == 0 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1)
                    {
                        temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
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
        else if ((temp_y[28] == 1 || temp_y[28] == 3) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 0)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
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
        else if ((temp_y[28] == 1 || temp_y[28] == 3) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 2 || temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 2] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
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
        else if ((temp_y[28] == 2 || temp_y[28] == 4) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            if (temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28]] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 2] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
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
        else if ((temp_y[28] == 2 || temp_y[28] == 4) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 1 || temp_x[28] == 2)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X' &&
                        ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                        (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O' && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X' &&
                             ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 3][temp_x[28]] != ' ')) &&
                             (temp_board1[temp_y[28] + 3][temp_x[28]] != 'X' || (temp_board1[temp_y[28] + 3][temp_x[28]] == 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != ' ')))
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
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
        else if (temp_y[28] == 5 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                {
                    temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[temp_y[28]][temp_x[28] + 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'x' &&
                         ((temp_board1[temp_y[28] - 1][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28]] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28]] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28]] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != ' ')) &&
                         (temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28]] != ' ')))
                {
                    if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                    {

                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                    }
                    else if (temp_board1[temp_y[28] + 1][temp_x[28]] == 'o')
                    {

                        temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                    }

                    temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                    removed_knock = true;
                }
                else if (temp_board1[temp_y[28] + 2][temp_x[28] + 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28]] == 'O')
                {
                    temp_board1[temp_y[28] + 2][temp_x[28] + 1] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28]] = '.';
                    removed_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !removed_knock);
        }

        //  upwards leftwards --> 5
        else if (temp_y[28] == 5 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            if (temp_x[28] == 1)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1)
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] + 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }

                    choice[0]++;
                    count++;
                    if (choice[0] == 3)
                        choice[0] = 0;

                } while (count < 4 && !removed_knock);
            }
            else if (temp_x[28] == 2 || temp_x[28] == 3)
            {
                choice[0] = rand() % 3;

                do
                {
                    if (temp_board1[temp_y[28] + 2][temp_x[28]] == ' ' && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28]] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28]][temp_x[28] - 1] == ' ' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'x' &&
                             ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'x' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X') || ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'x' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'X') && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != ' ')) &&
                             (temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'X' || (temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'X' && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != ' ')))
                    {
                        if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'O';
                        }
                        else if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'o')
                        {

                            temp_board1[temp_y[28]][temp_x[28] - 1] = 'o';
                        }

                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                        removed_knock = true;
                    }
                    else if (temp_board1[temp_y[28] + 2][temp_x[28] - 1] == ' ' && choice[0] == 2 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[28] + 2][temp_x[28] - 1] = 'O';
                        temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
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

    return removed_knock;
}

bool playersKnock_block()
{
    bool blocked_knock{false};
    short int count{};

    if (play_mode != 3)
    {
        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                temp_board1[s][t] = board[s][t];
            }
        }

        for (s = 0; s < 8; s++)
        {
            for (t = 0; t < 4; t++)
            {
                if ((s == 0 || s == 2 || s == 4) && t != 3 && (temp_board1[s + 1][t + 1] == 'o' || temp_board1[s + 1][t + 1] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 0 || s == 2 || s == 4) && t != 0 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t - 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 3 && (temp_board1[s + 1][t] == 'o' || temp_board1[s + 1][t] == 'O') &&
                    (temp_board1[s + 2][t + 1] == ' ' || temp_board1[s + 2][t + 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 1 || s == 3 || s == 5) && t != 0 && (temp_board1[s + 1][t - 1] == 'o' || temp_board1[s + 1][t - 1] == 'O') &&
                    (temp_board1[s + 2][t - 1] == ' ' || temp_board1[s + 2][t - 1] == '.') && (temp_board1[s][t] == 'x' || temp_board1[s][t] == 'X'))
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s + 2;
                    x1_store[count] = t - 1;
                    count++;
                }

                if ((s == 6 || s == 2 || s == 4) && t != 3 && (temp_board1[s - 1][t + 1] == 'o' || temp_board1[s - 1][t + 1] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 6 || s == 2 || s == 4) && t != 0 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t - 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 3 && (temp_board1[s - 1][t] == 'o' || temp_board1[s - 1][t] == 'O') &&
                    (temp_board1[s - 2][t + 1] == ' ' || temp_board1[s - 2][t + 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t + 1;
                    count++;
                }
                if ((s == 7 || s == 3 || s == 5) && t != 0 && (temp_board1[s - 1][t - 1] == 'o' || temp_board1[s - 1][t - 1] == 'O') &&
                    (temp_board1[s - 2][t - 1] == ' ' || temp_board1[s - 2][t - 1] == '.') && temp_board1[s][t] == 'X')
                {
                    temp_y[count] = s;
                    temp_x[count] = t;
                    y1_store[count] = s - 2;
                    x1_store[count] = t - 1;
                    count++;
                }
            }
        }

        if (count > 0)
        {
            auto rand_num{rand() % count};

            temp_y[28] = temp_y[rand_num];
            temp_x[28] = temp_x[rand_num];
            temp_y[29] = y1_store[rand_num];
            temp_x[29] = x1_store[rand_num];
        }
    }

    if (count > 0 || play_mode == 3)
    {
        count = 0;

        // downwards rightwards... y0 --> 7/5/3
        if ((temp_y[28] == 7 || temp_y[28] == 5 || temp_y[28] == 3) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            choice[0] = rand() % 2;

            do
            {
                if ((temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O') && choice[0] == 0 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X')
                {
                    if (temp_board1[temp_y[28] - 1][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] - 1][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] - 3][temp_x[28]] == 'O' && choice[0] == 1 && temp_board1[temp_y[28] - 1][temp_x[28] + 1] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        // downwards leftwards... y0 --> 7/5/3
        else if ((temp_y[28] == 7 || temp_y[28] == 5 || temp_y[28] == 3) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if (temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'O' && choice[0] == 0 && temp_x[29] == 0)
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] - 3][temp_x[28] - 1] == 'O' && choice[0] == 1 && temp_x[29] != 0 && temp_board1[temp_y[28] - 1][temp_x[28] - 2] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'O' || temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'o') && choice[0] == 2 && temp_x[29] != 0 && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28] - 1] != 'x')
                {
                    if (temp_board1[temp_y[28] - 1][temp_x[28] - 2] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] - 1][temp_x[28] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        // downwards rightwards... y0 --> 6/4
        else if ((temp_y[28] == 6 || temp_y[28] == 4) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'O') && choice[0] == 0 && temp_x[29] != 3 && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'x' && temp_board1[temp_y[28] - 3][temp_x[28] + 1] != 'X')
                {
                    if (temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] - 1][temp_x[28] + 2] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'O' && choice[0] == 1 && temp_x[29] != 3 && temp_board1[temp_y[28] - 1][temp_x[28] + 2] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] - 3][temp_x[28] + 1] == 'O' && choice[0] == 2 && temp_x[29] == 3)
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        // downwards leftwards... y0 --> 6/4
        else if ((temp_y[28] == 6 || temp_y[28] == 4) && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            choice[0] = rand() % 2;

            do
            {
                if (temp_board1[temp_y[28] - 3][temp_x[28]] == 'O' && choice[0] == 0 && temp_board1[temp_y[28] - 1][temp_x[28] - 1] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] - 3][temp_x[28]] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o') && choice[0] == 1 && temp_board1[temp_y[28] - 3][temp_x[28]] != 'X' && temp_board1[temp_y[28] - 3][temp_x[28]] != 'x')
                {
                    if (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        // downwards rightwards... y0 --> 2
        else if (temp_y[28] == 2 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3 && temp_x[28] != 2 &&
                 (temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'o' || temp_board1[temp_y[28] - 1][temp_x[28] + 2] == 'O'))
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28] - 1][temp_x[28] + 2] = '.';
            blocked_knock = true;
        }

        // downwards leftwards... y0 --> 2
        else if (temp_y[28] == 2 && temp_y[29] == temp_y[28] - 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0 &&
                 (temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'O' || temp_board1[temp_y[28] - 1][temp_x[28] - 1] == 'o'))
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28] - 1][temp_x[28] - 1] = '.';
            blocked_knock = true;
        }

        //  upwards rightwards --> 0/2/4
        else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'O') && choice[0] == 0 && temp_x[29] != 3 && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'x' && temp_board1[temp_y[28] + 1][temp_x[28] + 2] != 'X')
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'o' || temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'O') && choice[0] == 1 && temp_x[29] == 3)
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28] + 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] + 1][temp_x[28] + 2] == 'O' && choice[0] == 2 && temp_x[29] != 3 && temp_board1[temp_y[28] + 3][temp_x[28] + 1] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28] + 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        //  upwards leftwards --> 0/2/4
        else if ((temp_y[28] == 0 || temp_y[28] == 2 || temp_y[28] == 4) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            choice[0] = rand() % 2;

            do
            {
                if ((temp_board1[temp_y[28] + 3][temp_x[28]] == 'O' || temp_board1[temp_y[28] + 3][temp_x[28]] == 'o') && choice[0] == 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 1] != 'x')
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28]] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] + 1][temp_x[28] - 1] == 'O' && choice[0] == 1 && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        //  upwards rightwards --> 1/3
        else if ((temp_y[28] == 1 || temp_y[28] == 3) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3)
        {
            choice[0] = rand() % 2;

            do
            {
                if (temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O' && choice[0] == 0 && temp_board1[temp_y[28] + 3][temp_x[28]] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[temp_y[28] + 3][temp_x[28]] == 'o' || temp_board1[temp_y[28] + 3][temp_x[28]] == 'O') && choice[0] == 1 && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'X' && temp_board1[temp_y[28] + 1][temp_x[28] + 1] != 'x')
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28]] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28]] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 2)
                    choice[0] = 0;

            } while (count < 3 && !blocked_knock);
        }

        //  upwards leftwards --> 1/3
        else if ((temp_y[28] == 1 || temp_y[28] == 3) && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0)
        {
            choice[0] = rand() % 3;

            do
            {
                if ((temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'O' || temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'o') && choice[0] == 0 && temp_x[29] != 0 && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'X' && temp_board1[temp_y[28] + 1][temp_x[28] - 2] != 'x')
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }
                else if ((temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'O' || temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'o') && choice[0] == 1 && temp_x[29] == 0)
                {
                    if (temp_board1[temp_y[28] + 3][temp_x[28] - 1] == 'O')
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    }
                    else
                    {
                        temp_board1[temp_y[29]][temp_x[29]] = 'o';
                    }

                    temp_board1[temp_y[28] + 3][temp_x[28] - 1] = '.';
                    blocked_knock = true;
                }
                else if (temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'O' && choice[0] == 2 && temp_x[29] != 0 && temp_board1[temp_y[28] + 3][temp_x[28] - 1] != 'X')
                {
                    temp_board1[temp_y[29]][temp_x[29]] = 'O';
                    temp_board1[temp_y[28] + 1][temp_x[28] - 2] = '.';
                    blocked_knock = true;
                }

                choice[0]++;
                count++;
                if (choice[0] == 3)
                    choice[0] = 0;

            } while (count < 4 && !blocked_knock);
        }

        //  upwards rightwards --> 5
        else if (temp_y[28] == 5 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] + 1 && temp_x[28] != 3 &&
                 temp_board1[temp_y[28] + 1][temp_x[28] + 1] == 'O')
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28] + 1][temp_x[28] + 1] = '.';
            blocked_knock = true;
        }

        //  upwards leftwards --> 5
        else if (temp_y[28] == 5 && temp_y[29] == temp_y[28] + 2 && temp_x[29] == temp_x[28] - 1 && temp_x[28] != 0 && temp_x[28] != 1 &&
                 temp_board1[temp_y[28] + 1][temp_x[28] - 2] == 'O')
        {
            temp_board1[temp_y[29]][temp_x[29]] = 'O';
            temp_board1[temp_y[28] + 1][temp_x[28] - 2] = '.';
            blocked_knock = true;
        }
    }

    return blocked_knock;
}

bool knock_antidote()
{
    short int count{};
    bool knock_chosen{false};

    for (s = 0; s < 8; s++)
    {
        for (int t = 0; t < 4; t++)
        {
            if ((s == 0 || s == 2 || s == 4) && t != 3 && (board[s + 1][t + 1] == 'o' || board[s + 1][t + 1] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 2;
                x1_store[count] = t + 1;
                count++;
            }
            if ((s == 0 || s == 2 || s == 4) && t != 0 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 2;
                x1_store[count] = t - 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && (board[s + 1][t] == 'o' || board[s + 1][t] == 'O') &&
                (board[s + 2][t + 1] == ' ' || board[s + 2][t + 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 2;
                x1_store[count] = t + 1;
                count++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && (board[s + 1][t - 1] == 'o' || board[s + 1][t - 1] == 'O') &&
                (board[s + 2][t - 1] == ' ' || board[s + 2][t - 1] == '.') && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s + 2;
                x1_store[count] = t - 1;
                count++;
            }

            if ((s == 6 || s == 2 || s == 4) && t != 3 && (board[s - 1][t + 1] == 'o' || board[s - 1][t + 1] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 2;
                x1_store[count] = t + 1;
                count++;
            }
            if ((s == 6 || s == 2 || s == 4) && t != 0 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 2;
                x1_store[count] = t - 1;
                count++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 3 && (board[s - 1][t] == 'o' || board[s - 1][t] == 'O') &&
                (board[s - 2][t + 1] == ' ' || board[s - 2][t + 1] == '.') && board[s][t] == 'X')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 2;
                x1_store[count] = t + 1;
                count++;
            }
            if ((s == 7 || s == 3 || s == 5) && t != 0 && (board[s - 1][t - 1] == 'o' || board[s - 1][t - 1] == 'O') &&
                (board[s - 2][t - 1] == ' ' || board[s - 2][t - 1] == '.') && board[s][t] == 'X')
            {
                temp_y[count] = s;
                temp_x[count] = t;
                y1_store[count] = s - 2;
                x1_store[count] = t - 1;
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
            y[2] = temp_y[index];
            x[2] = temp_x[index];
            y[3] = y1_store[index];
            x[3] = x1_store[index];

            temp_y[28] = y[2];
            temp_y[29] = y[3];
            temp_x[28] = x[2];
            temp_x[29] = x[3];

            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board1[s][t] = board[s][t];
                }
            }

            bool knock_blocked = playersKnock_block();
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board2[s][t] = temp_board1[s][t];
                }
            }

            totalKnocks_b = maxKnocks_player();

            if ((knock_blocked && !knock_chosen) || totalKnocks_b < totalKnocks_r)
            {
                knock_chosen = true;
                for (s = 0; s < 8; s++)
                {
                    for (t = 0; t < 4; t++)
                    {
                        final_board[s][t] = temp_board2[s][t];
                        temp_board1[s][t] = board[s][t];
                    }
                }
            }

            temp_y[28] = y[2];
            temp_y[29] = y[3];
            temp_x[28] = x[2];
            temp_x[29] = x[3];

            bool knock_removed = playersKnock_remove();
            for (s = 0; s < 8; s++)
            {
                for (t = 0; t < 4; t++)
                {
                    temp_board2[s][t] = temp_board1[s][t];
                }
            }

            totalKnocks_r = maxKnocks_player();

            if ((knock_removed && !knock_chosen) || totalKnocks_r < totalKnocks_b)
            {
                knock_chosen = true;
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

        if (knock_chosen)
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

    return knock_chosen;
}

bool x_chase()
{
    short int row0[30]{};
    short int row1[30]{};
    short int column0[30]{};
    short int column1[30]{};
    short int row_o[20]{};
    short int column_o[20]{};
    short int count[4]{};
    short int section{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // upwards rightwards
            if ((s == 0 || s == 2 || s == 4) && t != 3 && board[s + 1][t + 1] == ' ' && board[s + 2][t + 1] != 'O' && board[s + 2][t + 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'O' || (board[s][t + 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t + 1;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t + 1;
                count[0]++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 3 && board[s + 1][t] == ' ' && board[s + 2][t + 1] != 'o' && board[s + 2][t + 1] != 'O' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t + 1] != ' ')) &&
                (board[s][t + 1] != 'O' || (board[s][t + 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t;
                count[0]++;
            }

            // upwards leftwards
            if ((s == 0 || s == 2 || s == 4) && t != 0 && board[s + 1][t] == ' ' && board[s + 2][t - 1] != 'O' && board[s + 2][t - 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'O' || (board[s][t - 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t;
                count[0]++;
            }
            if ((s == 0 || s == 2 || s == 4) && t == 0 && board[s + 1][t] == ' ' && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t;
                count[0]++;
            }
            if ((s == 1 || s == 3 || s == 5) && t != 0 && board[s + 1][t - 1] == ' ' && board[s + 2][t - 1] != 'O' && board[s + 2][t - 1] != 'o' &&
                ((board[s + 2][t] != 'o' && board[s + 2][t] != 'O') || ((board[s + 2][t] == 'o' || board[s + 2][t] == 'O') && board[s][t - 1] != ' ')) &&
                (board[s][t - 1] != 'O' || (board[s][t - 1] == 'O' && board[s + 2][t] != ' ')) && (board[s][t] == 'x' || board[s][t] == 'X'))
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s + 1;
                column1[count[0]] = t - 1;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t;
                count[0]++;
            }
            if (s == 1 && board[s - 1][t] == ' ' && board[s][t] == 'X')
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t;
                count[0]++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s - 1][t + 1] == ' ' && board[s - 2][t + 1] != 'O' &&
                ((board[s][t + 1] != 'o' && board[s][t + 1] != 'O') || ((board[s][t + 1] == 'o' || board[s][t + 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t + 1] != ' ')) && board[s][t] == 'X')
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t + 1;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t - 1;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t - 1;
                count[0]++;
            }
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s - 1][t] == ' ' && board[s - 2][t - 1] != 'O' &&
                ((board[s][t - 1] != 'o' && board[s][t - 1] != 'O') || ((board[s][t - 1] == 'o' || board[s][t - 1] == 'O') && board[s - 2][t] != ' ')) &&
                (board[s - 2][t] != 'O' || (board[s - 2][t] == 'O' && board[s][t - 1] != ' ')) && board[s][t] == 'X')
            {
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t;
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
                row0[count[0]] = s;
                column0[count[0]] = t;
                row1[count[0]] = s - 1;
                column1[count[0]] = t;
                count[0]++;
            }
        }
    }
    std::cout << "\n        count[0]: " << count[0];
    std::cout << "\n        count[1]: " << count[1];

    short int free_y0[20]{};
    short int free_y1[20]{};
    short int free_x0[20]{};
    short int free_x1[20]{};

    bool pass{false};

    auto total_moves = total_unknock_moves();
    std::cout << "\n        total_moves: " << total_moves;

    for (s = 0; s < total_moves; s++)
    {
        for (t = 0; t < count[1]; t++)
        {
            if (temp_y[s] == row_o[t] && temp_x[s] == column_o[t])
                pass = true;
        }
        if (!pass)
        {
            free_y0[count[2]] = temp_y[s];
            free_x0[count[2]] = temp_x[s];
            free_y1[count[2]] = y1_store[s];
            free_x1[count[2]] = x1_store[s];
            count[2]++;
        }
    }

    std::cout << "\n        count[2]: " << count[2];

    bool chased{false};
    short int round{};
    short int number{};

    while (round < count[0] && count[0] > 0 && count[2] > 0 && !chased)
    {
        y[0] = row0[round];
        y[1] = row1[round];
        x[0] = column0[round];
        x[1] = column1[round];

        for (t = 0; t < count[2]; t++)
        {
            choice[0] = rand() % 20;
            number = 0;

            do
            {
                // downwards rightwards... y0 --> 7/5/3
                if (choice[0] == 0 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && y[1] == y[0] - 1 && x[1] == x[0] && x[0] != 3 && board[y[0] - 2][x[0] + 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] + 1 == free_x1[t])
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
                    chased = true;
                }
                // downwards leftwards... y0 --> 7/5/3
                else if (choice[0] == 1 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && y[1] == y[0] - 1 && x[1] == x[0] - 1 && x[0] != 0 && board[y[0] - 2][x[0] - 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] - 1 == free_x1[t])
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
                    chased = true;
                }
                // downwards rightwards... y0 --> 6/4
                else if (choice[0] == 2 && (y[0] == 6 || y[0] == 4) && y[1] == y[0] - 1 && x[1] == x[0] + 1 && x[0] != 3 && board[y[0] - 2][x[0] + 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] + 1 == free_x1[t])
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
                    chased = true;
                }

                // downwards leftwards... y0 --> 6/4
                else if (choice[0] == 3 && (y[0] == 6 || y[0] == 4) && y[1] == y[0] - 1 && x[1] == x[0] && x[0] != 0 && board[y[0] - 2][x[0] - 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] - 1 == free_x1[t])
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
                    chased = true;
                }

                // downwards rightwards... y0 --> 2
                else if (choice[0] == 4 && y[0] == 2 && y[1] == y[0] - 1 && x[1] == x[0] + 1 && x[0] != 3 && x[0] != 2 && board[y[0] - 2][x[0] + 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] + 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }

                // downwards leftwards... y0 --> 2
                else if (choice[0] == 5 && y[0] == 2 && y[1] == y[0] - 1 && x[1] == x[0] && x[0] != 0 && board[y[0] - 2][x[0] - 1] == ' ' && y[0] - 2 == free_y1[t] && x[0] - 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }

                //  upwards rightwards --> 0/2/4
                else if (choice[0] == 6 && (y[0] == 0 || y[0] == 2 || y[0] == 4) && y[1] == y[0] + 1 && x[1] == x[0] + 1 && x[0] != 3 && board[y[0] + 2][x[0] + 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] + 1 == free_x1[t])
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
                    chased = true;
                }

                //  upwards leftwards --> 0/2/4
                else if (choice[0] == 7 && (y[0] == 0 || y[0] == 2 || y[0] == 4) && y[1] == y[0] + 1 && x[1] == x[0] && x[0] != 0 && board[y[0] + 2][x[0] - 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] - 1 == free_x1[t])
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
                    chased = true;
                }

                //  upwards rightwards --> 1/3
                else if (choice[0] == 8 && (y[0] == 1 || y[0] == 3) && y[1] == y[0] + 1 && x[1] == x[0] && x[0] != 3 && board[y[0] + 2][x[0] + 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] + 1 == free_x1[t])
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
                    chased = true;
                }

                //  upwards leftwards --> 1/3
                else if (choice[0] == 9 && (y[0] == 1 || y[0] == 3) && y[1] == y[0] + 1 && x[1] == x[0] - 1 && x[0] != 0 && board[y[0] + 2][x[0] - 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] - 1 == free_x1[t])
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
                    chased = true;
                }

                //  upwards rightwards --> 5
                else if (choice[0] == 10 && y[0] == 5 && y[1] == y[0] + 1 && x[1] == x[0] && x[0] != 3 && board[y[0] + 2][x[0] + 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] + 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }

                //  upwards leftwards --> 5
                else if (choice[0] == 11 && y[0] == 5 && y[1] == y[0] + 1 && x[1] == x[0] - 1 && x[0] != 0 && x[0] != 1 && board[y[0] + 2][x[0] - 1] == ' ' && y[0] + 2 == free_y1[t] && x[0] - 1 == free_x1[t])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }

                // ------------------------------------------------------------------------- //

                // downwards rightwards 7/5/3
                else if (choice[0] == 12 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && y[1] == y[0] - 1 && x[0] == 3 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }
                // upwards rightwards 6
                else if (choice[0] == 13 && choice[0] == 1 && y[0] == 6 && y[1] == y[0] + 1 && x[0] != 3 && x[1] == x[0] + 1 && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }
                // downwards rightwards 1
                else if (choice[0] == 14 && y[0] == 1 && y[1] == y[0] - 1 && x[0] != 3 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }
                // downwards leftwards 6/4/2
                else if (choice[0] == 15 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && y[1] == y[0] - 1 && x[0] == 0 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }
                // downwards leftwards 1
                else if (choice[0] == 16 && y[0] == 1 && y[1] == y[0] - 1 && x[0] != 0 && x[1] == x[0] - 1 && free_y1[t] == y[1] && free_x1[t] == x[1])
                {
                    board[free_y1[t]][free_x1[t]] = 'O';
                    board[free_y0[t]][free_x0[t]] = '.';
                    chased = true;
                }
                // upwards rightwards 1/3/5
                else if (choice[0] == 17 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && y[1] == y[0] + 1 && x[0] == 3 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }
                // upwards leftwards 0/2/4
                else if (choice[0] == 18 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && y[1] == y[0] + 1 && x[0] == 0 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }
                // upwards leftwards 6
                else if (choice[0] == 19 && choice[0] == 0 && y[0] == 6 && y[1] == y[0] + 1 && x[0] != 0 && x[1] == x[0] && free_y1[t] == y[1] && free_x1[t] == x[1])
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
                    chased = true;
                }

                number++;
                choice[0]++;
                if (choice[0] == 20)
                    choice[0] = 0;

            } while (number < 21 && !chased);
            if (chased)
                break;
        }

        round++;
    }

    std::cout << "\n        chased 1: " << std::boolalpha << chased;

    /*------------------------------------- !CHASED --------------------------------------*/

    if (!chased && count[0] > 0 && count[2] > 0)
    {
        /* getting player's free target */
        for (s = 7; s >= 0; s--)
        {
            for (t = 0; t < 4; t++)
            {
                for (short int u = 0; u < count[0]; u++)
                {
                    if (row1[u] == s && column1[u] == t)
                    {
                        /* players target already detected */
                        for (short int v = 7; v >= 0; v--)
                        {
                            if (t == 0 || t == 1)
                            {
                                for (short int w = 1; w < 4; w++)
                                {
                                    /* getting free comp targets */
                                    for (short int x = 0; x < count[2]; x++)
                                    {
                                        if (free_y1[x] == v && free_x1[x] == w)
                                        {
                                            if (board[free_y0[x]][free_x0[x]] == 'O')
                                            {
                                                board[free_y1[x]][free_x1[x]] = 'O';
                                            }
                                            else if (board[free_y0[x]][free_x0[x]] == 'o')
                                            {
                                                board[free_y1[x]][free_x1[x]] = 'o';
                                            }

                                            board[free_y0[x]][free_x0[x]] = '.';
                                            chased = true;
                                            break;
                                        }
                                    }
                                    if (chased)
                                        break;
                                }
                            }
                            else if (t == 2 || t == 3)
                            {
                                for (short int w = 2; w <= 0; w--)
                                {
                                    /* getting free comp targets */
                                    for (short int x = 0; x < count[2]; x++)
                                    {
                                        if (free_y1[x] == v && free_x1[x] == w)
                                        {
                                            if (board[free_y0[x]][free_x0[x]] == 'O')
                                            {
                                                board[free_y1[x]][free_x1[x]] = 'O';
                                            }
                                            else if (board[free_y0[x]][free_x0[x]] == 'o')
                                            {
                                                board[free_y1[x]][free_x1[x]] = 'o';
                                            }

                                            board[free_y0[x]][free_x0[x]] = '.';
                                            chased = true;
                                            break;
                                        }
                                    }
                                    if (chased)
                                        break;
                                }
                            }
                            if (chased)
                                break;
                        }
                    }
                    if (chased)
                        break;
                }
                if (chased)
                    break;
            }
            if (chased)
                break;
        }
    }

    std::cout << "\n        chased 2: " << std::boolalpha << chased;

    return chased;
}

short int check_winner(bool count)
{
    short int player_moves{};

    for (s = 0; s < 8; s++)
    {
        for (t = 0; t < 4; t++)
        {
            // downwards rightwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && board[s][t] == 'X' && board[s - 1][t] == ' ')
            {
                player_moves++;
            }

            // downwards leftwards - odd
            if ((s == 7 || s == 5 || s == 3 || s == 1) && t != 0 && board[s][t] == 'X' && board[s - 1][t - 1] == ' ')
            {
                player_moves++;
            }

            // downwards rightwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 3 && board[s][t] == 'X' && board[s - 1][t + 1] == ' ')
            {
                player_moves++;
            }

            // downwards leftwards - even
            if ((s == 6 || s == 4 || s == 2) && t != 0 && board[s][t] == 'X' && board[s - 1][t] == ' ')
            {
                player_moves++;
            }

            // upwards rightwards - odd
            if ((s == 1 || s == 5 || s == 3) && (board[s][t] == 'X' || board[s][t] == 'x') && board[s + 1][t] == ' ')
            {
                player_moves++;
            }

            // upwards leftwards - odd
            if ((s == 1 || s == 5 || s == 3) && t != 0 && (board[s][t] == 'X' || board[s][t] == 'x') && board[s + 1][t - 1] == ' ')
            {
                player_moves++;
            }

            // upwards rightwards - even
            if ((s == 0 || s == 4 || s == 2 || s == 6) && t != 3 && (board[s][t] == 'X' || board[s][t] == 'x') && board[s + 1][t + 1] == ' ')
            {
                player_moves++;
            }

            // upwards leftwards - even
            if ((s == 0 || s == 4 || s == 2) && (board[s][t] == 'X' || board[s][t] == 'x') && board[s + 1][t] == ' ')
            {
                player_moves++;
            }
        }
    }

    auto comp_moves = total_compMoves();

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

    if ((draw_count[2] == draw_count[0] && draw_count[3] == draw_count[0]) && total_comp_pieces < 4 && total_player_pieces < 4 && count)
        draw_count[4]++;
    else if (((draw_count[2] != draw_count[0] && draw_count[3] == draw_count[0]) || (draw_count[2] == draw_count[0] && draw_count[3] != draw_count[0]) || (draw_count[2] != draw_count[0] && draw_count[3] != draw_count[0])) && total_comp_pieces < 4 && total_player_pieces < 4 && count)
        draw_count[4] = 0;

    if (draw_count[4] == 12)
        return 3;
    else if (player_moves == 0 && comp_moves > 0)
        return 2;
    else if (comp_moves == 0 && player_moves > 0)
        return 1;
    else
        return 0;
}

void print_winner(int winner)
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