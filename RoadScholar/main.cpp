#include <iostream>
#include <vector>
#include <string>
#include "Tester.h"

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
        atlas.addEdge(std::stoi(lng[0]), std::stoi(lng[1]), std::stoi(lng[2]));
        buffer = "";
    }
    for (int i = 0; i < roads; i++) {
        std::getline(std::cin, buffer);
        auto lng = Split(buffer);
        atlas.addCity(std::stoi(lng[0]), lng[1]);
        buffer = "";
    }

    std::getline(std::cin, buffer);
    int SignNum = std::stoi(buffer);
    std::vector<int[3]> Signs;
    buffer = "";
    for (int i = 0; i < SignNum; i++) {
        std::getline(std::cin, buffer);
        auto segments = Split(buffer);
        Signs.push_back({std::stoi(segments[0]), std::stoi(segments[1]), std::stoi(segments[2])});
        buffer = "";
    }

    for (int i = 0; i < Signs.size(); i++) {
        atlas.test(Signs.at(i)[0], Signs.at(i)[1], Signs.at(i)[2]);
        auto result = atlas.getResult();
        for (auto obj : result) {
            std::cout << obj << std::endl;
        }
        std::cout << std::endl;
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
    return result;
}