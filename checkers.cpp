#include <iostream>
#include <ctime>
#include <cstdlib>

char box[8][4]{};
char temp_box1[8][4]{};
char temp_box2[8][4]{};

const unsigned short int max_length{20};
char player_name[max_length]{};

unsigned short int play_mode{2};
unsigned short int choice[3]{};
unsigned short int y[2];
unsigned short int x[2];
unsigned short int temp_y[20]{};
unsigned short int temp_x[20]{};
unsigned short int y1_store[20]{};
unsigned short int x1_store[20]{};

void reset_board();
void print_board();

void player();
bool choice_processing(int index);
bool select_piece();
bool movePiece_player();
bool more_knocks();

void computer();
bool knocks_checking(int *total_knocks);
void row_select();
int direct_unknock_moves();
void column_select();
void movePiece_comp(char knock);
bool future_Knock_byPlayer();
int future_maxKnocks_comp();
bool future_more_knocks();
int future_maxKnocks_player();

int totalMoves_comp();

int main()
{
    srand(time(0));
    /*
    bool end{true};
    bool winner{false};

    std::cout << '\n';
    std::cout << "        Enter your name dear: ";

    char temp_name[max_length]{};
    std::cin.getline(temp_name, max_length);

    for (size_t i{}; i < std::size(temp_name); ++i)
    {
        if (temp_name[i] == ' ')
        {
            break;
        }
        temp_name[i] = std::toupper(temp_name[i]);
        player_name[i] = temp_name[i];
    }

    std::cout << std::endl;
    std::cout << "           ID  |  MODE" << std::endl;
    std::cout << "        -------|---------" << std::endl;
    std::cout << "            1  |  Easy" << std::endl;
    std::cout << "            2  |  Normal" << std::endl;
    std::cout << "            3  |  Hard" << std::endl;
    std::cout << std::endl;
    while (play_mode != 1 && play_mode != 2 && play_mode != 3)
    {
        std::cout << "        Enter mode ID: ";
        std::cin >> play_mode;
    }
*/
    reset_board();
    print_board();
    for (size_t i = 0; i < 1; i++)
    {
        computer();
    }

    return 0;
}

void reset_board()
{
    for (size_t row{}; row < 8; row++)
    {
        for (size_t column{}; column < 4; column++)
        {
            box[row][column] = ' ';
            temp_box1[row][column] = ' ';
            temp_box2[row][column] = ' ';
        }
    }

    // players pieces
    for (size_t row{}; row < 3; row++)
    {
        for (size_t column{}; column < 4; column++)
        {
            box[row][column] = ' ';
        }
    }

    // comp pieces
    for (size_t row{5}; row <= 7; row++)
    {
        for (size_t column{}; column < 4; column++)
        {
            box[row][column] = ' ';
        }
    }

    box[2][0] = 'X';
    box[2][2] = 'X';
    box[4][1] = 'O';
    box[6][0] = 'X';
    box[6][2] = 'x';
}

void print_board()
{
    std::cout << '\n';
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << '\n';
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        8   | " << box[7][0] << " |   | " << box[7][1] << " |   | " << box[7][2] << " |   | " << box[7][3] << " |   |   8" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        7   |   | " << box[6][0] << " |   | " << box[6][1] << " |   | " << box[6][2] << " |   | " << box[6][3] << " |   7" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        6   | " << box[5][0] << " |   | " << box[5][1] << " |   | " << box[5][2] << " |   | " << box[5][3] << " |   |   6" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        5   |   | " << box[4][0] << " |   | " << box[4][1] << " |   | " << box[4][2] << " |   | " << box[4][3] << " |   5" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        4   | " << box[3][0] << " |   | " << box[3][1] << " |   | " << box[3][2] << " |   | " << box[3][3] << " |   |   4" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        3   |   | " << box[2][0] << " |   | " << box[2][1] << " |   | " << box[2][2] << " |   | " << box[2][3] << " |   3" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        2   | " << box[1][0] << " |   | " << box[1][1] << " |   | " << box[1][2] << " |   | " << box[1][3] << " |   |   2" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "        1   |   | " << box[0][0] << " |   | " << box[0][1] << " |   | " << box[0][2] << " |   | " << box[0][3] << " |   1" << std::endl;
    std::cout << "            |---|---|---|---|---|---|---|---|" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "              1   2   3   4   5   6   7   8  " << std::endl;
    std::cout << "" << std::endl;
}

