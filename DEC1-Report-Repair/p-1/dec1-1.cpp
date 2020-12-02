#include <iostream>
#include <vector>
#include "../../headers/Inputv1.h"

int main()
{
	//example data
	//std::vector<int> expense_report{1721, 979, 366, 299, 675, 1456};

	Input expense_report("PuzzleInput/Day1Input.txt", '\n', Mode::INTEGER);

	size_t result{};

	for (size_t i = 0; i < expense_report.idata.size(); i++)
	{
		for (size_t k = i + 1; k < expense_report.idata.size(); k++)
		{
			if (expense_report.idata.at(i) + expense_report.idata.at(k) == 2020)
			{
				result = expense_report.idata.at(i) * expense_report.idata.at(k);
				break;
			}
		}
		if (result != 0)
			break;
	}

	std::cout << result << '\n';
	return 0;
}