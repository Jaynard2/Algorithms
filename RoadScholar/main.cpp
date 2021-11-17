#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "Tester.h"

/*********************************************************
* Summary: Entry point of the program. Initializes the Tester class, takes input,
* and displays the final results.
*
* Author: Nathanael Cook
* Created: Nov 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

std::vector<std::string> Split(std::string val);
/* Screwed up test case on Gradel
10 17 5
0 1 5.2
0 4 7.7
1 2 8.1
1 3 3.3
2 4 1.3
2 6 6.6
3 6 4.2
3 9 8.6
4 5 4.4
4 7 5.5
5 6 2.3
5 7 3.3
6 7 7.0
6 8 2.1
6 9 2.2
7 8 4.4
8 9 6.6
0 AA
3 BB
5 CC
7 DD
9 EE
4
7 5 1.0
7 4 1.0
3 6 1.0
0 4 1.0
*/

int main() {
    std::string buffer;
    std::getline(std::cin, buffer);
    auto lng = Split(buffer);
    int intersections = std::stoi(lng[0]);
    int roads = std::stoi(lng[1]);
    int cities = std::stoi(lng[2]);
    buffer = "";

    Tester atlas = Tester(intersections);

    for (int i = 0; i < roads; i++) {
        std::getline(std::cin, buffer);
        auto lng = Split(buffer);
        atlas.addEdge(std::stoi(lng.at(0)), std::stoi(lng.at(1)), std::stof(lng.at(2)));
        buffer = "";
    }
    for (int i = 0; i < cities; i++) {
        std::getline(std::cin, buffer);
        auto lng = Split(buffer);
        atlas.addCity(std::stoi(lng.at(0)), lng.at(1));
        buffer = "";
    }

    std::getline(std::cin, buffer);
    int SignNum = std::stoi(buffer);
    std::vector<std::vector<float>> Signs;
    buffer = "";
    for (int i = 0; i < SignNum; i++) {
        std::getline(std::cin, buffer);
        auto segments = Split(buffer);
        std::vector<float> intsegments;
        intsegments.push_back(std::stof(segments[0]));
        intsegments.push_back(std::stof(segments[1]));
        intsegments.push_back(std::stof(segments[2]));
        Signs.push_back(intsegments);
        buffer = "";
    }

    for (int i = 0; i < Signs.size(); i++) {
        atlas.test(Signs.at(i)[0], Signs.at(i)[1], Signs.at(i)[2]);
        auto result = atlas.getResult();

        for (auto obj : result) {
            char str[30] = "";
            sprintf_s(str, "%s%s%-2.0f\0", obj.first.c_str(), std::string(20 - obj.first.length(), ' ').c_str(), obj.second);

            if (str[strlen(str) - 1] == ' ')
            {
                str[strlen(str) - 1] = '\0';
            }

            std::cout << str << std::endl;
        }

        if (i != Signs.size() - 1)
        {
            std::cout << std::endl;
        }
    }
}


std::vector<std::string> Split(std::string val) {
    std::vector<std::string> result;
    std::string temp = "";
    for (int i = 0; i < val.length(); i++) {
        if (val[i] == ' ') {
            result.push_back(temp);
            temp = "";
        }
        else {
            temp += val[i];
        }
    }
    result.push_back(temp);
    return result;
}