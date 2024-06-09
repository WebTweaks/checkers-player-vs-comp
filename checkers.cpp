#include <iostream>
#include <ctime>
#include <cstdlib>

char box[8][4]{};
char temp_box1[8][4]{};
char temp_box2[8][4]{};
char temp_box3[8][4]{};
const unsigned short int max_length{20};
char player_name[max_length]{};
short int play_mode{1};
unsigned short int y[2];
unsigned short int x[2];
unsigned short int temp_y[20];
unsigned short int temp_x[20];
unsigned short int choice[3]{};

void reset_board();
void print_board();
void player();
bool choice_processing(int);
bool select_piece();
bool movePiece_player();
bool more_knocks(bool, char);
void computer();
bool knocks(int *, bool);
void movePiece_comp(char);
int unknock_moves();
void row_select();
void column_select();
int virtualMove_comp(char);
int virtualMove_player();
int playerNext_knock();
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
    
    int total_knocks = virtualMove_comp('Y');
    std::cout << "max_knocks: " << total_knocks << std::endl;

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            box[i][j] = temp_box3[i][j];
        }
    }

    print_board();

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
            temp_box3[row][column] = ' ';
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

    box[2][1] = 'x';
    box[2][2] = 'x';
    box[2][0] = 'x';
    box[4][1] = 'x';
    box[4][2] = 'x';
    box[4][0] = 'x';
    box[1][2] = 'O';
    box[1][1] = 'o';
    box[6][1] = 'x';
    box[6][2] = 'x';
    box[6][0] = 'x';

    y[0] = 1;
    y[1] = 3;
    x[0] = 2;
    x[1] = 3;
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

    while (knock_available = more_knocks(false, 'P'))
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

