#include <iostream>
#include <iomanip>

char box[8][4]{};
short int play_mode{};
const short int max_length{20};
char player_name[max_length]{};
unsigned short int choice[3]{};
unsigned short int y[3];
unsigned short int x[3];

void reset_board();
void print_board();
void player();
char choice_processing(int index);
char move_piece(char knock);
char knocks(char player, int *total);
char more_knocks();

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

    box[3][1] = 'o';
    box[3][2] = 'o';
    box[2][0] = 'x';
    box[2][1] = 'X';
    box[5][1] = 'O';
    box[5][2] = 'O';
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

    int total_knocks{10};
    char next{'N'};
    char knock = knocks('P', &total_knocks);

    char played{};

    if (knock == 'Y')
    {
        if (total_knocks > 1)
        {
            print_board();
            std::cout << "        -----------------------------------------" << std::endl;
            std::cout << "               KNOCK AVAILABLE (MANDATORY)" << std::endl;
            std::cout << "        -----------------------------------------" << std::endl;

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

            while (next == 'N')
            {
                std::cout << "        Enter piece  row# column# e.g 34: ";
                std::cin >> choice[1];
                choice_processing(1);

                next = more_knocks();
                if (next == 'N')
                {
                    print_board();
                    std::cout << "        Choice invalid! Try again!" << std::endl;
                }
                else
                {
                    y[0] = y[1];
                    x[0] = x[1];

                    if (box[y[1]][x[1]] == 'X')
                    {
                        box[y[1]][x[1]] = 'S';
                    }
                    else
                    {
                        box[y[1]][x[1]] = 's';
                    }
                }
            }

            print_board();
            std::cout << "        -----------------------------------------" << std::endl;
            std::cout << "               SELECTED " << player_name << std::endl;
            std::cout << "        -----------------------------------------" << std::endl;

            do
            {
                std::cout << "        Enter target row# column# e.g 23: ";
                std::cin >> choice[1];
                choice_processing(1);

                played = move_piece('Y');
                if (played == 'N')
                {
                    print_board();
                    std::cout << "        Invalid choice! Try again!" << std::endl;
                }

            } while (played == 'N');
        }
        else if (total_knocks == 1)
        {
            if (box[y[0]][x[0]] == 'X')
            {
                box[y[0]][x[0]] = 'S';
            }
            else
            {
                box[y[0]][x[0]] = 's';
            }

            print_board();
            std::cout << "        -----------------------------------------" << std::endl;
            std::cout << "               KNOCK AVAILABLE (MANDATORY)" << std::endl;
            std::cout << "        -----------------------------------------" << std::endl;

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

            std::cout << "               SELECTED " << player_name << std::endl;
            std::cout << "        -----------------------------------------" << std::endl;

            do
            {
                std::cout << "        Enter target row# column# e.g 23: ";
                std::cin >> choice[1];
                choice_processing(1);

                played = move_piece('Y');
                if (played == 'N')
                {
                    print_board();
                    std::cout << "        Invalid choice! Try again!" << std::endl;
                }

            } while (played == 'N');
        }
    }
    else
    {
        do
        {
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

            std::cout << "        Enter piece  row# column# e.g 12: ";
            std::cin >> choice[0];
            choice_processing(0);

            std::cout << "        Enter target row# column# e.g 23: ";
            std::cin >> choice[1];
            choice_processing(1);

            played = move_piece('N');

        } while (played == 'N');
    }

    while ((played = more_knocks()) != 'N')
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

        print_board();
        std::cout << "        -----------------------------------------" << std::endl;
        std::cout << "               CONSECUTIVE KNOCK AVAILABLE " << std::endl;
        std::cout << "        -----------------------------------------" << std::endl;

        do
        {
            std::cout << "        Enter target row# column# e.g 23: ";
            std::cin >> choice[1];
            choice_processing(1);

            next = move_piece('Y');
            if (next == 'N')
            {
                print_board();
                std::cout << "        Invalid choice! Try again!" << std::endl;
            }

        } while (next == 'N');
    }

    print_board();
    std::cout << "        -----------------------------------------" << std::endl;
    std::cout << "               MOVED " << player_name << std::endl;
    std::cout << "        -----------------------------------------" << std::endl;
}

