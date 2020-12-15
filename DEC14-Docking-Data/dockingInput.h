#ifndef DOCKING_INPUT_H
#define DOCKING_INPUT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

// instruction , value
// instruction: a number = acess mem at number, mask = define the next bitmask
// value: a number = write number to mem add, a string = new mask
using Instruction = std::pair<std::string, std::string>;

namespace DockingInput
{
    std::vector<Instruction> GetProgram(const std::string &path)
    {
        std::vector<Instruction> program{};
        try
        {
            std::ifstream infile(path);
            std::string line{};
            std::stringstream sstream{};

            while (std::getline(infile, line, '\n'))
            {
                Instruction temp{};
                if (line.substr(0, 4) == "mask")
                {
                    temp.first = "mask";          // set inst to mask
                    temp.second = line.substr(7); // grab mask info
                }
                else
                {
                    sstream << line;
                    sstream.ignore(4, '[');
                    std::getline(sstream, temp.first, ']');
                    sstream.ignore(3);
                    sstream >> temp.second;
                    sstream.clear();
                    sstream.str("");
                }
                program.push_back(temp);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return program;
    }
} // namespace DockingInput

#endif // DOCKING_INPUT_H