bool more_knocks(bool virtual_game, char player)
{
    bool knock_present{false};

    if (virtual_game == false)
    {
        if ((box[y[1]][x[1]] == 'x' || box[y[1]][x[1]] == 'X') && player == 'P')
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
        if (box[y[1]][x[1]] == 'X' && player == 'P')
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
        if ((box[y[1]][x[1]] == 'o' || box[y[1]][x[1]] == 'O') && player == 'C')
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
        if (box[y[1]][x[1]] == 'O' && player == 'C')
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
    }

    else if (virtual_game)
    {
        if ((temp_box2[temp_y[18]][temp_x[18]] == 'x' || temp_box2[temp_y[18]][temp_x[18]] == 'X') && player == 'P')
        {
            choice[0] = rand() % 4;
            auto temp_num = choice[0];

            do
            {
                if (choice[0] == 0 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box2[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                    (temp_box2[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box2[temp_y[18] + 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_y[18] - 1;
                }
                else if (choice[0] == 1 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box2[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18]] == 'O') &&
                         (temp_box2[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box2[temp_y[18] + 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_y[18] + 1;
                }
                else if (choice[0] == 2 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box2[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18]] == 'O') &&
                         (temp_box2[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box2[temp_y[18] + 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_y[18] - 1;
                }
                else if (choice[0] == 3 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box2[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                         (temp_box2[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box2[temp_y[18] + 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_y[18] + 1;
                }

                choice[0]++;
                if (choice[0] == 4)
                    choice[0] = 0;
                if (choice[0] == temp_num)
                    break;

            } while (true);
        }
        if (temp_box2[temp_y[18]][temp_x[18]] == 'X' && player == 'P' && knock_present == false)
        {
            choice[0] = rand() % 4;
            auto temp_num = choice[0];

            do
            {
                if (choice[0] == 0 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box2[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                    (temp_box2[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box2[temp_y[18] - 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_y[18] - 1;
                }
                else if (choice[0] == 1 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box2[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18]] == 'O') &&
                         (temp_box2[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box2[temp_y[18] - 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_y[18] + 1;
                }
                else if (choice[0] == 2 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box2[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18]] == 'O') &&
                         (temp_box2[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box2[temp_y[18] - 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_y[18] - 1;
                }
                else if (choice[0] == 3 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box2[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                         (temp_box2[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box2[temp_y[18] - 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_y[18] + 1;
                }

                choice[0]++;
                if (choice[0] == 4)
                    choice[0] = 0;
                if (choice[0] == temp_num)
                    break;

            } while (true);
        }

        if ((temp_box1[temp_y[18]][temp_x[18]] == 'o' || temp_box1[temp_y[18]][temp_x[18]] == 'O') && player == 'C')
        {
            choice[0] = rand() % 4;
            //std::cout << "choice[0]: " << choice[0] << std::endl;
            auto temp_num = choice[0];

            do
            {
                if (choice[0] == 0 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                    (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_x[18] - 1;
                }
                else if (choice[0] == 1 && (temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_x[18] + 1;
                }
                else if (choice[0] == 2 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[18] - 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_x[18] - 1;
                }
                else if (choice[0] == 3 && (temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] + 1] == 'X') &&
                         (temp_box1[temp_y[18] - 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] - 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] - 2;
                    temp_x[19] = temp_x[18] + 1;
                }

                choice[0]++;
                if (choice[0] == 4)
                    choice[0] = 0;
                if (choice[0] == temp_num)
                    break;

            } while (true);
        }

        if (temp_box1[temp_y[18]][temp_x[18]] == 'O' && player == 'C' && knock_present == false)
        {
            choice[0] = rand() % 4;
            //std::cout << "choice[0]: " << choice[0] << std::endl;
            auto temp_num = choice[0];

            do
            {
                if (choice[0] == 0 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                    (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_x[18] - 1;
                }
                else if (choice[0] == 1 && (temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_x[18] + 1;
                }
                else if (choice[0] == 2 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[18] + 2][temp_x[18] - 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] - 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_x[18] - 1;
                }
                else if (choice[0] == 3 && (temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                         (temp_box1[temp_y[18] + 2][temp_x[18] + 1] == ' ' || temp_box1[temp_y[18] + 2][temp_x[18] + 1] == '.'))
                {
                    knock_present = true;
                    temp_y[19] = temp_y[18] + 2;
                    temp_x[19] = temp_x[18] + 1;
                }

                choice[0]++;
                if (choice[0] == 4)
                    choice[0] = 0;
                if (choice[0] == temp_num)
                    break;

            } while (true);
        }
    }

    return knock_present;
}

void computer()
{
    std::cout << '\n';
    std::cout << "        =========================================" << std::endl;
    std::cout << "                       COMP'S TURN" << std::endl;
    std::cout << "        ========================================= ";

    // removing '.'
    for (size_t f{}; f < 8; f++)
    {
        for (size_t g{}; g < 4; g++)
        {
            if (box[f][g] == '.')
            {
                box[f][g] = ' ';
            }
        }
    }

    int total_knocks{};
    unsigned short int rand_num{};
    bool knock_present = knocks(&total_knocks, false);

    if (play_mode == 1)
    {
        rand_num = rand() % 3;
        if ((rand_num == 0 || rand_num == 2) && knock_present)
        {
            knock_present = !knock_present;
        }

        if (knock_present)
        {
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];

            temp_y[0] = y[0];
            temp_x[0] = x[0];

            int num{};
            knocks(&num, true);

            y[0] = temp_y[0];
            x[0] = temp_x[0];
            y[1] = temp_y[1];
            x[1] = temp_x[1];

            movePiece_comp('Y');
        }
        else
        {
            row_select();
            column_select();
            movePiece_comp('N');
        }
    }

    else if (play_mode == 2)
    {
        rand_num = rand() % 4;
        if (rand_num == 2 && knock_present)
        {
            knock_present = !knock_present;
        }

        if (knock_present)
        {
            rand_num = rand() % total_knocks;

            y[0] = temp_y[rand_num];
            x[0] = temp_x[rand_num];

            temp_y[0] = y[0];
            temp_x[0] = x[0];

            int num{};
            knocks(&num, true);

            y[0] = temp_y[0];
            x[0] = temp_x[0];
            y[1] = temp_y[1];
            x[1] = temp_x[1];

            movePiece_comp('Y');
        }
        else
        {
            row_select();
            column_select();
            movePiece_comp('N');
        }
    }

    // king
    for (size_t a{}; a < 4; a++)
    {
        if (box[0][a] == 'o')
        {
            box[0][a] = 'O';
        }
    }

    while ((knock_present = more_knocks(false, 'C')))
    {
        temp_y[0] = y[1];
        temp_x[0] = x[1];

        int num{};
        knocks(&num, true);

        y[0] = temp_y[0];
        x[0] = temp_x[0];
        y[1] = temp_y[1];
        x[1] = temp_x[1];

        movePiece_comp('Y');
    }

    std::cout << '\n';
    print_board();
}

bool knocks(int *total, bool to_move)
{
    bool knock_present{false};
    int count{};

    if (to_move == false)
    {
        for (size_t q = 0; q <= 7; q++)
        {
            for (size_t r = 0; r < 4; r++)
            {
                // checking upwards
                if ((q == 0 || q == 2 || q == 4) && r != 3 && (box[q + 1][r + 1] == 'x' || box[q + 1][r + 1] == 'X') &&
                    (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 0 || q == 2 || q == 4) && r != 0 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                    (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 1 || q == 3 || q == 5) && r != 3 && (box[q + 1][r] == 'x' || box[q + 1][r] == 'X') &&
                    (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && box[q][r] == 'O')
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 1 || q == 3 || q == 5) && r != 0 && (box[q + 1][r - 1] == 'x' || box[q + 1][r - 1] == 'X') &&
                    (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && box[q][r] == 'O')
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                // checking downwards
                if ((q == 6 || q == 2 || q == 4) && r != 3 && (box[q - 1][r + 1] == 'x' || box[q - 1][r + 1] == 'X') &&
                    (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 6 || q == 2 || q == 4) && r != 0 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                    (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 7 || q == 3 || q == 5) && r != 3 && (box[q - 1][r] == 'x' || box[q - 1][r] == 'X') &&
                    (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
                if ((q == 7 || q == 3 || q == 5) && r != 0 && (box[q - 1][r - 1] == 'x' || box[q - 1][r - 1] == 'X') &&
                    (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && (box[q][r] == 'o' || box[q][r] == 'O'))
                {
                    temp_y[count] = q;
                    temp_x[count] = r;
                    count++;
                }
            }
        }
    }

    // for choosing destination
    else if (to_move)
    {
        choice[0] = rand() % 8;
        count = 0;

        do
        {
            // checking upwards
            if (choice[0] == 0 && (temp_y[0] == 0 || temp_y[0] == 2 || temp_y[0] == 4) && temp_x[0] != 3 && (box[temp_y[0] + 1][temp_x[0] + 1] == 'x' || box[temp_y[0] + 1][temp_x[0] + 1] == 'X') &&
                (box[temp_y[0] + 2][temp_x[0] + 1] == ' ' || box[temp_y[0] + 2][temp_x[0] + 1] == '.') && box[temp_y[0]][temp_x[0]] == 'O')
            {
                temp_y[1] = temp_y[0] + 2;
                temp_x[1] = temp_x[0] + 1;
                break;
            }
            if (choice[0] == 1 && (temp_y[0] == 0 || temp_y[0] == 2 || temp_y[0] == 4) && temp_x[0] != 0 && (box[temp_y[0] + 1][temp_x[0]] == 'x' || box[temp_y[0] + 1][temp_x[0]] == 'X') &&
                (box[temp_y[0] + 2][temp_x[0] - 1] == ' ' || box[temp_y[0] + 2][temp_x[0] - 1] == '.') && box[temp_y[0]][temp_x[0]] == 'O')
            {
                temp_y[1] = temp_y[0] + 2;
                temp_x[1] = temp_x[0] - 1;
                break;
            }
            if (choice[0] == 2 && (temp_y[0] == 1 || temp_y[0] == 3 || temp_y[0] == 5) && temp_x[0] != 3 && (box[temp_y[0] + 1][temp_x[0]] == 'x' || box[temp_y[0] + 1][temp_x[0]] == 'X') &&
                (box[temp_y[0] + 2][temp_x[0] + 1] == ' ' || box[temp_y[0] + 2][temp_x[0] + 1] == '.') && box[temp_y[0]][temp_x[0]] == 'O')
            {
                temp_y[1] = temp_y[0] + 2;
                temp_x[1] = temp_x[0] + 1;
                break;
            }
            if (choice[0] == 3 && (temp_y[0] == 1 || temp_y[0] == 3 || temp_y[0] == 5) && temp_x[0] != 0 && (box[temp_y[0] + 1][temp_x[0] - 1] == 'x' || box[temp_y[0] + 1][temp_x[0] - 1] == 'X') &&
                (box[temp_y[0] + 2][temp_x[0] - 1] == ' ' || box[temp_y[0] + 2][temp_x[0] - 1] == '.') && box[temp_y[0]][temp_x[0]] == 'O')
            {
                temp_y[1] = temp_y[0] + 2;
                temp_x[1] = temp_x[0] - 1;
                break;
            }

            // checking downwards
            if (choice[0] == 4 && (temp_y[0] == 6 || temp_y[0] == 2 || temp_y[0] == 4) && temp_x[0] != 3 && (box[temp_y[0] - 1][temp_x[0] + 1] == 'x' || box[temp_y[0] - 1][temp_x[0] + 1] == 'X') &&
                (box[temp_y[0] - 2][temp_x[0] + 1] == ' ' || box[temp_y[0] - 2][temp_x[0] + 1] == '.') && (box[temp_y[0]][temp_x[0]] == 'o' || box[temp_y[0]][temp_x[0]] == 'O'))
            {
                temp_y[1] = temp_y[0] - 2;
                temp_x[1] = temp_x[0] + 1;
                break;
            }
            if (choice[0] == 5 && (temp_y[0] == 6 || temp_y[0] == 2 || temp_y[0] == 4) && temp_x[0] != 0 && (box[temp_y[0] - 1][temp_x[0]] == 'x' || box[temp_y[0] - 1][temp_x[0]] == 'X') &&
                (box[temp_y[0] - 2][temp_x[0] - 1] == ' ' || box[temp_y[0] - 2][temp_x[0] - 1] == '.') && (box[temp_y[0]][temp_x[0]] == 'o' || box[temp_y[0]][temp_x[0]] == 'O'))
            {
                temp_y[1] = temp_y[0] - 2;
                temp_x[1] = temp_x[0] - 1;
                break;
            }
            if (choice[0] == 6 && (temp_y[0] == 7 || temp_y[0] == 3 || temp_y[0] == 5) && temp_x[0] != 3 && (box[temp_y[0] - 1][temp_x[0]] == 'x' || box[temp_y[0] - 1][temp_x[0]] == 'X') &&
                (box[temp_y[0] - 2][temp_x[0] + 1] == ' ' || box[temp_y[0] - 2][temp_x[0] + 1] == '.') && (box[temp_y[0]][temp_x[0]] == 'o' || box[temp_y[0]][temp_x[0]] == 'O'))
            {
                temp_y[1] = temp_y[0] - 2;
                temp_x[1] = temp_x[0] + 1;
                break;
            }
            if (choice[0] == 7 && (temp_y[0] == 7 || temp_y[0] == 3 || temp_y[0] == 5) && temp_x[0] != 0 && (box[temp_y[0] - 1][temp_x[0] - 1] == 'x' || box[temp_y[0] - 1][temp_x[0] - 1] == 'X') &&
                (box[temp_y[0] - 2][temp_x[0] - 1] == ' ' || box[temp_y[0] - 2][temp_x[0] - 1] == '.') && (box[temp_y[0]][temp_x[0]] == 'o' || box[temp_y[0]][temp_x[0]] == 'O'))
            {
                temp_y[1] = temp_y[0] - 2;
                temp_x[1] = temp_x[0] - 1;
                break;
            }

            count++;
            choice[0]++;
            if (choice[0] == 8)
            {
                choice[0] = 0;
            }

        } while (count < 8);
    }

    *total = count;

    if (*total > 0)
        knock_present = true;

    return knock_present;
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

void row_select()
{
    char next{'N'};

    auto count = unknock_moves();
    auto temp_play_mode{play_mode};

    if (count == 0)
        temp_play_mode == 1;

    while (next == 'N')
    {
        y[0] = rand() % 8;

        if (temp_play_mode == 1)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                // downwards rightwards - odd
                if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // downwards leftwards - odd
                if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // downwards rightwards - even
                if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // downwards leftwards - even
                if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards rightwards - odd
                if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards leftwards - odd
                if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards rightwards - even
                if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards leftwards - even
                if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }
            }
        }
        else if (temp_play_mode == 2 || temp_play_mode == 3)
        {
            for (x[0] = 0; x[0] < 4; x[0]++)
            {
                // downwards rightwards - odd
                if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                    (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if (y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }
                if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // downwards leftwards - odd
                if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                    (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if (y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // downwards rightwards - even
                if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                    (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    next = 'Y';
                    break;
                }

                // downwards leftwards - even
                if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                    ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                    (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards rightwards - odd
                if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                    ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] + 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards leftwards - odd
                if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                    ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                {
                    next = 'Y';
                    break;
                }

                // upwards rightwards - even
                if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                    ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if (y[0] == 6 && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
                {
                    next = 'Y';
                    break;
                }

                // upwards leftwards - even
                if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                    ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                    (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
                {
                    next = 'Y';
                    break;
                }
                if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }
                if (y[0] == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
                {
                    next = 'Y';
                    break;
                }
            }
        }
    }
}

void column_select()
{
    char next{'N'};

    auto count = unknock_moves();
    auto temp_play_mode{play_mode};

    if (count == 0)
        temp_play_mode == 1;

    while (next == 'N')
    {
        x[0] = rand() % 4;

        if (temp_play_mode == 1)
        {
            // downwards rightwards - odd
            if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }

            // downwards leftwards - odd
            if ((y[0] == 7 || y[0] == 5 || y[0] == 3 || y[0] == 1) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0] - 1;
                break;
            }

            // downwards rightwards - even
            if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0] + 1;
                break;
            }

            // downwards leftwards - even
            if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }

            // upwards rightwards - odd
            if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }

            // upwards leftwards - odd
            if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0] - 1;
                break;
            }

            // upwards rightwards - even
            if ((y[0] == 0 || y[0] == 4 || y[0] == 2 || y[0] == 6) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0] + 1;
                break;
            }

            // upwards leftwards - even
            if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }
        }
        else if (temp_play_mode == 2 || temp_play_mode == 3)
        {
            // downwards rightwards - odd
            if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }
            if (y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }
            if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }

            // downwards leftwards - odd
            if ((y[0] == 7 || y[0] == 5 || y[0] == 3) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0] - 1;
                break;
            }
            if (y[0] == 1 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] - 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0] - 1;
                break;
            }

            // downwards rightwards - even
            if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0] + 1] == ' ' && box[y[0] - 2][x[0] + 1] != 'x' && box[y[0] - 2][x[0] + 1] != 'X' &&
                ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] + 1] != ' ')) &&
                (box[y[0]][x[0] + 1] != 'X' || (box[y[0]][x[0] + 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0] + 1;
                break;
            }

            // downwards leftwards - even
            if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && x[0] != 0 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ' && box[y[0] - 2][x[0] - 1] != 'x' && box[y[0] - 2][x[0] - 1] != 'X' &&
                ((box[y[0] - 2][x[0]] != 'x' && box[y[0] - 2][x[0]] != 'X') || ((box[y[0] - 2][x[0]] == 'x' || box[y[0] - 2][x[0]] == 'X') && box[y[0]][x[0] - 1] != ' ')) &&
                (box[y[0]][x[0] - 1] != 'X' || (box[y[0]][x[0] - 1] == 'X' && box[y[0] - 2][x[0]] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }
            if ((y[0] == 6 || y[0] == 4 || y[0] == 2) && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] - 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] - 1;
                x[1] = x[0];
                break;
            }

            // upwards rightwards - odd
            if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
            {
                next = 'Y';
                break;
            }
            if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] == 3 && (box[y[0]][x[0]] == 'O' || box[y[0]][x[0]] == 'o') && box[y[0] + 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }

            // upwards leftwards - odd
            if ((y[0] == 1 || y[0] == 5 || y[0] == 3) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] - 1] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0] - 1;
                break;
            }

            // upwards rightwards - even
            if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ' && box[y[0] + 2][x[0] + 1] != 'x' && box[y[0] + 2][x[0] + 1] != 'X' &&
                ((box[y[0]][x[0] + 1] != 'x' && box[y[0]][x[0] + 1] != 'X') || ((box[y[0]][x[0] + 1] == 'x' || box[y[0]][x[0] + 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] + 1] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0] + 1;
                break;
            }
            if (y[0] == 6 && x[0] != 3 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0] + 1] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0] + 1;
                break;
            }

            // upwards leftwards - even
            if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x[0] != 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ' && box[y[0] + 2][x[0] - 1] != 'x' && box[y[0] + 2][x[0] - 1] != 'X' &&
                ((box[y[0]][x[0] - 1] != 'x' && box[y[0]][x[0] - 1] != 'X') || ((box[y[0]][x[0] - 1] == 'x' || box[y[0]][x[0] - 1] == 'X') && box[y[0] + 2][x[0]] != ' ')) &&
                (box[y[0] + 2][x[0]] != 'X' || (box[y[0] + 2][x[0]] == 'X' && box[y[0]][x[0] - 1] != ' ')))
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }
            if ((y[0] == 0 || y[0] == 4 || y[0] == 2) && x == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }
            if (y[0] == 0 && box[y[0]][x[0]] == 'O' && box[y[0] + 1][x[0]] == ' ')
            {
                next = 'Y';
                y[1] = y[0] + 1;
                x[1] = x[0];
                break;
            }
        }
    }
}

