// Copyright 2016 Virgilio Sanz <virgilio.sanz@gmail.com>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    std::ifstream ifile{argv[1]};
    std::string line;
    std::vector<std::string> data;

    while (std::getline(ifile, line)) {
        data.push_back(line);
    }
    std::sort(data.begin(), data.end());

    std::ofstream ofile{argv[2]};
    for (const auto &i : data) {
        ofile << i << std::endl;
    }

    return EXIT_SUCCESS;
}