void player()
{
    std::cout << '\n';
    std::cout << "        =========================================" << std::endl;
    std::cout << "                       YOUR TURN" << std::endl;
    std::cout << "        =========================================" << std::endl;
    print_board();

    // removing '.'
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (box[i][j] == '.')
            {
                box[i][j] = ' ';
            }
        }
    }

    bool not_played{true};
    bool invalid_choice{true};
    bool knock_available{false};
    bool unselected{true};

    do
    {
        do
        {
            std::cout << "        Enter piece  row# column# e.g 12: ";
            std::cin >> choice[0];
            invalid_choice = choice_processing(0);

            if (invalid_choice)
            {
                print_board();
                std::cout << "        Invalid piece entry! Try again!" << std::endl;
            }

        } while (invalid_choice);

        unselected = select_piece();
        if (unselected)
        {
            print_board();
            std::cout << "        Invalid piece entry! Try again!" << std::endl;
        }

    } while (unselected);

    std::cout << "        -----------------------------------------" << std::endl;
    std::cout << "          SELECTED " << player_name << std::endl;
    std::cout << "        -----------------------------------------" << std::endl;
    print_board();

    do
    {
        do
        {
            std::cout << "        Enter target row# column# e.g 23: ";
            std::cin >> choice[1];
            invalid_choice = choice_processing(1);

            if (invalid_choice)
            {
                print_board();
                std::cout << "        Invalid target entry! Try again!" << std::endl;
            }

        } while (invalid_choice);

        not_played = movePiece_player();
        if (not_played)
        {
            print_board();
            std::cout << "        Invalid target entry! Try again!" << std::endl;
        }

    } while (not_played);

    while (knock_available = more_knocks())
    {
        if (box[y[1]][x[1]] == 'X')
        {
            box[y[1]][x[1]] = 'S';
        }
        else
        {
            box[y[1]][x[1]] = 's';
        }

        y[0] = y[1];
        x[0] = x[1];

        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "               CONSECUTIVE KNOCK AVAILABLE " << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;
        print_board();

        do
        {
            do
            {
                std::cout << "        Enter target row# column# e.g 23: ";
                std::cin >> choice[1];
                invalid_choice = choice_processing(1);

                if (invalid_choice)
                {
                    print_board();
                    std::cout << "        Invalid target entry! Try again!" << std::endl;
                }

            } while (invalid_choice);

            not_played = movePiece_player();
            if (not_played)
            {
                print_board();
                std::cout << "        Invalid target entry! Try again!" << std::endl;
            }

        } while (not_played);
    }

    std::cout << "        -----------------------------------------" << std::endl;
    std::cout << "          MOVED " << player_name << std::endl;
    std::cout << "        -----------------------------------------" << std::endl;
    print_board();
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
        // converting choice from 1D to 2D

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

bool select_piece()
{
    bool unselected{true};

    // selecting to move up
    if (box[y[0]][x[0]] == 'x' || box[y[0]][x[0]] == 'X')
    {
        // moving up without knock
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && (box[y[0] + 1][x[0]] == ' ' || box[y[0] + 1][x[0]] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == ' ' || box[y[0] + 1][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && (box[y[0] + 1][x[0]] == ' ' || box[y[0] + 1][x[0]] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == ' ' || box[y[0] + 1][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        // moving up with knock
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[0] + 2][x[0] + 1] == ' ' || box[y[0] + 2][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[0] + 2][x[0] - 1] == ' ' || box[y[0] + 2][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[0] + 2][x[0] + 1] == ' ' || box[y[0] + 2][x[0] + 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'o' || box[y[0] + 1][x[0] - 1] == 'O') &&
                 (box[y[0] + 2][x[0] - 1] == ' ' || box[y[0] + 2][x[0] - 1] == '.'))
        {
            if (box[y[0]][x[0]] == 'x')
            {
                box[y[0]][x[0]] = 's';
            }
            else
            {
                box[y[0]][x[0]] = 'S';
            }

            unselected = false;
        }
    }
    if (box[y[0]][x[0]] == 'X' && unselected == 'N')
    {
        // moving down without knock
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == ' ' || box[y[0] - 1][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == ' ' || box[y[0] - 1][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }

        // moving down with knock
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            unselected = false;
        }
    }

    return unselected;
}

bool movePiece_player()
{
    bool not_moved{true};
    bool unchanged{true};

    if (box[y[0]][x[0]] == 'S')
    {
        box[y[0]][x[0]] = 'X';
        unchanged = false;
    }
    else if (box[y[0]][x[0]] == 's')
    {
        box[y[0]][x[0]] = 'x';
        unchanged = false;
    }

    // moving up without knock
    if (y[0] + 1 == y[1])
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';

            not_moved = false;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
        }
    }

    // moving down without knock
    else if (y[0] - 1 == y[1] && box[y[0]][x[0]] == 'X')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
    }

    // moving up with knock
    else if (y[0] + 2 == y[1])
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'o' || box[y[0] + 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            not_moved = false;

            if (box[y[0]][x[0]] == 'X')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
        }
    }

    // moving down with knock
    else if (y[0] - 2 == y[1] && box[y[0]][x[0]] == 'X')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            not_moved = false;
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
        }
    }

    if (unchanged == false)
    {
        if (box[y[0]][x[0]] == 'X')
        {
            box[y[0]][x[0]] = 's';
        }
        else if (box[y[0]][x[0]] == 'x')
        {
            box[y[0]][x[0]] = 's';
        }
    }

    // king
    for (size_t column = 0; column < 4; column++)
    {
        if (box[7][column] == 'x')
        {
            box[7][column] = 'X';
        }
    }

    return not_moved;
}

bool more_knocks()
{
    bool knock_present{false};

    if ((box[y[1]][x[1]] == 'x' || box[y[1]][x[1]] == 'X'))
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'o' || box[y[1] + 1][x[1] - 1] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'o' || box[y[1] + 1][x[1] + 1] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (box[y[1]][x[1]] == 'X')
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'o' || box[y[1] - 1][x[1] - 1] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'o' || box[y[1] - 1][x[1] + 1] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if ((box[y[1]][x[1]] == 'o' || box[y[1]][x[1]] == 'O'))
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'x' || box[y[1] - 1][x[1] - 1] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'x' || box[y[1] - 1][x[1] + 1] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }
    if (box[y[1]][x[1]] == 'O')
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'x' || box[y[1] + 1][x[1] - 1] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = true;
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'x' || box[y[1] + 1][x[1] + 1] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = true;
        }
    }

    return knock_present;
}

