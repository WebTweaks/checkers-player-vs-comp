#include <iostream>
#include <iomanip>

int main()
{
    int align{100};
    const short int max_length{20};
    char player_name[max_length]{};

    std::cout << '\n';
    std::cout << "Enter your name dear: ";
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

    std::cout << '\n';
    std::cout << std::right;
    std::cout << std::setw(align) << "====================================" << std::endl;
    std::cout << std::setw(align) << "COMP vs " << player_name << std::endl;
    std::cout << std::setw(align) << "====================================" << std::endl;

    return 0;
}