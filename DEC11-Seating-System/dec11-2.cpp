#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include "../headers/Inputv4.h"

size_t SimulateSeating(std::vector<std::string> &currentSeats);
void CheckAllVisibleSeats(std::map<char *, std::map<char *, char *>> &seatMap);
bool HasSeatingChanged(const std::vector<std::string> &currentSeats, const std::vector<std::string> &lastSeats);
std::map<char *, std::map<char *, char *>> *GenerateSeatMap(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats);
void FindVisibleSeats(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats, std::map<char *, std::map<char *, char *>> &seatmap, int col, int row);
void SearchDirection(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats, std::map<char *, char *> &visSeats, std::vector<int> dir, int col, int row);
size_t CountOccupiedSeats(const std::vector<std::string> &currentSeats);

const std::vector<std::vector<int>> deltaXY{
    {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

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

size_t SimulateSeating(std::vector<std::string> &currentSeats)
{
    std::vector<std::string> lastSeats(currentSeats);
    //Pre-generate map of seats that CAN change nad set seats that CANT
    std::map<char *, std::map<char *, char *>> seatMap(*GenerateSeatMap(currentSeats, lastSeats));

    do
    {
        for (size_t y{}; y < currentSeats.size(); y++)
            for (size_t x{}; x < currentSeats.at(y).size(); x++)
                lastSeats[y][x] = currentSeats[y][x];

        CheckAllVisibleSeats(seatMap);

    } while (HasSeatingChanged(currentSeats, lastSeats));

    return CountOccupiedSeats(currentSeats);
}

void CheckAllVisibleSeats(std::map<char *, std::map<char *, char *>> &seatMap)
{
    int takenSeats{};
    for (auto seat : seatMap)
    {
        for (auto neighbor : seat.second)
        {
            if (*neighbor.second == 35)
                takenSeats++;
        }

        if (takenSeats == 0)
        {
            *seat.first = 35;
        }
        else if (*seat.first == 35 && takenSeats >= 5)
        {
            *seat.first = 76;
        }
        takenSeats = 0;
    }
}

bool HasSeatingChanged(const std::vector<std::string> &currentSeats, const std::vector<std::string> &lastSeats)
{
    for (size_t col{}; col < currentSeats.size(); col++)
    {
        for (size_t row{}; row < currentSeats.at(col).size(); row++)
        {
            if (currentSeats.at(col).at(row) != lastSeats.at(col).at(row))
                return true;
        }
    }
    return false;
}

std::map<char *, std::map<char *, char *>> *GenerateSeatMap(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats)
{
    static std::map<char *, std::map<char *, char *>> seatMap;

    for (size_t col{}; col < currentSeats.size(); col++)
    {
        for (size_t row{}; row < currentSeats.at(col).size(); row++)
        {
            if (currentSeats.at(col).at(row) == '.')
                continue;
            else if (currentSeats.at(col).at(row) == 'L' || currentSeats.at(col).at(row) == '#')
                FindVisibleSeats(currentSeats, lastSeats, seatMap, col, row);
        }
    }

    return &seatMap;
}

void FindVisibleSeats(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats, std::map<char *, std::map<char *, char *>> &seatmap, int col, int row)
{
    std::map<char *, char *> visSeats{};
    for (auto dir : deltaXY)
    {
        SearchDirection(currentSeats, lastSeats, visSeats, dir, col, row);
    }
    if (visSeats.size() >= 5)
        seatmap.insert({&currentSeats.at(col).at(row), visSeats});
    else
    {
        currentSeats.at(col).at(row) = '#';
    }
}

void SearchDirection(std::vector<std::string> &currentSeats, std::vector<std::string> &lastSeats, std::map<char *, char *> &visSeats, std::vector<int> dir, int col, int row)
{
    int searchCol{col + dir[1]}, searchRow{row + dir[0]};

    while ((searchCol >= 0 && searchCol < currentSeats.size()) &&
           (searchRow >= 0 && searchRow < currentSeats.at(col).size()))
    {
        if (currentSeats.at(searchCol).at(searchRow) == 'L' ||
            currentSeats.at(searchCol).at(searchRow) == '#')
        {
            visSeats.insert({&currentSeats.at(searchCol).at(searchRow), &lastSeats.at(searchCol).at(searchRow)});
            return;
        }
        else
        {
            searchCol += dir[1];
            searchRow += dir[0];
        }
    }
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