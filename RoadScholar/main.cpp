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
        atlas.addEdge(std::stoi(lng.at(0)), std::stod(lng.at(1)), std::stod(lng.at(2)));
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
        intsegments.push_back(std::stod(segments[0]));
        intsegments.push_back(std::stod(segments[1]));
        intsegments.push_back(std::stod(segments[2]));
        Signs.push_back(intsegments);
        buffer = "";
    }

    for (int i = 0; i < Signs.size(); i++) {
        atlas.test(Signs.at(i)[0], Signs.at(i)[1], Signs.at(i)[2]);
        auto result = atlas.getResult();

        for (auto obj : result) {
            char str[30] = "";
            sprintf_s(str, "%s%s%-2.0f\0", obj.first.c_str(), std::string(20 - obj.first.length(), ' ').c_str(), obj.second);
            //sprintf(str, "%s%s%-2.0f\0", obj.first.c_str(), std::string(20 - obj.first.length(), ' ').c_str(), obj.second);

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