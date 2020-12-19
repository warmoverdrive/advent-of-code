#include <iostream>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <string>
#include "powercube.h"
#include "../headers/Inputv4.h"

using PocketDimension = std::unordered_map<Powercube, bool>;

const int directionCnt{26};
const Powercube directions[26]{
    Powercube(-1, -1, -1),
    Powercube(0, -1, -1),
    Powercube(1, -1, -1),
    Powercube(-1, 0, -1),
    Powercube(0, 0, -1),
    Powercube(1, 0, -1),
    Powercube(-1, 1, -1),
    Powercube(0, 1, -1),
    Powercube(1, 1, -1),
    Powercube(-1, -1, 0),
    Powercube(0, -1, 0),
    Powercube(1, -1, 0),
    Powercube(-1, 0, 0),
    Powercube(1, 0, 0),
    Powercube(-1, 1, 0),
    Powercube(0, 1, 0),
    Powercube(1, 1, 0),
    Powercube(-1, -1, 1),
    Powercube(0, -1, 1),
    Powercube(1, -1, 1),
    Powercube(-1, 0, 1),
    Powercube(0, 0, 1),
    Powercube(1, 0, 1),
    Powercube(-1, 1, 1),
    Powercube(0, 1, 1),
    Powercube(1, 1, 1)};

int PowercubeSimulation(std::vector<std::string> &input, int &cycles);
void PopulatePocketDimension(std::vector<std::string> &input, PocketDimension &currentPD);
void CheckNeighbors(PocketDimension &lastPD, PocketDimension &currentPD);

int main()
{
    // Input Params
    int simulationCycles{6};
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day17Test.txt", '\n');
    //std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day17Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    int result = PowercubeSimulation(input, simulationCycles);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Remaining Active Power Cubes: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

int PowercubeSimulation(std::vector<std::string> &input, int &cycles)
{
    PocketDimension currentPD{};
    PocketDimension lastPD{};
    int i{};
    int result{};

    PopulatePocketDimension(input, currentPD);

    while (i <= cycles)
    {
        lastPD = currentPD;

        CheckNeighbors(lastPD, currentPD);

        i++;
    }

    for (auto point : currentPD)
    {
        //std::cout << point.first << '\n';
        if (point.second == true)
            result++;
    }
    std::cout << currentPD.size() << '\n';

    return result;
}

void PopulatePocketDimension(std::vector<std::string> &input, PocketDimension &currentPD)
{
    for (int y{}; y < input.size(); y++)
    {
        for (int x{}; x < input.at(y).size(); x++)
        {
            if (input[y][x] == '#')
                currentPD.emplace(Powercube(x, y, 0), true);
            else
                currentPD.emplace(Powercube(x, y, 0), false);
        }
    }
}

void CheckNeighbors(PocketDimension &lastPD, PocketDimension &currentPD)
{
    for (auto point : lastPD)
    {
        int activeNeighbors{};

        for (int dir{0}; dir < directionCnt; dir++)
        {
            Powercube check(point.first + directions[dir]);
            if (currentPD[check] == true)
                activeNeighbors++;
            if (activeNeighbors > 3)
                break;
        }

        if (point.second == false && activeNeighbors == 3)
            point.second == true;
        else if (point.second == true && (activeNeighbors == 2 || activeNeighbors == 3))
            point.second == true;
        else
            point.second == false;
    }
}