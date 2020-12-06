#ifndef INPUT2_H
#define INPUT2_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

template <typename T>
struct Input
{
    std::vector<T> data;
    Input(const std::string &path, char delim)
    {
        try
        {
            std::ifstream infile(path);
            std::string line;
            while (std::getline(infile, line, delim))
            {
                T element;
                std::stringstream input(line);
                while (input >> element)
                    data.push_back(element);
            }
        }
        catch (...)
        {
            std::cout << "An error occured!\n";
        }
    }
};

#endif