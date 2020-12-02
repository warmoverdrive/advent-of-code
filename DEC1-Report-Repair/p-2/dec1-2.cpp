#include <iostream>
#include <vector>
#include <chrono>
#include "../../headers/Inputv1.h"

void NestedLoopSearch(const std::vector<int> &data, int &results);
void HashSearch(const std::vector<int> &data, int &results);

int main()
{
    Input in("PuzzleInput/Day1Input.txt", '\n', Mode::INTEGER);

    std::vector<int> expense_report = in.idata;

    //	example data
    //    std::vector<int> expense_report{1721, 979, 366, 299, 675, 1456};

    int result = 0;

    auto start = std::chrono::high_resolution_clock::now();
    NestedLoopSearch(expense_report, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Nested Loop found " << result << " after " << duration << "ms\n";
    return 0;
}

void NestedLoopSearch(const std::vector<int> &data, int &results)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = i + 1; j < data.size(); j++)
        {
            for (size_t k = j + 1; k < data.size(); k++)
            {
                if (data.at(i) + data.at(j) + data.at(k) == 2020)
                {
                    results = data.at(i) * data.at(j) * data.at(k);
                    break;
                }
            }
            if (results != 0)
                break;
        }
        if (results != 0)
            break;
    }
}