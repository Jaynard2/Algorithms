#include <iostream>
#include <algorithm>
#include <string>
#include "RedBlackTree.h"

int main()
{
    RedBlackTree<int> tree;


    while (true)
    {
        std::string input = "";
        std::cin >> input;

        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (std::find_if(input.begin(), input.end(), [](auto c) { return !isdigit(c); }) != input.end())
        {
            if (!input.compare("print"))
                std::cout << std::endl << tree << std::endl;
            else if (!input.compare("q"))
                break;

            continue;
        }

        tree.insert(std::stoi(input));

        std::cout << std::endl << tree << std::endl;
    }
    

    return 0;
}
