#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

// Input with help from @b0guslaw
std::vector<std::string> ProcessInput();
bool IsPassportValid(const std::string &passport);
bool CheckValidFields(const std::string &passport);
bool IsInRange(const std::string &input, size_t lowBound, size_t highBound);
bool IsValidHairColor(const std::string &input);
bool IsValidEyeColor(const std::string &input);
bool IsPassportID(const std::string &input);

//	Check passports for validity
//	Valid passports have all 7 fields below:
//	byr || iyr || eyr || hgt || hcl || ecl || pid
//
//	Valid passports can optionally have:
//	cid
//
//	data input is a key:value pair

//	parse all input, create individual passports
//	for each passport:
//		find ' '
//		create substring 3 chars after result
//		store substring in vector (keys)
//		loop until find == string::npos
//		check if keys has 8 values - if so its valid
//		check if keys has 7 values
//		if so, check if one is cid - if cid is in there, it is invalid

//  Part 2: Validate all fields of valid passports

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
        isValid = CheckValidFields(passport);
    else if (keys.size() == 7)
    {
        // Check if "cid" is present
        if (std::find(keys.begin(), keys.end(), "cid") != keys.end())
            isValid = false;
        else
            isValid = CheckValidFields(passport);
    }
    else
        isValid = false;

    return isValid;
}

bool CheckValidFields(const std::string &passport)
{
    bool isValid{false};

    std::stringstream sstream;
    std::string input;

    sstream << passport;

    while (sstream >> input)
    {
        if (input.substr(0, 3) == "byr")
            isValid = IsInRange(input.substr(4, std::string::npos), 1920, 2002);
        else if (input.substr(0, 3) == "iyr")
            isValid = IsInRange(input.substr(4, std::string::npos), 2010, 2020);
        else if (input.substr(0, 3) == "eyr")
            isValid = IsInRange(input.substr(4, std::string::npos), 2020, 2030);
        else if (input.substr(0, 3) == "hgt")
        {
            if (input.substr(input.size() - 2, std::string::npos) == "cm")
                isValid = IsInRange(input.substr(4, input.size() - 3), 150, 193);
            else
                isValid = IsInRange(input.substr(4, input.size() - 3), 59, 76);
        }
        else if (input.substr(0, 3) == "hcl")
            isValid = IsValidHairColor(input.substr(4, std::string::npos));
        else if (input.substr(0, 3) == "ecl")
            isValid = IsValidEyeColor(input.substr(4, std::string::npos));
        else if (input.substr(0, 3) == "pid")
            isValid = IsPassportID(input.substr(4, std::string::npos));
        else if (input.substr(0, 3) == "cid")
            continue;
        else
            isValid = false;

        if (isValid == false)
            break;
    }
    sstream.clear();

    return isValid;
}

bool IsInRange(const std::string &input, size_t lowBound, size_t highBound)
{
    size_t num = stoi(input);
    return (num >= lowBound && num <= highBound);
}

bool IsValidHairColor(const std::string &input) // Valid input is #xxxxxx <- x = 0-9 or a-f
{
    if (input.size() == 7 && input.at(0) == '#')
    {
        for (size_t i{1}; i < input.size(); i++)
        {
            if (input.at(i) >= 'a' && input.at(i) <= 'f')
                continue;
            else if (input.at(i) >= '0' && input.at(i) <= '9')
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool IsValidEyeColor(const std::string &input)
{
    if (input == "amb" || input == "blu" || input == "brn" ||
        input == "gry" || input == "grn" || input == "hzl" || input == "oth")
        return true;
    else
        return false;
}

bool IsPassportID(const std::string &input) // check if 9 length string of numbers
{                                           // including leading 0s
    if (input.size() == 9)
    {
        for (char digit : input)
        {
            if (isdigit(digit))
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}