void computer()
{
    std::cout << '\n';
    std::cout << "        =========================================" << std::endl;
    std::cout << "                       COMP'S TURN" << std::endl;
    std::cout << "        =========================================" << std::endl;
    std::cout << "        Thinking...";
    // remove later
    std::cout << std::endl;

    char temp_box3[8][4]{};

    // removing '.'
    for (size_t f{}; f < 8; f++)
    {
        for (size_t g{}; g < 4; g++)
        {
            if (box[f][g] == '.')
            {
                box[f][g] = ' ';
                temp_box3[f][g] = ' ';
            }
        }
    }

    int total_knocks{};
    unsigned short int rand_num{};
    bool knock_present = knocks_checking(&total_knocks);
    bool selected{false};
    bool moved{false};

    if (play_mode == 1)
    {
        rand_num = rand() % 4;

        if (rand_num == 2 && knock_present)
        {
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
            y[1] = y1_store[rand_num];
            x[1] = x1_store[rand_num];

            movePiece_comp('Y');
            moved = true;
        }

        if (!moved)
        {
            row_select();
            column_select();
            movePiece_comp('N');
        }

        while (knock_present = knocks_checking(&total_knocks))
        {
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
            y[1] = y1_store[rand_num];
            x[1] = x1_store[rand_num];

            movePiece_comp('Y');
        }
    }

    else if (play_mode == 2)
    {
        rand_num = rand() % 2;

        if ((rand_num == 3 || rand_num == 3) && knock_present)
        {
            std::cout << "knock_present: " << std::boolalpha << knock_present << std::endl;
            rand_num = rand() % 2;

            if (rand_num == 0 || rand_num == 1)
            {
                while (!selected)
                {
                    short int max_knocks{};
                    short int index{};

                    do
                    {
                        y[0] = temp_y[index];
                        x[0] = temp_x[index];

                        auto total_comp_knocks = future_maxKnocks_comp();
                        auto total_player_knocks = future_maxKnocks_player();

                        if(total_player_knocks > total_comp_knocks) std::cout << "player knocks more\n" ;

                        if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
                        {
                            std::cout << "checked for future knocks" << std::endl;
                            max_knocks = total_comp_knocks;
                            for (short int c = 0; c < 8; c++)
                            {
                                for (short int d = 0; d < 4; d++)
                                {
                                    temp_box3[c][d] = temp_box2[c][d];
                                }
                            }

                            selected = true;
                        }

                        index++;

                    } while (index < total_knocks);

                    if (selected)
                    {
                        for (short int c = 0; c < 8; c++)
                        {
                            for (short int d = 0; d < 4; d++)
                            {
                                box[c][d] = temp_box3[c][d];
                            }
                        }

                        moved = true;
                    }
                }
            }
        }

        if (!moved)
        {

            do
            {
                for (short int re_do = 0; re_do < 5100; re_do++)
                {

                    row_select();
                    column_select();

                    bool future_knock {future_Knock_byPlayer()};
                    if (!future_knock)
                    {
                        for (short int c = 0; c < 8; c++)
                        {
                            for (short int d = 0; d < 4; d++)
                            {
                                box[c][d] = temp_box2[c][d];
                            }
                        }

                        moved = true;
                    }

                    if (moved)
                        break;
                    else if (!moved && re_do == 50)
                    {
                        std::cout << "No choice" << std::endl;
                        row_select();
                        column_select();
                        movePiece_comp('N');
                        moved = true;
                        break;
                    }
                }

            } while (!moved);
        }
    }

    std::cout << '\n';
    print_board();
}

bool knocks_checking(int *total_knocks)
{
    bool knock_present{false};
    *total_knocks = 0;

    for (size_t q = 0; q <= 7; q++)
    {
        for (size_t r = 0; r < 4; r++)
        {
            // checking upwards

            if ((q == 0 || q == 2 || q == 4) && r != 3 && (box[q + 1][r + 1] == 'x' || box[q + 1][r + 1] == 'X') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 0 || q == 2 || q == 4) && r != 0 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r = 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 3 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 0 && (box[q + 1][r - 1] == 'x' || box[q + 1][r - 1] == 'X') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q + 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
            // checking downwards

            if ((q == 6 || q == 2 || q == 4) && r != 3 && (box[q - 1][r + 1] == 'x' || box[q - 1][r + 1] == 'X') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 6 || q == 2 || q == 4) && r != 0 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 3 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r + 1;
                *total_knocks = *total_knocks + 1;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 0 && (box[q - 1][r - 1] == 'x' || box[q - 1][r - 1] == 'X') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
            {
                temp_y[*total_knocks] = q;
                temp_x[*total_knocks] = r;
                y1_store[*total_knocks] = q - 2;
                x1_store[*total_knocks] = r - 1;
                *total_knocks = *total_knocks + 1;
            }
        }
    }

    if (*total_knocks > 0)
        knock_present = true;

    return knock_present;
}

