#ifndef BUS_INPUT_H
#define BUS_INPUT_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using ulong = unsigned long;

namespace BusInput
{
    std::vector<ulong> GetBusData(const std::string &path, char delim)
    {
        std::vector<ulong> data;
        try
        {
            std::ifstream infile(path);
            std::string line;
            std::getline(infile, line, '\n');
            data.push_back(stol(line));

            while (std::getline(infile, line, delim))
            {
                if (line == "x")
                    continue;
                else
                    data.push_back(stol(line));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return data;
    }
} // namespace BusInput

#endif // BUS_INPUT_H