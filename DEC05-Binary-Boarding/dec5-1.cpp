#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "../headers/Inputv3.h"

/*	=== Input Specs === 
	Sample Input
	FBFBBFFRLR
	Input is sperated into 2 sections:
	First 7 Digits are for the Row, last 3 are for columns
	Breakdown as such:
	Total rows: 0-127
	1. F means lower half (0-63)	2. B means upper half (32-63)
	3. F means lower half (32-47)	4. B means uppfer half (40-47)
	5. B keeps upper rows 44-47		6. F keeps lower rows 44-45
	7. F keeps lower row, 44.
	Total columns: 0-7
	1. R takes upper half (4-7)		2. L takes lower half (4-5)
	3. R keeps upper column, 5

	Final result: Row 44, Column 5
	Seat ID = row * 8 + column
	44 * 8 + 5 = 357

	Goal: Input all boarding passes and determine the pass with the highest ID number
*/

size_t BinarySort(const std::string &string, size_t lowerBound, size_t upperBound);
size_t GetPassID(const std::string &pass);

int main()
{
	Input<std::string> in("PuzzleInput/Day5Input.txt", '\n');

	size_t highestID{};
	size_t seatID{};

	auto start = std::chrono::high_resolution_clock::now();
	for (auto pass : in.data)
	{
		seatID = GetPassID(pass);

		if (seatID > highestID)
			highestID = seatID;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Highest Seat ID: " << highestID << '\n';
	std::cout << "Found in: " << duration << "ms\n";
}

size_t GetPassID(const std::string &pass)
{
	size_t passID{};

	size_t row = BinarySort(pass.substr(0, 7), 0, 127);
	size_t column = BinarySort(pass.substr(7, std::string::npos), 0, 7);

	passID = row * 8 + column;

	return passID;
}

size_t BinarySort(const std::string &string, size_t lowerBound, size_t upperBound)
{
	size_t result{};
	size_t divisor{(upperBound + 1) / 2}; // procedurally get the divisor ie 128/2 = 64,
										  // so we can add or subtract from the bounds
										  //using this and divide by two afterwards
	// F and L = lower half			B and R = upper half
	for (char c : string)
	{
		if (c == 'F' || c == 'L')
		{
			upperBound -= divisor;
			divisor /= 2;
		}
		else if (c == 'B' || c == 'R')
		{
			lowerBound += divisor;
			divisor /= 2;
		}
	}

	if (string.at(string.size() - 1) == 'F' || string.at(string.size() - 1) == 'L')
		result = lowerBound;
	else
		result = upperBound;

	return result;
}