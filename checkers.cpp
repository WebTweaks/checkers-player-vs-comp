#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>

char box[8][4]{};
char temp_box1[8][4]{};
char temp_box2[8][4]{};

const unsigned short int max_length{20};
char player_name[max_length]{};

unsigned short int play_mode{};
unsigned short int choice[3]{};
unsigned short int y[2];
unsigned short int x[2];
bool moved_by_knock{false};
unsigned short int temp_y[20]{};
unsigned short int temp_x[20]{};
unsigned short int y1_store[20]{};
unsigned short int x1_store[20]{};

void reset_board();
void print_board();

void player();
bool choice_processing(int index);
bool selectPiece_player();
bool auto_playerMove();
bool movePiece_player();
bool more_knocks();

void computer();
bool knocks_checking(int *total_knocks);
unsigned short int totalMoves_comp();
unsigned short int total_unknockMoves();
void selectPiece_comp();
void movePiece_comp(char knock);
bool future_knock_byPlayer();
int future_maxKnocks_comp();
bool future_more_knocks();
int future_maxKnocks_player();

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

    for (short int i{}; i < std::size(temp_name); ++i)
    {
        if (temp_name[i] == ' ')
        {
            break;
        }
        temp_name[i] = std::toupper(temp_name[i]);
        player_name[i] = temp_name[i];
    }*/

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
    for (short int i = 0; i < 1000000; i++)
    {
        player();
        computer();
    }

    std::cout << "        PROGRAM ENDS WELL" << std::endl;
    return 0;
}

void reset_board()
{
    for (short int row{}; row < 8; row++)
    {
        for (short int column{}; column < 4; column++)
        {
            box[row][column] = ' ';
            temp_box1[row][column] = ' ';
            temp_box2[row][column] = ' ';
        }
    }

    // players pieces
    for (short int row{}; row < 3; row++)
    {
        for (short int column{}; column < 4; column++)
        {
            box[row][column] = 'x';
        }
    }

    // comp pieces
    for (short int row{5}; row <= 7; row++)
    {
        for (short int column{}; column < 4; column++)
        {
            box[row][column] = 'o';
        }
    }
    /*box[0][3] = 'O';
    box[7][3] = 'o';
    box[1][1] = 'x';
    box[1][2] = 'x';
    box[1][3] = 'x';
    box[3][1] = 'x';
    box[3][2] = 'x';
    box[3][3] = 'x';
    box[5][1] = 'x';
    box[5][2] = 'x';
    box[5][3] = 'x';*/
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
    for (short int i = 0; i < 8; i++)
    {
        for (short int j = 0; j < 4; j++)
        {
            if (box[i][j] == '.')
            {
                box[i][j] = ' ';
            }
        }
    }

    bool moved{false};
    bool knock_available{false};
    bool selected{false};
    bool invalid_input{false};
    moved_by_knock = false;

    do
    {
        do
        {
            std::cout << "        Enter piece row# column# e.g 12: ";

            if (!(std::cin >> choice[0]))
            {
                std::cout << "        Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                print_board();
            }
            else
            {
                invalid_input = choice_processing(0);
                if (invalid_input)
                {
                    std::cout << "        Invalid input! Try again!" << std::endl;
                    print_board();
                }
            }

        } while (invalid_input);

        selected = selectPiece_player();
        if (!selected)
        {
            print_board();
            std::cout << "        Invalid piece entry! Try again!" << std::endl;
        }

    } while (!selected);

    std::cout << "        -----------------------------------------" << std::endl;
    std::cout << "          SELECTED " << player_name << std::endl;
    std::cout << "        -----------------------------------------" << std::endl;
    print_board();

    do
    {
        do
        {
            std::cout << "        Enter target row# column# e.g 23: ";

            if (!(std::cin >> choice[1]))
            {
                std::cout << "        Invalid input! Try again!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                print_board();
            }
            else
            {
                invalid_input = choice_processing(1);
                if (invalid_input)
                {
                    std::cout << "        Invalid input! Try again!" << std::endl;
                    print_board();
                }
            }

        } while (invalid_input);

        moved = movePiece_player();

    } while (!moved);

    while ((knock_available = more_knocks()) && moved_by_knock)
    {
        if (box[y[1]][x[1]] == 'X')
        {
            box[y[1]][x[1]] = 'S';
        }
        else if (box[y[1]][x[1]] == 'x')
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

                if (!(std::cin >> choice[1]))
                {
                    std::cout << "        Invalid input! Try again!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    print_board();
                }

                else
                {
                    invalid_input = choice_processing(1);
                    if (invalid_input)
                    {
                        std::cout << "        Invalid input! Try again!" << std::endl;
                        print_board();
                    }
                }

            } while (invalid_input);

            moved = movePiece_player();

        } while (!moved);
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

