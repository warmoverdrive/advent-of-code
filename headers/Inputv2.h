#ifndef INPUT1_H
#define INPUT1_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

template <typename T>
struct Input
{
    std::vector<T> data;
    Input(const std::string &path, char delim = ' ')
    {
        try
        {
            std::ifstream infile(path);
            T t;
            while (std::getline(infile, t, delim))
            {
                data.push_back(t);
            }
        }
        catch (...)
        {
            std::cout << "An error occured!\n";
        }
    }
};

#endif