char choice_processing(int index)
{
    char proceed{};
    if (choice[index] == 11 || choice[index] == 13 || choice[index] == 15 || choice[index] == 17 || choice[index] == 22 || choice[index] == 24 || choice[index] == 26 || choice[index] == 28 || choice[index] == 31 || choice[index] == 33 || choice[index] == 35 || choice[index] == 37 || choice[index] == 42 || choice[index] == 44 || choice[index] == 46 || choice[index] == 48)
    {
        proceed = 'N';
    }
    else if (choice[index] == 51 || choice[index] == 53 || choice[index] == 55 || choice[index] == 57 || choice[index] == 62 || choice[index] == 64 || choice[index] == 66 || choice[index] == 68 || choice[index] == 71 || choice[index] == 73 || choice[index] == 75 || choice[index] == 77 || choice[index] == 82 || choice[index] == 84 || choice[index] == 86 || choice[index] == 88)
    {
        proceed = 'N';
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
            proceed = 'Y';
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
            proceed = 'Y';
        }
    }

    return proceed;
}

char move_piece(char knock)
{
    char moved{'N'};

    // moving up without knock
    if (y[0] + 1 == y[1] && knock == 'N')
    {
        if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && (x[0] == x[1] || x[0] + 1 == x[1]))
        {
            moved = 'Y';
            if (box[y[0]][x[0]] == 'S')
            {
                box[y[1]][x[1]] = 'X';
            }
            else
            {
                box[y[1]][x[1]] = 'x';
            }
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            moved = 'Y';
            if (box[y[0]][x[0]] == 'S')
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
            moved = 'Y';
            if (box[y[0]][x[0]] == 'S')
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
            moved = 'Y';
            if (box[y[0]][x[0]] == 'S')
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
    else if (y[0] - 1 == y[1] && knock == 'N' && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] != 3 && (x[0] == x[1] || x[0] + 1 == x[1]) &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 2 || y[0] == 4 || y[0] == 6) && x[0] == 3 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] != 0 && (x[0] == x[1] || x[0] - 1 == x[1]) &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5 || y[0] == 7) && x[0] == 0 && x[0] == x[1] &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.'))
        {
            moved = 'Y';
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
            moved = 'Y';
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
        }
        else if ((y[0] == 1 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            moved = 'Y';
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
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] + 1][x[0]] == 'o' || box[y[0] + 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            moved = 'Y';
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
        }
        else if ((y[0] == 0 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] + 1][x[0] + 1] == 'o' || box[y[0] + 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            moved = 'Y';
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
        }
    }

    // moving down with knock
    else if (y[0] - 2 == y[1] && box[y[0]][x[0]] == 'S')
    {
        if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 0 && (box[y[0] - 1][x[0] - 1] == 'o' || box[y[0] - 1][x[0] - 1] == 'O') &&
            (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] - 1] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 7 || y[0] == 3 || y[0] == 5) && x[0] != 3 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 0 && (box[y[0] - 1][x[0]] == 'o' || box[y[0] - 1][x[0]] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] - 1 == x[1])
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0]] = '.';
            box[y[0]][x[0]] = '.';
        }
        else if ((y[0] == 6 || y[0] == 2 || y[0] == 4) && x[0] != 3 && (box[y[0] - 1][x[0] + 1] == 'o' || box[y[0] - 1][x[0] + 1] == 'O') &&
                 (box[y[1]][x[1]] == ' ' || box[y[1]][x[1]] == '.') && x[0] + 1 == x[1])
        {
            moved = 'Y';
            box[y[1]][x[1]] = 'X';
            box[y[0] - 1][x[0] + 1] = '.';
            box[y[0]][x[0]] = '.';
        }
    }

    return moved;
}