void row_select()
{
    auto count = direct_unknock_moves();
    auto temp_play_mode{play_mode};

    if (count == 0)
        temp_play_mode = 1;

    bool chosen{false};

    while (!chosen)
    {
        y[0] = rand() % 8;

        if (temp_play_mode == 1)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                choice[0] = rand() % 8;
                short int count{};

                do
                {

                    // downwards rightwards - odd
                    if (choice[0] == 0 && (y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // downwards leftwards - odd
                    if (choice[0] == 1 && (y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // downwards rightwards - even
                    if (choice[0] == 2 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // downwards leftwards - even
                    if (choice[0] == 3 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards rightwards - odd
                    if (choice[0] == 4 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards leftwards - odd
                    if (choice[0] == 5 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards rightwards - even
                    if (choice[0] == 6 && (y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards leftwards - even
                    if (choice[0] == 7 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    count++;
                    choice[0]++;
                    if (choice[0] == 8)
                        choice[0] = 0;

                } while (count <= 8);

                if (chosen)
                    break;
            }
        }

        else if (temp_play_mode == 2 || temp_play_mode == 3)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                choice[0] = rand() % 16;
                short int count{};

                do
                {

                    // downwards rightwards - odd
                    if (choice[0] == 0 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                        ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                        (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 1 && y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 2 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // downwards leftwards - odd
                    if (choice[0] == 3 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                        ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                        (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 4 && y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // downwards rightwards - even
                    if (choice[0] == 5 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                        ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                        (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                    {
                        chosen = true;
                        break;
                    }

                    // downwards leftwards - even
                    if (choice[0] == 6 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                        ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                        (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 7 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards rightwards - odd
                    if (choice[0] == 8 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                        ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                        (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 9 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] + 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards leftwards - odd
                    if (choice[0] == 10 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                        ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                        (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                    {
                        chosen = true;
                        break;
                    }

                    // upwards rightwards - even
                    if (choice[0] == 11 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                        ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                        (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 12 && y[0] == 6 && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    // upwards leftwards - even
                    if (choice[0] == 13 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                        ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                        (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 14 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }
                    if (choice[0] == 15 && y[0] == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                    {
                        chosen = true;
                        break;
                    }

                    count++;
                    choice[0]++;
                    if (choice[0] == 16)
                        choice[0] = 0;

                } while (count <= 16);

                if (chosen)
                    break;
            }
        }
    }
}

int direct_unknock_moves()
{
    unsigned short int count{};

    for (size_t c = 0; c < 8; c++)
    {
        for (size_t d = 0; d < 4; d++)
        {
            // downwards rightwards - odd
            if ((c == 7 || c == 5 || c == 3) && x[0] != 3 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0]] == ' ' && box[c - 2][x[0] + 1] != 'x' && box[c - 2][x[0] + 1] != 'X' &&
                ((box[c - 2][x[0]] != 'x' && box[c - 2][x[0]] != 'X') || ((box[c - 2][x[0]] == 'x' || box[c - 2][x[0]] == 'X') && box[c][x[0] + 1] != ' ')) &&
                (box[c][x[0] + 1] != 'X' || (box[c][x[0] + 1] == 'X' && box[c - 2][x[0]] != ' ')))
            {
                count++;
            }
            if (c == 1 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0]] == ' ')
            {
                count++;
            }
            if ((c == 7 || c == 5 || c == 3) && x[0] == 3 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0]] == ' ')
            {
                count++;
            }

            // downwards leftwards - odd
            if ((c == 7 || c == 5 || c == 3) && x[0] != 0 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0] - 1] == ' ' && box[c - 2][x[0] - 1] != 'x' && box[c - 2][x[0] - 1] != 'X' &&
                ((box[c - 2][x[0]] != 'x' && box[c - 2][x[0]] != 'X') || ((box[c - 2][x[0]] == 'x' || box[c - 2][x[0]] == 'X') && box[c][x[0] - 1] != ' ')) &&
                (box[c][x[0] - 1] != 'X' || (box[c][x[0] - 1] == 'X' && box[c - 2][x[0]] != ' ')))
            {
                count++;
            }
            if (c == 1 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0] - 1] == ' ')
            {
                count++;
            }

            // downwards rightwards - even
            if ((c == 6 || c == 4 || c == 2) && x[0] != 3 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0] + 1] == ' ' && box[c - 2][x[0] + 1] != 'x' && box[c - 2][x[0] + 1] != 'X' &&
                ((box[c - 2][x[0]] != 'x' && box[c - 2][x[0]] != 'X') || ((box[c - 2][x[0]] == 'x' || box[c - 2][x[0]] == 'X') && box[c][x[0] + 1] != ' ')) &&
                (box[c][x[0] + 1] != 'X' || (box[c][x[0] + 1] == 'X' && box[c - 2][x[0]] != ' ')))
            {
                count++;
            }

            // downwards leftwards - even
            if ((c == 6 || c == 4 || c == 2) && x[0] != 0 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0]] == ' ' && box[c - 2][x[0] - 1] != 'x' && box[c - 2][x[0] - 1] != 'X' &&
                ((box[c - 2][x[0]] != 'x' && box[c - 2][x[0]] != 'X') || ((box[c - 2][x[0]] == 'x' || box[c - 2][x[0]] == 'X') && box[c][x[0] - 1] != ' ')) &&
                (box[c][x[0] - 1] != 'X' || (box[c][x[0] - 1] == 'X' && box[c - 2][x[0]] != ' ')))
            {
                count++;
            }
            if ((c == 6 || c == 4 || c == 2) && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c - 1][x[0]] == ' ')
            {
                count++;
            }

            // upwards rightwards - odd
            if ((c == 1 || c == 5 || c == 3) && x[0] != 3 && box[c][x[0]] == 'O' && box[c + 1][x[0]] == ' ' && box[c + 2][x[0] + 1] != 'x' && box[c + 2][x[0] + 1] != 'X' &&
                ((box[c][x[0] + 1] != 'x' && box[c][x[0] + 1] != 'X') || ((box[c][x[0] + 1] == 'x' || box[c][x[0] + 1] == 'X') && box[c + 2][x[0]] != ' ')) &&
                (box[c + 2][x[0]] != 'X' || (box[c + 2][x[0]] == 'X' && box[c][x[0] + 1] != ' ')))
            {
                count++;
            }
            if ((c == 1 || c == 5 || c == 3) && x[0] == 3 && (box[c][x[0]] == 'O' || box[c][x[0]] == 'o') && box[c + 1][x[0]] == ' ')
            {
                count++;
            }

            // upwards leftwards - odd
            if ((c == 1 || c == 5 || c == 3) && x[0] != 0 && box[c][x[0]] == 'O' && box[c + 1][x[0] - 1] == ' ' && box[c + 2][x[0] - 1] != 'x' && box[c + 2][x[0] - 1] != 'X' &&
                ((box[c][x[0] - 1] != 'x' && box[c][x[0] - 1] != 'X') || ((box[c][x[0] - 1] == 'x' || box[c][x[0] - 1] == 'X') && box[c + 2][x[0]] != ' ')) &&
                (box[c + 2][x[0]] != 'X' || (box[c + 2][x[0]] == 'X' && box[c][x[0] - 1] != ' ')))
            {
                count++;
            }

            // upwards rightwards - even
            if ((c == 0 || c == 4 || c == 2) && x[0] != 3 && box[c][x[0]] == 'O' && box[c + 1][x[0] + 1] == ' ' && box[c + 2][x[0] + 1] != 'x' && box[c + 2][x[0] + 1] != 'X' &&
                ((box[c][x[0] + 1] != 'x' && box[c][x[0] + 1] != 'X') || ((box[c][x[0] + 1] == 'x' || box[c][x[0] + 1] == 'X') && box[c + 2][x[0]] != ' ')) &&
                (box[c + 2][x[0]] != 'X' || (box[c + 2][x[0]] == 'X' && box[c][x[0] + 1] != ' ')))
            {
                count++;
            }
            if (c == 6 && x[0] != 3 && box[c][x[0]] == 'O' && box[c + 1][x[0] + 1] == ' ')
            {
                count++;
            }

            // upwards leftwards - even
            if ((c == 0 || c == 4 || c == 2) && x[0] != 0 && box[c][x[0]] == 'O' && box[c + 1][x[0]] == ' ' && box[c + 2][x[0] - 1] != 'x' && box[c + 2][x[0] - 1] != 'X' &&
                ((box[c][x[0] - 1] != 'x' && box[c][x[0] - 1] != 'X') || ((box[c][x[0] - 1] == 'x' || box[c][x[0] - 1] == 'X') && box[c + 2][x[0]] != ' ')) &&
                (box[c + 2][x[0]] != 'X' || (box[c + 2][x[0]] == 'X' && box[c][x[0] - 1] != ' ')))
            {
                count++;
            }
            if ((c == 0 || c == 4 || c == 2) && x == 0 && box[c][x[0]] == 'O' && box[c + 1][x[0]] == ' ')
            {
                count++;
            }
            if (c == 0 && box[c][x[0]] == 'O' && box[c + 1][x[0]] == ' ')
            {
                count++;
            }
        }
    }

    return count;
}

void column_select()
{
    auto count = direct_unknock_moves();
    auto temp_play_mode{play_mode};

    if (count == 0)
        temp_play_mode = 1;

    bool chosen{false};

    while (!chosen)
    {
        x[0] = rand() % 4;

        if (temp_play_mode == 1)
        {
            choice[0] = rand() % 8;
            short int count{};

            do
            {
                // downwards rightwards - odd
                if (choice[0] == 7 && (y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }

                // downwards leftwards - odd
                if (choice[0] == 6 && (y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0] - 1;
                    break;
                }

                // downwards rightwards - even
                if (choice[0] == 5 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0] + 1;
                    break;
                }

                // downwards leftwards - even
                if (choice[0] == 4 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }

                // upwards rightwards - odd
                if (choice[0] == 3 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }

                // upwards leftwards - odd
                if (choice[0] == 2 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0] - 1;
                    break;
                }

                // upwards rightwards - even
                if (choice[0] == 2 && (y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0] + 1;
                    break;
                }

                // upwards leftwards - even
                if (choice[0] == 0 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }

                count++;
                choice[0]++;
                if (choice[0] == 8)
                    choice[0] = 0;

            } while (count <= 8);
        }
        else if (temp_play_mode == 2 || temp_play_mode == 3)
        {
            choice[0] = rand() % 16;
            short int count{};

            do
            {
                // downwards rightwards - odd
                if (choice[0] == 15 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                    (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 14 && y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 13 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }

                // downwards leftwards - odd
                if (choice[0] == 12 && (y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                    (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0] - 1;
                    break;
                }
                if (choice[0] == 11 && y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0] - 1;
                    break;
                }

                // downwards rightwards - even
                if (choice[0] == 10 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                    (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0] + 1;
                    break;
                }

                // downwards leftwards - even
                if (choice[0] == 9 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                    (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 8 && (y[0] == 6 || y[0] == 4 || y[0] == 2) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] - 1;
                    x[1] = x[0];
                    break;
                }

                // upwards rightwards - odd
                if (choice[0] == 7 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                    ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 6 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] + 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }

                // upwards leftwards - odd
                if (choice[0] == 5 && (y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                    ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0] - 1;
                    break;
                }

                // upwards rightwards - even
                if (choice[0] == 4 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                    ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0] + 1;
                    break;
                }
                if (choice[0] == 3 && y[0] == 6 && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0] + 1;
                    break;
                }

                // upwards leftwards - even
                if (choice[0] == 2 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                    ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 1 && (y[0] == 0 || y[0] == 4 || y[0] == 2) && x == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }
                if (choice[0] == 0 && y[0] == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    chosen = true;
                    y[1] = y[0] + 1;
                    x[1] = x[0];
                    break;
                }

                count++;
                choice[0]++;
                if (choice[0] == 16)
                    choice[0] = 0;

            } while (count <= 16);
        }
    }
}

void movePiece_comp(char knock)
{
    // moving up without knock

    if (y[0] + 1 == y[1] && knock == 'N' && box[y[0]][x[0]] == 'O')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
    }

    // moving down without knock

    else if (y[0] - 1 == y[1] && knock == 'N')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0]][x[0]] = '.';
        }
    }

    // moving up with knock

    else if (y[0] + 2 == y[1] && box[y[0]][x[0]] == 'O' && knock == 'Y')
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'x' || box[y[0] + 1][x[0] - 1] == 'X') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'x' || box[y[0] + 1][x[0] + 1] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
        }
    }

    // moving down with knock

    else if (y[0] - 2 == y[1] && knock == 'Y')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'x' || box[y[0] - 1][x[0] - 1] == 'X') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'x' || box[y[0] - 1][x[0]] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'x' || box[y[0] - 1][x[0]] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'x' || box[y[0] - 1][x[0] + 1] == 'X') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            if (box[y[0]][x[0]] == 'O')
            {
                box[y[1]][x[1]] = 'O';
            }
            else
            {
                box[y[1]][x[1]] = 'o';
            }
            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
        }
    }

    // king
    for (size_t i = 0; i < 4; i++)
    {
        if (box[0][i] == 'o')
        {
            box[0][i] = 'O';
        }
    }
}

