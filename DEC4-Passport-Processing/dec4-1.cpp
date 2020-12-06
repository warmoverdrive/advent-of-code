#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

// Input with help from @b0guslaw
std::vector<std::string> ProcessInput();
bool IsPassportValid(const std::string &passport);

//	Check passports for validity
//	Valid passports have all 7 fields below:
//	byr || iyr || eyr || hgt || hcl || ecl || pid
//
//	Valid passports can optionally have:
//	cid
//
//	data input is a key:value pair
//
//	parse all input, create individual passports
//	for each passport:
//		find ' '
//		create substring 3 chars after result
//		store substring in vector (keys)
//		loop until find == string::npos
//		check if keys has 8 values - if so its valid
//		check if keys has 7 values
//		if so, check if one is cid - if cid is in there, it is invalid

int main()
{
	std::vector<std::string> passports = ProcessInput();
	size_t result{};

	auto start = std::chrono::high_resolution_clock::now();
	for (auto passport : passports)
	{
		if (IsPassportValid(passport))
			result++;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Total Passports: " << passports.size() << '\n';
	std::cout << "Valid Passports: " << result << '\n';
	std::cout << "Process time: " << duration << "ms\n";
}

std::vector<std::string> ProcessInput()
{
	std::ifstream infile("PuzzleInput/Day4Input.txt");

	std::vector<std::string> data;
	std::string passport;

	for (std::string line; std::getline(infile, line);)
	{
		if (line.empty())
		{
			data.push_back(passport);
			passport.clear();
		}
		if (infile.eof())
		{
			passport += line;
			data.push_back(passport);
		}
		passport += line;
		passport += " ";
	}
	return data;
}

bool IsPassportValid(const std::string &passport)
{
	bool isValid{false};
	std::vector<std::string> keys{};

	// get first substring. Product of proper parsing
	// is an extra ' ' at the begining of passports
	// This if/else catches edge cases at the begining
	std::size_t found = passport.find(' ');
	if (found == 0)
		keys.push_back(passport.substr(1, 3));
	else
	{
		keys.push_back(passport.substr(0, 3));
		found = 0;
	}

	while (found <= passport.size())
	{
		found = passport.find(' ', ++found);
		if (found >= passport.size() - 1)
			break;
		else
			keys.push_back(passport.substr(found + 1, 3));
	}

	if (keys.size() == 8)
		isValid = true;
	else if (keys.size() == 7)
	{
		// Check if "cid" is present
		if (std::find(keys.begin(), keys.end(), "cid") != keys.end())
			isValid = false;
		else
			isValid = true;
	}
	else
		isValid = false;

	return isValid;
}