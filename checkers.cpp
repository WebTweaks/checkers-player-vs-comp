#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

char box[8][4]{};
short int play_mode{};
const short int max_length{20};
char player_name[max_length]{};
unsigned short int choice[3]{};
unsigned short int y[10];
unsigned short int temp_y[10];
unsigned short int x[10];
unsigned short int temp_x[10];

void reset_board();
void print_board();

void player();
bool choice_processing(int index);
bool select_piece();
bool move_piece();
bool more_knocks();

void computer();
char knocks(int *total);

int main()
{
    int align{100};
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

    reset_board();
    player();

    return 0;
}

void reset_board()
{
    for (size_t row{}; row < 8; row++)
    {
        for (size_t column{}; column < 4; column++)
        {
            box[row][column] = ' ';
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

    box[2][1] = 'o';
    box[2][2] = 'o';
    box[2][0] = 'o';
    box[4][1] = 'o';
    box[4][2] = 'o';
    box[4][0] = 'o';
    box[1][2] = 'x';
    box[1][1] = 'X';
    box[6][1] = 'O';
    box[6][2] = 'O';
    box[6][0] = 'O';
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
    std::cout << std::left;
    std::cout << "        ========================================" << std::endl;
    std::cout << "                       YOUR TURN" << std::endl;
    std::cout << "        ========================================" << std::endl;
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

        not_played = move_piece();
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

            not_played = move_piece();
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

bool move_piece()
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

    if (box[y[1]][x[1]] == 'x' || box[y[1]][x[1]] == 'X')
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
    if (box[y[1]][x[1]] == 'o' || box[y[1]][x[1]] == 'O')
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
    std::cout << std::left;
    std::cout << "        ========================================" << std::endl;
    std::cout << "                      COMP'S TURN" << std::endl;
    std::cout << "        ========================================" << std::endl;

    srand(time(0));
    int total_knocks{};
    char knock_present = knocks(&total_knocks);

    if ((play_mode == 1 || play_mode == 2) && knock_present == 'Y')
    {
        unsigned short int rand_num = rand() % 2;
        if (rand_num == 1 && play_mode == 1)
        {
            knock_present = 'N';
        }

        rand_num = rand() % 4;
        if (rand_num == 2 && play_mode == 3)
        {
            knock_present = 'N';
        }
    }

    if (knock_present == 'Y')
    {
        if (total_knocks > 1)
        {
        }
    }
}

char knocks(int *total)
{
    char knock{};
    int count{};

    for (int a = 0; a <= 7; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            // checking upwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (box[a + 1][b + 1] == 'x' || box[a + 1][b + 1] == 'X') &&
                (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && box[a][b] == 'O')
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (box[a + 1][b] == 'x' || box[a + 1][b] == 'X') &&
                (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && box[a][b] == 'O')
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (box[a + 1][b] == 'x' || box[a + 1][b] == 'X') &&
                (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && box[a][b] == 'O')
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (box[a + 1][b - 1] == 'x' || box[a + 1][b - 1] == 'X') &&
                (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && box[a][b] == 'O')
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            // checking downwards
            if ((a == 6 || a == 2 || a == 4) && b != 3 && (box[a - 1][b + 1] == 'x' || box[a - 1][b + 1] == 'X') &&
                (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && (box[a][b] == 'o' || box[a][b] == 'O'))
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (box[a - 1][b] == 'x' || box[a - 1][b] == 'X') &&
                (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && (box[a][b] == 'o' || box[a][b] == 'O'))
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (box[a - 1][b] == 'x' || box[a - 1][b] == 'X') &&
                (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && (box[a][b] == 'o' || box[a][b] == 'O'))
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (box[a - 1][b - 1] == 'x' || box[a - 1][b - 1] == 'X') &&
                (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && (box[a][b] == 'o' || box[a][b] == 'O'))
            {
                count++;
                y[count - 1] = a;
                x[count - 1] = b;
            }
        }
    }

    *total = count;

    if (*total > 0)
        knock = 'Y';
    else
        knock = 'N';

    return knock;
}