bool future_Knock_byPlayer()
{
    bool future_knock{false};

    temp_y[18] = y[0];
    temp_x[18] = x[0];
    temp_y[19] = y[1];
    temp_x[19] = x[1];

    for (int c = 0; c < 8; c++)
    {
        for (int d = 0; d < 4; d++)
        {
            temp_box1[c][d] = box[c][d];
        }
    }

    // moving up without knock

    if (temp_y[18] + 1 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'O')
    {
        if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] != 3 &&
            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && (temp_x[18] == temp_x[19] || temp_x[18] + 1 == temp_x[19]))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] == 3 && temp_x[18] == temp_x[19] &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && (temp_x[18] == temp_x[19] || temp_x[18] - 1 == temp_x[19]))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] == 0 && temp_x[18] == temp_x[19] &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
    }

    // moving down without knock

    else if (temp_y[18] - 1 == temp_y[19])
    {
        if ((temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] != 3 && (temp_x[18] == temp_x[19] || temp_x[18] + 1 == temp_x[19]) &&
            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] == 3 && temp_x[18] == temp_x[19] &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5 || temp_y[18] == 7) && temp_x[18] != 0 && (temp_x[18] == temp_x[19] || temp_x[18] - 1 == temp_x[19]) &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5 || temp_y[18] == 7) && temp_x[18] == 0 && temp_x[18] == temp_x[19] &&
                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.'))
        {
            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'O';
            }
            else
            {
                temp_box1[temp_y[19]][temp_x[19]] = 'o';
            }
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
    }

    // saving current board

    for (short int k = 0; k < 8; k++)
    {
        for (short int l = 0; l < 4; l++)
        {
            temp_box2[k][l] = temp_box1[k][l];
        }
    }

    // checking for future player knock

    for (size_t q = 0; q <= 7; q++)
    {
        for (size_t r = 0; r < 4; r++)
        {
            // checking upwards

            if ((q == 0 || q == 2 || q == 4) && r != 3 && (temp_box1[q + 1][r + 1] == 'o' || temp_box1[q + 1][r + 1] == 'O') &&
                (temp_box1[q + 2][r + 1] == ' ' || temp_box1[q + 2][r + 1] == '.') && (temp_box1[q][r] == 'x' || temp_box1[q][r] == 'X'))
            {
                future_knock = true;
            }
            if ((q == 0 || q == 2 || q == 4) && r != 0 && (temp_box1[q + 1][r] == 'o' || temp_box1[q + 1][r] == 'O') &&
                (temp_box1[q + 2][r - 1] == ' ' || temp_box1[q + 2][r - 1] == '.') && (temp_box1[q][r] == 'x' || temp_box1[q][r] == 'X'))
            {
                future_knock = true;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 3 && (temp_box1[q + 1][r] == 'o' || temp_box1[q + 1][r] == 'O') &&
                (temp_box1[q + 2][r + 1] == ' ' || temp_box1[q + 2][r + 1] == '.') && (temp_box1[q][r] == 'x' || temp_box1[q][r] == 'X'))
            {
                future_knock = true;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 0 && (temp_box1[q + 1][r - 1] == 'o' || temp_box1[q + 1][r - 1] == 'O') &&
                (temp_box1[q + 2][r - 1] == ' ' || temp_box1[q + 2][r - 1] == '.') && (temp_box1[q][r] == 'x' || temp_box1[q][r] == 'X'))
            {
                future_knock = true;
            }

            // checking downwards

            if ((q == 6 || q == 2 || q == 4) && r != 3 && (temp_box1[q - 1][r + 1] == 'o' || temp_box1[q - 1][r + 1] == 'O') &&
                (temp_box1[q - 2][r + 1] == ' ' || temp_box1[q - 2][r + 1] == '.') && temp_box1[q][r] == 'X')
            {
                future_knock = true;
            }
            if ((q == 6 || q == 2 || q == 4) && r != 0 && (temp_box1[q - 1][r] == 'o' || temp_box1[q - 1][r] == 'O') &&
                (temp_box1[q - 2][r - 1] == ' ' || temp_box1[q - 2][r - 1] == '.') && temp_box1[q][r] == 'X')
            {
                future_knock = true;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 3 && (temp_box1[q - 1][r] == 'o' || temp_box1[q - 1][r] == 'O') &&
                (temp_box1[q - 2][r + 1] == ' ' || temp_box1[q - 2][r + 1] == '.') && temp_box1[q][r] == 'X')
            {
                future_knock = true;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 0 && (temp_box1[q - 1][r - 1] == 'o' || temp_box1[q - 1][r - 1] == 'O') &&
                (temp_box1[q - 2][r - 1] == ' ' || temp_box1[q - 2][r - 1] == '.') && temp_box1[q][r] == 'X')
            {
                future_knock = true;
            }
        }
    }

    return future_knock;
}

