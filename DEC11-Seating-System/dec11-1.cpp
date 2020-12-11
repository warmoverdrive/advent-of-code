#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "../headers/Inputv4.h"

size_t SimulateSeating(std::vector<std::string> currentSeats);
size_t CountOccupiedSeats(const std::vector<std::string> &currentSeats);
std::vector<std::string> RunSimulation(std::vector<std::string> currentSeats);
char CheckNeighbors(const std::vector<std::string> &currentSeats, int row, int col);
bool HasSeatingChanged(const std::vector<std::string> &currentSeats, const std::vector<std::string> &lastSeats);

int main()
{
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day11Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    size_t result = SimulateSeating(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\nOccupied Seats: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

size_t SimulateSeating(std::vector<std::string> currentSeats)
{
    std::vector<std::string> lastSeats{};

    do
    {
        lastSeats.clear();
        for (auto r : currentSeats)
            lastSeats.push_back(r);

        currentSeats = RunSimulation(currentSeats);

        std::cout << '.';
    } while (HasSeatingChanged(currentSeats, lastSeats) == true);

    return CountOccupiedSeats(currentSeats);
}

size_t CountOccupiedSeats(const std::vector<std::string> &currentSeats)
{
    size_t occupiedSeats{};
    for (std::string r : currentSeats)
    {
        for (char c : r)
        {
            if (c == '#')
                occupiedSeats++;
        }
    }

    return occupiedSeats;
}

std::vector<std::string> RunSimulation(std::vector<std::string> currentSeats)
{
    std::vector<std::string> newSeats(currentSeats);

    for (size_t row{}; row < currentSeats.size(); row++)
    {
        for (size_t col{}; col < currentSeats.at(row).size(); col++)
        {
            if (currentSeats.at(row).at(col) == '.')
                continue;
            else
                newSeats.at(row).at(col) = CheckNeighbors(currentSeats, row, col);
        }
    }

    return newSeats;
}

char CheckNeighbors(const std::vector<std::string> &currentSeats, int row, int col)
{
    char test = currentSeats.at(row).at(col);
    size_t adjOccupiedSeats{};

    for (int chkRow{row - 1}; chkRow <= row + 1; chkRow++)
    {
        for (int chkCol{col - 1}; chkCol <= col + 1; chkCol++)
        {
            if (chkCol == col && chkRow == row)
                continue; // skip checking current seat
            try
            {
                if (currentSeats.at(chkRow).at(chkCol) == '#')
                    adjOccupiedSeats++;
            }
            catch (...)
            {
                continue;
            }
        }
    }

    if (test == 'L' && adjOccupiedSeats == 0)
        return '#';
    else if (test == '#' && adjOccupiedSeats >= 4)
        return 'L';
    else
        return test;
}

bool HasSeatingChanged(const std::vector<std::string> &currentSeats, const std::vector<std::string> &lastSeats)
{
    for (size_t row{}; row < currentSeats.size(); row++)
    {
        for (size_t col{}; col < currentSeats.at(row).size(); col++)
        {
            if (currentSeats.at(row).at(col) != lastSeats.at(row).at(col))
                return true;
        }
    }
    return false;
}