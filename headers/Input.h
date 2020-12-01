#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

enum Mode {STRING, INTEGER, DOUBLE };

struct Input {
    std::vector<std::string> sdata;
    std::vector<int> idata;
    std::vector<double> ddata;
    Input(std::string path, char delim = ' ', Mode mode = Mode::STRING) {
        try {
            std::ifstream infile(path);
            std::string l;
            while(std::getline(infile, l, delim)) {
                if (mode == Mode::STRING)    sdata.push_back(l);
                if (mode == Mode::INTEGER)   idata.push_back(std::stoi(l));
                if (mode == Mode::DOUBLE)    ddata.push_back(std::stod(l));
            }
        } catch (...) {
            std::cout << "An error occured!\n";
        }
    }
};

#endif