#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <string>
#include <bitset>
#include "dockingInput.h"

using MemoryMap = std::unordered_map<unsigned long int, std::bitset<36>>;

void ApplyBitmask(std::string &mask, std::bitset<36> &target);
unsigned long long CalculateMemoryValues(std::vector<Instruction> &program);

int main()
{
    auto instructionSet = DockingInput::GetProgram("PuzzleInput/Day14Input.txt");
    //auto instructionSet = DockingInput::GetProgram("PuzzleInput/Day14Input.txt");

    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long result = CalculateMemoryValues(instructionSet);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Sum of all values in memory: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

unsigned long long CalculateMemoryValues(std::vector<Instruction> &program)
{
    MemoryMap memoryMap{};
    std::string bitmask{};
    unsigned long long sum{};

    for (auto inst : program)
    {
        if (inst.first == "mask")
            bitmask = inst.second;
        else
        {
            unsigned long int tempMem = std::stoul(inst.first);
            std::bitset<36> tempData = std::stoull(inst.second);
            ApplyBitmask(bitmask, tempData);

            if (memoryMap.find(tempMem) != memoryMap.end())
            {
                memoryMap.at(tempMem) = tempData;
            }
            else
                memoryMap.insert({tempMem, tempData});
        }
    }

    for (auto m : memoryMap)
    {
        sum += m.second.to_ullong();
    }

    return sum;
}

void ApplyBitmask(std::string &mask, std::bitset<36> &target)
{
    for (int m{}, t{35}; m < mask.length(); m++, t--)
    {
        if (mask.at(m) == '1')
            target[t] = 1;
        else if (mask.at(m) == '0')
            target[t] = 0;
    }
}