int future_maxKnocks_comp()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {

        int total_knocks{};

        for (size_t m{}; m < 8; m++)
        {
            for (size_t n{}; n < 4; n++)
            {
                temp_box1[m][n] = box[m][n];
            }
        }

        temp_y[18] = y[0];
        temp_x[18] = x[0];

        const unsigned short int initial_Y = y[0];
        const unsigned short int initial_X = x[0];

        for (temp_y[19] = 0; temp_y[19] < 8; temp_y[19]++)
        {
            const unsigned short int temp_y19 = temp_y[19];

            for (temp_x[19] = 0; temp_x[19] < 4; temp_x[19]++)
            {
                const unsigned short int temp_x19 = temp_x[19];

                bool knock_present{false};
                bool proceed{false};

                do
                {
                    // std::cout << ".";
                    // moving up with knock
                    if (temp_y[18] + 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'O')
                    {
                        if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                            temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        }
                    }
                    // moving down with knock
                    else if (temp_y[18] - 2 == temp_y[19])
                    {
                        if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                            (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                                 (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            proceed = true;
                            if (temp_box1[temp_y[18]][temp_x[18]] == 'O')
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'O';
                            }
                            else
                            {
                                temp_box1[temp_y[19]][temp_x[19]] = 'o';
                            }
                            temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                            temp_box1[temp_y[18]][temp_x[18]] = '.';
                        }
                    }

                    if (proceed)
                    {
                        total_knocks++;

                        temp_y[18] = temp_y[19];
                        temp_x[18] = temp_x[19];

                        if (total_knocks > max_knocks)
                        {
                            max_knocks = total_knocks;

                            for (size_t m{}; m < 8; m++)
                            {
                                for (size_t n{}; n < 4; n++)
                                {
                                    temp_box2[m][n] = temp_box1[m][n];
                                }
                            }
                        }
                        // king
                        for (size_t i = 0; i < 4; i++)
                        {
                            if (temp_box1[0][i] == 'o')
                            {
                                temp_box1[0][i] = 'O';
                                temp_box2[0][i] = 'O';
                            }
                        }

                        knock_present = future_more_knocks();
                    }

                } while (knock_present);

                total_knocks = 0;

                temp_y[18] = initial_Y;
                temp_x[18] = initial_X;

                for (size_t m{}; m < 8; m++)
                {
                    for (size_t n{}; n < 4; n++)
                    {
                        temp_box1[m][n] = box[m][n];
                    }
                }

                temp_x[19] = temp_x19;
            }

            temp_y[19] = temp_y19;
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

    if (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // downwards

            if (choice[0] == 0 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            // upwards

            if (choice[0] == 4 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'O')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
                choice[0] = 0;
        }
    }

    else if (temp_box1[temp_y[18]][temp_x[18]] == 'X' || temp_box1[temp_y[18]][temp_x[18]] == 'x')
    {
        unsigned short int count{};

        while (count < 8)
        {
            // upwards

            if (choice[0] == 0 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.') && (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X'))
            {
                knock_present = true;
                temp_y[19] = temp_y[18] + 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }

            // downwards

            if (choice[0] == 4 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] - 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.') && temp_box1[temp_y[18]][temp_x[18]] == 'X')
            {
                knock_present = true;
                temp_y[19] = temp_y[18] - 2;
                temp_x[19] = temp_x[18] + 1;
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

int future_maxKnocks_player()
{
    int max_knocks{};

    for (short int re_do = 0; re_do < 51; re_do++)
    {
        for (temp_y[18] = 0; temp_y[18] < 8; temp_y[18]++)
        {
            for (temp_x[18] = 0; temp_x[18] < 4; temp_x[18]++)
            {
                for (size_t m{}; m < 8; m++)
                {
                    for (size_t n{}; n < 4; n++)
                    {
                        temp_box1[m][n] = temp_box2[m][n];
                    }
                }

                if (temp_box1[temp_y[18]][temp_x[18]] == 'x' || temp_box1[temp_y[18]][temp_x[18]] == 'X')
                {
                    const unsigned short int initial_Y = temp_y[18];
                    const unsigned short int initial_X = temp_x[18];

                    int total_knocks{};

                    for (temp_y[19] = 0; temp_y[19] < 8; temp_y[19]++)
                    {
                        const unsigned short int temp_y19 = temp_y[19];

                        for (temp_x[19] = 0; temp_x[19] < 4; temp_x[19]++)
                        {
                            const unsigned short int temp_x19 = temp_x[19];

                            bool knock_present{false};
                            bool proceed{false};

                            do
                            {
                                // moving up with knock

                                if (temp_y[18] + 2 == temp_y[19])
                                {
                                    if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                                    }
                                    else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;

                                        if (temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        }
                                        else
                                        {
                                            temp_box1[temp_y[19]][temp_x[19]] = 'x';
                                        }
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                        temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                                    }
                                }

                                // moving down with knock

                                else if (temp_y[18] - 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'X')
                                {
                                    if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                                        (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18] - 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18]] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                    else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                                             (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                                    {
                                        proceed = true;
                                        temp_box1[temp_y[19]][temp_x[19]] = 'X';
                                        temp_box1[temp_y[18] - 1][temp_x[18] + 1] = '.';
                                        temp_box1[temp_y[18]][temp_x[18]] = '.';
                                    }
                                }

                                if (proceed)
                                {
                                    total_knocks++;
                                    max_knocks = (total_knocks > max_knocks) ? total_knocks : max_knocks;

                                    temp_y[18] = temp_y[19];
                                    temp_x[18] = temp_x[19];

                                    // king
                                    for (size_t i = 0; i < 4; i++)
                                    {
                                        if (temp_box1[7][i] == 'x')
                                        {
                                            temp_box1[7][i] = 'X';
                                        }
                                    }

                                    knock_present = future_more_knocks();
                                }

                            } while (knock_present);

                            total_knocks = 0;

                            temp_y[18] = initial_Y;
                            temp_x[18] = initial_X;

                            for (size_t m{}; m < 8; m++)
                            {
                                for (size_t n{}; n < 4; n++)
                                {
                                    temp_box1[m][n] = temp_box2[m][n];
                                }
                            }

                            temp_x[19] = temp_x19;
                        }

                        temp_y[19] = temp_y19;
                    }
                }
            }
        }
    }

    return max_knocks;
}

