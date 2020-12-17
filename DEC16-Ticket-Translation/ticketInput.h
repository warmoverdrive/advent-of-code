#ifndef TICKET_INPUT_H
#define TICKET_INPUT_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using Range = std::pair<int, int>;
using Ranges = std::pair<Range, Range>;
using Fields = std::unordered_map<std::string, Ranges>;
using Ticket = std::vector<int>;

struct Input
{
    Fields fields;
    Ticket yourTick;
    std::vector<Ticket> nearbyTicks;
    Input(const std::string &filepath);
    void DisplayContents() const;
};

Input::Input(const std::string &filepath)
    : fields{}, yourTick{}, nearbyTicks{}
{
    std::ifstream infile(filepath);
    std::string line{};
    std::stringstream sstream{};

    bool collectedFields{};
    bool collectedYourTick{};

    while (std::getline(infile, line, '\n'))
    {
        if (!collectedFields)
        {
            if (line == "")
                collectedFields = true;
            else
            {
                std::string name;
                int range1_1{}, range1_2{};
                int range2_1{}, range2_2{};

                sstream << line;
                std::getline(sstream, name, ':');
                sstream.ignore(1);
                sstream >> range1_1 >> range1_2;
                sstream.ignore(4);
                sstream >> range2_1 >> range2_2;
                range1_2 = abs(range1_2);
                range2_2 = abs(range2_2);

                Range range1{range1_1, range1_2}, range2{range2_1, range2_2};
                Ranges ranges{range1, range2};
                fields.emplace(name, ranges);

                sstream.clear();
                sstream.str("");
            }
        }
        else if (!collectedYourTick)
        {
            if (line == "your ticket:")
                continue;
            else if (line == "")
                collectedYourTick = true;
            else
            {
                std::string temp{};
                sstream << line;
                while (std::getline(sstream, temp, ','))
                {
                    yourTick.push_back(std::stoi(temp));
                }
                sstream.clear();
                sstream.str("");
            }
        }
        else
        {
            if (line == "nearby tickets:")
                continue;
            else
            {
                Ticket tempTick{};
                std::string temp{};
                sstream << line;
                while (std::getline(sstream, temp, ','))
                {
                    tempTick.push_back(std::stoi(temp));
                }
                nearbyTicks.push_back(tempTick);
                sstream.clear();
                sstream.str("");
            }
        }
    }
}

void Input::DisplayContents() const
{
    std::cout << "Fields:\n";
    for (auto field : fields)
    {
        std::cout << field.first << ": " << field.second.first.first << "-" << field.second.first.second << " ";
        std::cout << field.second.second.first << "-" << field.second.second.second << '\n';
    }
    std::cout << "\nYour Ticket:\n";
    for (auto i : yourTick)
        std::cout << i << " ";
    std::cout << "\n\nNearby Tickets:\n";
    for (auto ticket : nearbyTicks)
    {
        for (auto val : ticket)
            std::cout << val << ' ';
        std::cout << '\n';
    }
}

#endif // TICKET_INPUT_H