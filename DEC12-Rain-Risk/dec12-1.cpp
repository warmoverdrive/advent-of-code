#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <chrono>
#include "../headers/Inputv4.h"

struct Boat
{
    char bearing;
    int nsDistTraveled;
    int ewDistTraveled;
    Boat(char b = 'E', int ns = 0, int ew = 0)
        : bearing{b}, nsDistTraveled{ns}, ewDistTraveled{ew} {}
};

using Instruction = std::pair<char, int>;
using InstructionSet = std::queue<Instruction>;
const int _N{0}, _E{90}, _S{180}, _W{270};

int FindManhattanDistance(std::vector<std::string> &input);
InstructionSet *GenerateInstructions(std::vector<std::string> &input);
void ExecInstructions(Boat &boat, InstructionSet &instructions);
int CalcManhattanDist(Boat &boat);
void TurnBoat(Boat &boat, int degrees);
void MoveBoat(Boat &boat, int dist);
char DegreesToCardinal(int d);
int CardinalToDegrees(char b);

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

    int manhattanDist = CalcManhattanDist(boat);

    return manhattanDist;
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
        switch (instructions.front().first)
        {
        case 'N':
            boat.nsDistTraveled += instructions.front().second;
            break;
        case 'S':
            boat.nsDistTraveled -= instructions.front().second;
            break;
        case 'W':
            boat.ewDistTraveled -= instructions.front().second;
            break;
        case 'E':
            boat.ewDistTraveled += instructions.front().second;
            break;
        case 'L': // counter-clockwise turn
            TurnBoat(boat, -instructions.front().second);
            break;
        case 'R': // clockwise turn
            TurnBoat(boat, instructions.front().second);
            break;
        case 'F':
            MoveBoat(boat, instructions.front().second);
            break;
        }
        instructions.pop();
    }
}

int CalcManhattanDist(Boat &boat)
{
    int nsDistTravAbs = abs(boat.nsDistTraveled);
    int ewDistTrabAbs = abs(boat.ewDistTraveled);

    return nsDistTravAbs + ewDistTrabAbs;
}

void TurnBoat(Boat &boat, int degrees)
{
    int bearingDegrees = CardinalToDegrees(boat.bearing);

    bearingDegrees = (bearingDegrees + degrees) % 360;

    if (bearingDegrees >= 0)
        boat.bearing = DegreesToCardinal(bearingDegrees);
    else
        boat.bearing = DegreesToCardinal(bearingDegrees + 360);
}

void MoveBoat(Boat &boat, int dist)
{
    if (boat.bearing == 'N')
        boat.nsDistTraveled += dist;
    else if (boat.bearing == 'W')
        boat.ewDistTraveled -= dist;
    else if (boat.bearing == 'S')
        boat.nsDistTraveled -= dist;
    else if (boat.bearing == 'E')
        boat.ewDistTraveled += dist;
}

char DegreesToCardinal(int d)
{
    if (d == _N)
        return 'N';
    else if (d == _W)
        return 'W';
    else if (d == _S)
        return 'S';
    else if (d == _E)
        return 'E';
    else
    {
        throw "Invalid Direction!";
        return 0;
    }
}

int CardinalToDegrees(char b)
{
    if (b == 'N')
        return _N;
    else if (b == 'W')
        return _W;
    else if (b == 'S')
        return _S;
    else if (b == 'E')
        return _E;
    else
        throw "Invalid Direction!";
    return INT16_MAX;
}