int unknock_moves()
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

int virtualMove_comp(char knock)
{
    bool knock_present{false};
    int max_knocks{};
    int total_knocks{};

    for (size_t times = 0; times < 1000000; times++)
    {
        for (size_t m{}; m < 8; m++)
        {
            for (size_t n{}; n < 4; n++)
            {
                temp_box1[m][n] = box[m][n];
            }
        }

        temp_y[18] = y[0];
        temp_x[18] = x[0];
        temp_y[19] = y[1];
        temp_x[19] = x[1];

        do
        {
            // moving up without knock
            if (temp_y[18] + 1 == temp_y[19] && knock == 'N' && temp_box1[temp_y[18]][temp_x[18]] == 'O')
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
            else if (temp_y[18] - 1 == temp_y[19] && knock == 'N')
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

            // moving up with knock
            else if (temp_y[18] + 2 == temp_y[19] && temp_box1[temp_y[18]][temp_x[18]] == 'O' && knock == 'Y')
            {
                if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] - 1] == 'X') &&
                    (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18]][temp_x[18]] = '.';
                    temp_box1[temp_y[18] + 1][temp_x[18] - 1] = '.';
                }
                else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18]][temp_x[18]] = '.';
                    temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                }
                else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box1[temp_y[18] + 1][temp_x[18]] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18]] == 'X') &&
                         (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18]][temp_x[18]] = '.';
                    temp_box1[temp_y[18] + 1][temp_x[18]] = '.';
                }
                else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'x' || temp_box1[temp_y[18] + 1][temp_x[18] + 1] == 'X') &&
                         (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                {
                    temp_box1[temp_y[19]][temp_x[19]] = 'O';
                    temp_box1[temp_y[18]][temp_x[18]] = '.';
                    temp_box1[temp_y[18] + 1][temp_x[18] + 1] = '.';
                }
            }

            // moving down with knock
            else if (temp_y[18] - 2 == temp_y[19] && knock == 'Y')
            {
                if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'x' || temp_box1[temp_y[18] - 1][temp_x[18] - 1] == 'X') &&
                    (temp_box1[temp_y[19]][temp_x[19]] == ' ' || temp_box1[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                {
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

            // king
            for (size_t i = 0; i < 4; i++)
            {
                if (temp_box1[0][i] == 'o')
                {
                    temp_box1[0][i] = 'O';
                }
            }

            if (knock == 'Y')
            {
                total_knocks++;

                if (total_knocks > max_knocks)
                {
                    for (size_t g = 0; g < 8; g++)
                    {
                        for (size_t h = 0; h < 4; h++)
                        {
                            temp_box3[g][h] = temp_box1[g][h];
                        }
                    }

                    max_knocks = total_knocks;
                }

                temp_y[18] = temp_y[19];
                temp_x[18] = temp_x[19];
            }

        } while (knock_present = more_knocks(true, 'C'));

        total_knocks = 0;
    }

    return max_knocks;
}

