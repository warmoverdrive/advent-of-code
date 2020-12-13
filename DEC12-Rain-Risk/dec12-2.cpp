#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <chrono>
#include "../headers/Inputv4.h"
#include "boat.h"

using Instruction = std::pair<char, int>;
using InstructionSet = std::queue<Instruction>;
const int _N{0}, _E{90}, _S{180}, _W{270};

int FindManhattanDistance(std::vector<std::string> &input);
InstructionSet *GenerateInstructions(std::vector<std::string> &input);
void ExecInstructions(Boat &boat, InstructionSet &instructions);
int CalcManhattanDist(Boat &boat);

int main()
{
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day12Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    int result = FindManhattanDistance(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Manhattan distance: " << result << '\n';
    std::cout << "Found in: " << duration << "ms\n";
}

int FindManhattanDistance(std::vector<std::string> &input)
{
    Boat boat{};
    InstructionSet instructionSet = *GenerateInstructions(input);

    ExecInstructions(boat, instructionSet);

    return CalcManhattanDist(boat);
}

InstructionSet *GenerateInstructions(std::vector<std::string> &input)
{
    static InstructionSet instSet{};

    for (auto line : input)
    {
        Instruction temp{};
        temp.first = line.at(0);
        temp.second = std::stoi(line.substr(1));
        instSet.push(temp);
    }

    return &instSet;
}

void ExecInstructions(Boat &boat, InstructionSet &instructions)
{
    while (!instructions.empty())
    {
        if (boat.waypoint.first == 0 || boat.waypoint.second == 0)
            std::cout << "! ";
        switch (instructions.front().first)
        {
        case 'N':
            boat.MoveWaypoint('N', instructions.front().second);
            break;
        case 'S':
            boat.MoveWaypoint('S', instructions.front().second);
            break;
        case 'W':
            boat.MoveWaypoint('W', instructions.front().second);
            break;
        case 'E':
            boat.MoveWaypoint('E', instructions.front().second);
            break;
        case 'L': // counter-clockwise turn
            boat.RotateWaypoint(-instructions.front().second);
            break;
        case 'R': // clockwise turn
            boat.RotateWaypoint(instructions.front().second);
            break;
        case 'F':
            boat.MoveBoat(instructions.front().second);
            break;
        }
        instructions.pop();
    }
}

int CalcManhattanDist(Boat &boat)
{
    return abs(boat.local.first) + abs(boat.local.second);
}