char knocks(char player, int *total)
{
    char knock{};

    if (player == 'P')
    {
        int count{};
        for (int a = 0; a < 8; a++)
        {
            for (int b = 0; b < 4; b++)
            {
                // checking upwards
                if ((a == 0 || a == 2 || a == 4) && b != 3 && (box[a + 1][b + 1] == 'o' || box[a + 1][b + 1] == 'O') &&
                    (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 0 || a == 2 || a == 4) && b != 0 && (box[a + 1][b] == 'o' || box[a + 1][b] == 'O') &&
                    (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 3 && (box[a + 1][b] == 'o' || box[a + 1][b] == 'O') &&
                    (box[a + 2][b + 1] == ' ' || box[a + 2][b + 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 1 || a == 3 || a == 5) && b != 0 && (box[a + 1][b - 1] == 'o' || box[a + 1][b - 1] == 'O') &&
                    (box[a + 2][b - 1] == ' ' || box[a + 2][b - 1] == '.') && (box[a][b] == 'x' || box[a][b] == 'X'))
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }

                // checking downwards
                if ((a == 6 || a == 2 || a == 4) && b != 3 && (box[a - 1][b + 1] == 'o' || box[a - 1][b + 1] == 'O') &&
                    (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && box[a][b] == 'X')
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 6 || a == 2 || a == 4) && b != 0 && (box[a - 1][b] == 'o' || box[a - 1][b] == 'O') &&
                    (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && box[a][b] == 'X')
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 3 && (box[a - 1][b] == 'o' || box[a - 1][b] == 'O') &&
                    (box[a - 2][b + 1] == ' ' || box[a - 2][b + 1] == '.') && box[a][b] == 'X')
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
                if ((a == 7 || a == 3 || a == 5) && b != 0 && (box[a - 1][b - 1] == 'o' || box[a - 1][b - 1] == 'O') &&
                    (box[a - 2][b - 1] == ' ' || box[a - 2][b - 1] == '.') && box[a][b] == 'X')
                {
                    y[0] = a;
                    x[0] = b;
                    count++;
                }
            }
        }

        *total = count;
    }

    if (*total > 0)
        knock = 'Y';
    else
        knock = 'N';

    return knock;
}

char more_knocks()
{
    char knock_present{'N'};

    if (box[y[1]][x[1]] == 'x' || box[y[1]][x[1]] == 'X')
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'o' || box[y[1] + 1][x[1] - 1] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'o' || box[y[1] + 1][x[1]] == 'O') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'o' || box[y[1] + 1][x[1] + 1] == 'O') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
    }
    if (box[y[1]][x[1]] == 'X')
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'o' || box[y[1] - 1][x[1] - 1] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'o' || box[y[1] - 1][x[1]] == 'O') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'o' || box[y[1] - 1][x[1] + 1] == 'O') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
    }
    if (box[y[1]][x[1]] == 'o' || box[y[1]][x[1]] == 'O')
    {
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] - 1][x[1] - 1] == 'x' || box[y[1] - 1][x[1] - 1] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 7 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] - 1][x[1]] == 'x' || box[y[1] - 1][x[1]] == 'X') &&
            (box[y[1] - 2][x[1] - 1] == ' ' || box[y[1] - 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 6 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] - 1][x[1] + 1] == 'x' || box[y[1] - 1][x[1] + 1] == 'X') &&
            (box[y[1] - 2][x[1] + 1] == ' ' || box[y[1] - 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
    }
    if (box[y[1]][x[1]] == 'O')
    {
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 0 && (box[y[1] + 1][x[1] - 1] == 'x' || box[y[1] + 1][x[1] - 1] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 1 || y[1] == 3 || y[1] == 5) && x[1] != 3 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 0 && (box[y[1] + 1][x[1]] == 'x' || box[y[1] + 1][x[1]] == 'X') &&
            (box[y[1] + 2][x[1] - 1] == ' ' || box[y[1] + 2][x[1] - 1] == '.'))
        {
            knock_present = 'Y';
        }
        if ((y[1] == 0 || y[1] == 2 || y[1] == 4) && x[1] != 3 && (box[y[1] + 1][x[1] + 1] == 'x' || box[y[1] + 1][x[1] + 1] == 'X') &&
            (box[y[1] + 2][x[1] + 1] == ' ' || box[y[1] + 2][x[1] + 1] == '.'))
        {
            knock_present = 'Y';
        }
    }

    return knock_present;
}