int virtualMove_player()
{
    auto total_moves = playerNext_knock();
    int total_knocks[2]{};
    int max_knocks{};

    if (total_moves > 0)
    {
        auto rand_num = rand() % total_moves;

        int index{};

        while (true)
        {
            auto temp_num = rand_num;

            temp_y[18] = temp_y[rand_num];
            temp_x[18] = temp_x[rand_num];

            for (size_t v = 0; v < 8; v++)
            {
                for (size_t w = 0; w < 4; w++)
                {
                    temp_box2[v][w] = temp_box1[v][w];
                }
            }

            bool knock_present{false};

            for (size_t times = 0; times < 6; times++)
            {
                while ((knock_present = more_knocks(true, 'P')))
                {
                    // moving up without knock
                    if (temp_y[18] + 1 == temp_y[19])
                    {
                        if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] != 3 &&
                            (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && (temp_x[18] == temp_x[19] || temp_x[18] + 1 == temp_x[19]))
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] == 3 && temp_x[18] == temp_x[19] &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && (temp_x[18] == temp_x[19] || temp_x[18] - 1 == temp_x[19]))
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] == 0 && temp_x[18] == temp_x[19] &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                    }

                    // moving down without knock
                    else if (temp_y[18] - 1 == temp_y[19] && temp_box2[temp_y[18]][temp_x[18]] == 'X')
                    {
                        if ((temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] != 3 && (temp_x[18] == temp_x[19] || temp_x[18] + 1 == temp_x[19]) &&
                            (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 2 || temp_y[18] == 4 || temp_y[18] == 6) && temp_x[18] == 3 && temp_x[18] == temp_x[19] &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5 || temp_y[18] == 7) && temp_x[18] != 0 && (temp_x[18] == temp_x[19] || temp_x[18] - 1 == temp_x[19]) &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5 || temp_y[18] == 7) && temp_x[18] == 0 && temp_x[18] == temp_x[19] &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.'))
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                    }

                    // moving up with knock
                    else if (temp_y[18] + 2 == temp_y[19])
                    {
                        if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box2[temp_y[18] + 1][temp_x[18] - 1] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18] - 1] == 'O') &&
                            (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                            temp_box2[temp_y[18] + 1][temp_x[18] - 1] = '.';
                        }
                        else if ((temp_y[18] == 1 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box2[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                            temp_box2[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box2[temp_y[18] + 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18]] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                            temp_box2[temp_y[18] + 1][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 0 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box2[temp_y[18] + 1][temp_x[18] + 1] == 'o' || temp_box2[temp_y[18] + 1][temp_x[18] + 1] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            if (temp_box2[temp_y[18]][temp_x[18]] == 'X')
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            }
                            else
                            {
                                temp_box2[temp_y[19]][temp_x[19]] = 'x';
                            }
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                            temp_box2[temp_y[18] + 1][temp_x[18] + 1] = '.';
                        }
                    }

                    // moving down with knock
                    else if (temp_y[18] - 2 == temp_y[19] && temp_box2[temp_y[18]][temp_x[18]] == 'X')
                    {
                        if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 0 && (temp_box2[temp_y[18] - 1][temp_x[18] - 1] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18] - 1] == 'O') &&
                            (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18] - 1][temp_x[18] - 1] = '.';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 7 || temp_y[18] == 3 || temp_y[18] == 5) && temp_x[18] != 3 && (temp_box2[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 0 && (temp_box2[temp_y[18] - 1][temp_x[18]] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18]] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] - 1 == temp_x[19])
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18] - 1][temp_x[18]] = '.';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                        else if ((temp_y[18] == 6 || temp_y[18] == 2 || temp_y[18] == 4) && temp_x[18] != 3 && (temp_box2[temp_y[18] - 1][temp_x[18] + 1] == 'o' || temp_box2[temp_y[18] - 1][temp_x[18] + 1] == 'O') &&
                                 (temp_box2[temp_y[19]][temp_x[19]] == ' ' || temp_box2[temp_y[19]][temp_x[19]] == '.') && temp_x[18] + 1 == temp_x[19])
                        {
                            temp_box2[temp_y[19]][temp_x[19]] = 'X';
                            temp_box2[temp_y[18] - 1][temp_x[18] + 1] = '.';
                            temp_box2[temp_y[18]][temp_x[18]] = '.';
                        }
                    }

                    // king
                    for (size_t w = 0; w < 4; w++)
                    {
                        if (temp_box2[7][w] == 'x')
                            temp_box2[7][w] = 'X';
                    }

                    total_knocks[index]++;
                    max_knocks = (total_knocks[0] > total_knocks[1]) ? total_knocks[0] : total_knocks[1];
                }

                for (size_t v = 0; v < 8; v++)
                {
                    for (size_t w = 0; w < 4; w++)
                    {
                        temp_box2[v][w] = temp_box1[v][w];
                    }
                }

                total_knocks[index] = 0;
            }

            temp_y[18] = temp_y[19];
            temp_x[18] = temp_x[19];

            rand_num++;
            if (rand_num == total_moves)
            {
                rand_num = 0;
            }
            if (rand_num == temp_num)
            {
                break;
            }

            index = (index == 0) ? 1 : 0;
        }
    }

    return max_knocks;
}