int totalMoves_comp()
{
    int count{};

    for (size_t u = 0; u < 8; u++)
    {
        for (size_t v{}; v < 4; v++)
        {
            // downwards rightwards - odd
            if ((u == 7 || u == 5 || u == 3 || u == 1) && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v] == ' ')
            {
                count++;
            }

            // downwards leftwards - odd
            if ((u == 7 || u == 5 || u == 3 || u == 1) && v != 0 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v - 1] == ' ')
            {
                count++;
            }

            // downwards rightwards - even
            if ((u == 6 || u == 4 || u == 2) && v != 3 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v + 1] == ' ')
            {
                count++;
            }

            // downwards leftwards - even
            if ((u == 6 || u == 4 || u == 2) && v != 0 && (box[u][v] == 'O' || box[u][v] == 'o') && box[u - 1][v] == ' ')
            {
                count++;
            }

            // upwards rightwards - odd
            if ((u == 1 || u == 5 || u == 3) && box[u][v] == 'O' && box[u + 1][v] == ' ')
            {
                count++;
            }

            // upwards leftwards - odd
            if ((u == 1 || u == 5 || u == 3) && v != 0 && box[u][v] == 'O' && box[u + 1][v - 1] == ' ')
            {
                count++;
            }

            // upwards rightwards - even
            if ((u == 0 || u == 4 || u == 2 || u == 6) && v != 3 && box[u][v] == 'O' && box[u + 1][v + 1] == ' ')
            {
                count++;
            }

            // upwards leftwards - even
            if ((u == 0 || u == 4 || u == 2) && box[u][v] == 'O' && box[u + 1][v] == ' ')
            {
                count++;
            }
        }
    }

    return count;
}