bool selectPiece_player()
{
    bool selected{false};

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

            selected = true;
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

            selected = true;
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

            selected = true;
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

            selected = true;
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

            selected = true;
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

            selected = true;
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

            selected = true;
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

            selected = true;
        }
    }
    if (box[y[0]][x[0]] == 'X' && !selected)
    {
        // moving down without knock
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == ' ' || box[y[0] - 1][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && (box[y[0] - 1][x[0]] == ' ' || box[y[0] - 1][x[0]] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == ' ' || box[y[0] - 1][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }

        // moving down with knock
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[0] - 2][x[0] + 1] == ' ' || box[y[0] - 2][x[0] + 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
                 (box[y[0] - 2][x[0] - 1] == ' ' || box[y[0] - 2][x[0] - 1] == '.'))
        {
            box[y[0]][x[0]] = 'S';
            selected = true;
        }
    }

    return selected;
}

bool auto_playerMove()
{
    bool target_selected{false};

    // checking available moves
}

bool movePiece_player()
{
    bool moved{false};

    // moving up without knock
    if (y[0] + 1 == y[1] && (box[y[0]][x[0]] == 'S' || box[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] - 1 == x[1]))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            moved = true;
        }
    }

    // moving down without knock
    else if (y[0] - 1 == y[1] && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
    }

    // moving up with knock
    else if (y[0] + 2 == y[1] && (box[y[0]][x[0]] == 'S' || box[y[0]][x[0]] == 's'))
    {
        if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] + 1][x[0] - 1] == 'o' || box[y[0] + 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
            moved = true;
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {

            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }

    // moving down with knock
    else if (y[0] - 2 == y[1] && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
            moved = true;
        }

        moved_by_knock = true;
    }

    // king
    for (short int column = 0; column < 4; column++)
    {
        if (box[7][column] == 'x')
        {
            box[7][column] = 'X';
        }
    }

    return moved;
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
    std::cout << "\n        Thinking...";

    char temp_box3[8][4]{};

    // removing '.'
    for (short int f{}; f < 8; f++)
    {
        for (short int g{}; g < 4; g++)
        {
            if (box[f][g] == '.')
            {
                box[f][g] = ' ';
            }
        }
    }

    int total_knocks{};
    short int rand_num{};
    bool selected{false};
    bool moved{false};

    bool knock_present = knocks_checking(&total_knocks);

    if (play_mode == 1)
    {
        rand_num = rand() % 4;
        auto total_moves = totalMoves_comp();

        if (total_moves == 0 && knock_present)
        {
            rand_num = 2;
        }

        if (rand_num == 2 && knock_present)
        {
            knocks_checking(&total_knocks);
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
            y[1] = y1_store[rand_num];
            x[1] = x1_store[rand_num];

            movePiece_comp('Y');

            while (knock_present = knocks_checking(&total_knocks))
            {
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                movePiece_comp('Y');
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
        rand_num = rand() % 10;

        auto unknock_moves = total_unknockMoves();
        if (unknock_moves == 0 && knock_present)
        {
            rand_num = 2;
        }

        if (rand_num != 4 && knock_present)
        {
            knocks_checking(&total_knocks);
            rand_num = rand() % 1;

            if (rand_num != 0)
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

                        if (total_comp_knocks > max_knocks && total_player_knocks <= total_comp_knocks)
                        {
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
            else if (rand_num == 0)
            {
                rand_num = rand() % total_knocks;

                y[0] = temp_y[rand_num];
                x[0] = temp_x[rand_num];
                y[1] = y1_store[rand_num];
                x[1] = x1_store[rand_num];

                movePiece_comp('Y');

                while (knock_present = knocks_checking(&total_knocks))
                {
                    rand_num = rand() % total_knocks;

                    y[0] = temp_y[rand_num];
                    x[0] = temp_x[rand_num];
                    y[1] = y1_store[rand_num];
                    x[1] = x1_store[rand_num];

                    movePiece_comp('Y');
                }
                moved = true;
            }
        }

        if (!moved)
        {
            do
            {
                for (short int re_do = 0; re_do < 11; re_do++)
                {
                    selectPiece_comp();
                    bool future_knock = future_knock_byPlayer();

                    if (!future_knock)
                    {
                        for (short int c = 0; c < 8; c++)
                        {
                            for (short int d = 0; d < 4; d++)
                            {
                                box[c][d] = temp_box1[c][d];
                            }
                        }

                        moved = true;
                    }

                    if (moved)
                        break;
                    else if (!moved && re_do == 10)
                    {
                        selectPiece_comp();
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

    for (short int q = 0; q <= 7; q++)
    {
        for (short int r = 0; r < 4; r++)
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
                x1_store[*total_knocks] = r - 1; // *x1_store[*total_knocks] = r = 1;*  expensive error I made
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

unsigned short int totalMoves_comp()
{
    int count{};

    for (short int u = 0; u < 8; u++)
    {
        for (short int v{}; v < 4; v++)
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

unsigned short int total_unknockMoves()
{
    unsigned short int count{};

    for (short int a = 0; a < 8; a++)
    {
        for (short int b = 0; b < 4; b++)
        {
            // upwards rightwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && box[a + 1][b + 1] == ' ' && box[a + 2][b + 1] != 'X' &&
                ((box[a][b + 1] != 'x' && box[a][b + 1] != 'X') || ((box[a][b + 1] == 'x' || box[a][b + 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b + 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if (a == 6 && b != 3 && box[a + 1][b + 1] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && box[a + 1][b] == ' ' && box[a + 2][b + 1] != 'X' &&
                ((box[a][b + 1] != 'x' && box[a][b + 1] != 'X') || ((box[a][b + 1] == 'x' || box[a][b + 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b + 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b == 3 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }

            // upwards leftwards
            if ((a == 0 || a == 2 || a == 4) && b != 0 && box[a + 1][b] == ' ' && box[a + 2][b - 1] != 'X' &&
                ((box[a][b - 1] != 'x' && box[a][b - 1] != 'X') || ((box[a][b - 1] == 'x' || box[a][b - 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b - 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if (a == 6 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 0 || a == 2 || a == 4) && b == 0 && box[a + 1][b] == ' ' && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && box[a + 1][b - 1] == ' ' && box[a + 2][b - 1] != 'X' &&
                ((box[a][b - 1] != 'x' && box[a][b - 1] != 'X') || ((box[a][b - 1] == 'x' || box[a][b - 1] == 'X') && box[a + 2][b] != ' ')) &&
                (box[a + 2][b] != 'X' || (box[a + 2][b] == 'X' && box[a][b - 1] != ' ')) && box[a][b] == 'O')
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }

            // downwards rightwards
            if ((a == 7 || a == 5 || a == 3) && b != 3 && box[a - 1][b] == ' ' && box[a - 2][b + 1] != 'X' && box[a - 2][b + 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b + 1] != ' ')) &&
                (box[a][b + 1] != 'X' || (box[a][b + 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 7 || a == 5 || a == 3) && b == 3 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if (a == 1 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b != 3 && box[a - 1][b + 1] == ' ' && box[a - 2][b + 1] != 'X' && box[a - 2][b + 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b + 1] != ' ')) &&
                (box[a][b + 1] != 'X' || (box[a][b + 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }

            // downwards leftwards
            if ((a == 7 || a == 5 || a == 3) && b != 0 && box[a - 1][b - 1] == ' ' && box[a - 2][b - 1] != 'X' && box[a - 2][b - 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b - 1] != ' ')) &&
                (box[a][b - 1] != 'X' || (box[a][b - 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if (a == 1 && b != 0 && box[a - 1][b - 1] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b != 0 && box[a - 1][b] == ' ' && box[a - 2][b - 1] != 'X' && box[a - 2][b - 1] != 'x' &&
                ((box[a - 2][b] != 'x' && box[a - 2][b] != 'X') || ((box[a - 2][b] == 'x' || box[a - 2][b] == 'X') && box[a][b - 1] != ' ')) &&
                (box[a][b - 1] != 'X' || (box[a][b - 1] == 'X' && box[a - 2][b] != ' ')) && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
            if ((a == 6 || a == 4 || a == 2) && b == 0 && box[a - 1][b] == ' ' && (box[a][b] == 'O' || box[a][b] == 'o'))
            {
                temp_y[count] = a;
                temp_x[count] = b;
                count++;
            }
        }
    }

    return count;
}

void selectPiece_comp()
{
    auto temp_play_mode{play_mode};

    if (play_mode == 2 || play_mode == 3)
    {
        auto total_moves{total_unknockMoves()};

        if (total_moves == 0)
            temp_play_mode = 1;

        else if (total_moves > 0)
        {
            auto rand_num{rand() % total_moves};
            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];
        }
    }

    int count{};
    bool selected{false};

    while (!selected && temp_play_mode == 1)
    {
        y[0] = rand() % 8;

        for (short int w = 0; w < 500; w++)
        {
            x[0] = rand() % 4;
            choice[0] = rand() % 8;
            count = 0;

            do
            {
                // moving up without knock
                if (choice[0] == 0 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 1 && (y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 2 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && box[y[0] + 1][x[0]] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }
                else if (choice[0] == 3 && (y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0]][x[0]] == 'O')
                {
                    selected = true;
                }

                // moving down without knock
                else if (choice[0] == 4 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 5 && (y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && box[y[0] - 1][x[0] + 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 6 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && box[y[0] - 1][x[0]] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
                {
                    selected = true;
                }
                else if (choice[0] == 7 && (y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && box[y[0] - 1][x[0] - 1] == ' ' && (box[y[0]][x[0]] == 'o' || box[y[0]][x[0]] == 'O'))
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
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // downwards leftwards - odd
    if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // downwards rightwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // downwards leftwards - even
    if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] - 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards rightwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    // upwards leftwards - odd
    if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] - 1;
        count++;
    }

    // upwards rightwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0] + 1;
        count++;
    }

    // upwards leftwards - even
    if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
    {
        temp_y[count] = y[0] + 1;
        temp_x[count] = x[0];
        count++;
    }

    //  CHOOSING TARGET
    if (count == 1)
    {
        y[1] = temp_y[0];
        x[1] = temp_x[0];
    }
    else if (count == 2)
    {
        short int rand_num = rand() % 2;
        y[1] = temp_y[rand_num];
        x[1] = temp_x[rand_num];
    }
    else if (count == 3)
    {
        short int rand_num = rand() % 3;
        y[1] = temp_y[rand_num];
        x[1] = temp_x[rand_num];
    }
    else if (count == 4)
    {
        short int rand_num = rand() % 4;
        y[1] = temp_y[rand_num];
        x[1] = temp_x[rand_num];
    }
}

void movePiece_comp(char knock)
{
    // moving up without knock

    if (y[0] + 1 == y[1] && knock == 'N' && box[y[0]][x[0]] == 'O')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            box[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 0 && box[y[1]][x[1]] == ' ' && (x[0] == x[1] || x[0] - 1 == x[1]))
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] == 0 && x[0] == x[1] &&
                 box[y[1]][x[1]] == ' ')
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
        }
    }

    // moving down without knock

    else if (y[0] - 1 == y[1] && knock == 'N' && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) && box[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) && box[y[1]][x[1]] == ' ')
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
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] && box[y[1]][x[1]] == ' ')
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
            box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] - 1] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'x' || box[y[0] + 1][x[0]] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'x' || box[y[0] + 1][x[0] + 1] == 'X') &&
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
        {
            box[y[1]][x[1]] = 'O';
            box[y[0]][x[0]] = '.';
            box[y[0] + 1][x[0] + 1] = '.';
        }
    }

    // moving down with knock

    else if (y[0] - 2 == y[1] && knock == 'Y' && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o'))
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'x' || box[y[0] - 1][x[0] - 1] == 'X') &&
            box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
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
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
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
                 box[y[1]][x[1]] == ' ' && x[0] - 1 == x[1])
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
                 box[y[1]][x[1]] == ' ' && x[0] + 1 == x[1])
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
    for (short int i = 0; i < 4; i++)
    {
        if (box[0][i] == 'o')
        {
            box[0][i] = 'O';
        }
    }
}

bool future_knock_byPlayer()
{
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

    // MOVING DOWNWARDS WITHOUT KNOCK
    if (temp_y[18] - 1 == temp_y[19])
    {
        // rightwards - odd
        if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3 || temp_y[18] == 1) && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
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

        // leftwards - odd
        else if ((temp_y[18] == 7 || temp_y[18] == 5 || temp_y[18] == 3 || temp_y[18] == 1) && temp_x[18] != 0 && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] - 1 == temp_x[19])
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

        // rightwards - even
        else if ((temp_y[18] == 6 || temp_y[18] == 4 || temp_y[18] == 2) && temp_x[18] != 3 && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] + 1 == temp_x[19])
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

        // leftwards - even
        else if ((temp_y[18] == 6 || temp_y[18] == 4 || temp_y[18] == 2) && temp_x[18] != 0 && (temp_box1[temp_y[18]][temp_x[18]] == 'O' || temp_box1[temp_y[18]][temp_x[18]] == 'o') && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
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

    // MOVING UPWARDS WITHOUT KNOCK
    else if (temp_y[18] + 1 == temp_y[19])
    {
        // rightwards - odd
        if ((temp_y[18] == 1 || temp_y[18] == 5 || temp_y[18] == 3) && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // checking upwards leftwards - odd
        else if ((temp_y[18] == 1 || temp_y[18] == 5 || temp_y[18] == 3) && temp_x[18] != 0 && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] - 1 == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // rightwards - even
        else if ((temp_y[18] == 0 || temp_y[18] == 4 || temp_y[18] == 2 || temp_y[18] == 6) && temp_x[18] != 3 && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] + 1 == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }

        // leftwards - even
        else if ((temp_y[18] == 0 || temp_y[18] == 4 || temp_y[18] == 2) && temp_box1[temp_y[18]][temp_x[18]] == 'O' && temp_box1[temp_y[19]][temp_x[19]] == ' ' && temp_x[18] == temp_x[19])
        {
            temp_box1[temp_y[19]][temp_x[19]] = 'O';
            temp_box1[temp_y[18]][temp_x[18]] = '.';
        }
    }

    // checking for future player knock

    bool future_knock{false};

    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            // checking upwards
            if ((a == 0 || a == 2 || a == 4) && b != 3 && (temp_box1[a + 1][b + 1] == 'o' || temp_box1[a + 1][b + 1] == 'O') &&
                (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 0 || a == 2 || a == 4) && b != 0 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 3 && (temp_box1[a + 1][b] == 'o' || temp_box1[a + 1][b] == 'O') &&
                (temp_box1[a + 2][b + 1] == ' ' || temp_box1[a + 2][b + 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }
            if ((a == 1 || a == 3 || a == 5) && b != 0 && (temp_box1[a + 1][b - 1] == 'o' || temp_box1[a + 1][b - 1] == 'O') &&
                (temp_box1[a + 2][b - 1] == ' ' || temp_box1[a + 2][b - 1] == '.') && (temp_box1[a][b] == 'x' || temp_box1[a][b] == 'X'))
            {
                future_knock = true;
            }

            // checking downwards
            if ((a == 6 || a == 2 || a == 4) && b != 3 && (temp_box1[a - 1][b + 1] == 'o' || temp_box1[a - 1][b + 1] == 'O') &&
                (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 6 || a == 2 || a == 4) && b != 0 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 3 && (temp_box1[a - 1][b] == 'o' || temp_box1[a - 1][b] == 'O') &&
                (temp_box1[a - 2][b + 1] == ' ' || temp_box1[a - 2][b + 1] == '.') && temp_box1[a][b] == 'X')
            {
                future_knock = true;
            }
            if ((a == 7 || a == 3 || a == 5) && b != 0 && (temp_box1[a - 1][b - 1] == 'o' || temp_box1[a - 1][b - 1] == 'O') &&
                (temp_box1[a - 2][b - 1] == ' ' || temp_box1[a - 2][b - 1] == '.') && temp_box1[a][b] == 'X')
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

        for (short int m{}; m < 8; m++)
        {
            for (short int n{}; n < 4; n++)
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

                            for (short int m{}; m < 8; m++)
                            {
                                for (short int n{}; n < 4; n++)
                                {
                                    temp_box2[m][n] = temp_box1[m][n];
                                }
                            }
                        }
                        // king
                        for (short int i = 0; i < 4; i++)
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

                for (short int m{}; m < 8; m++)
                {
                    for (short int n{}; n < 4; n++)
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
                for (short int m{}; m < 8; m++)
                {
                    for (short int n{}; n < 4; n++)
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
                                    for (short int i = 0; i < 4; i++)
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

                            for (short int m{}; m < 8; m++)
                            {
                                for (short int n{}; n < 4; n++)
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