int playerNext_knock()
{
    int index{};

    for (size_t q = 0; q <= 7; q++)
    {
        for (size_t r = 0; r < 4; r++)
        {
            // checking upwards
            if ((q == 0 || q == 2 || q == 4) && r != 3 && (box[q + 1][r + 1] == 'o' || box[q + 1][r + 1] == 'O') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && (box[q][r] == 'x' || box[q][r] == 'X'))
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 0 || q == 2 || q == 4) && r != 0 && (box[q + 1][r] == 'o' || box[q + 1][r] == 'O') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && (box[q][r] == 'x' || box[q][r] == 'X'))
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 3 && (box[q + 1][r] == 'o' || box[q + 1][r] == 'O') &&
                (box[q + 2][r + 1] == ' ' || box[q + 2][r + 1] == '.') && (box[q][r] == 'x' || box[q][r] == 'X'))
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 1 || q == 3 || q == 5) && r != 0 && (box[q + 1][r - 1] == 'o' || box[q + 1][r - 1] == 'O') &&
                (box[q + 2][r - 1] == ' ' || box[q + 2][r - 1] == '.') && (box[q][r] == 'x' || box[q][r] == 'X'))
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }

            // checking downwards
            if ((q == 6 || q == 2 || q == 4) && r != 3 && (box[q - 1][r + 1] == 'o' || box[q - 1][r + 1] == 'O') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && box[q][r] == 'X')
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 6 || q == 2 || q == 4) && r != 0 && (box[q - 1][r] == 'o' || box[q - 1][r] == 'O') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && box[q][r] == 'X')
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 3 && (box[q - 1][r] == 'o' || box[q - 1][r] == 'O') &&
                (box[q - 2][r + 1] == ' ' || box[q - 2][r + 1] == '.') && box[q][r] == 'X')
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
            if ((q == 7 || q == 3 || q == 5) && r != 0 && (box[q - 1][r - 1] == 'o' || box[q - 1][r - 1] == 'O') &&
                (box[q - 2][r - 1] == ' ' || box[q - 2][r - 1] == '.') && box[q][r] == 'X')
            {
                temp_y[index] = q;
                temp_x[index] = r;
                index++;
            }
        }
    }

    return index;
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