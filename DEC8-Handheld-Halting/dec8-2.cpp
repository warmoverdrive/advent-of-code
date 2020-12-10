#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "../headers/Inputv4.h"

struct Instruction
{
    std::string inst;
    int value;
    size_t iteration;

    Instruction(std::string _inst, int _value)
        : inst{_inst}, value{_value}, iteration{} {}
};

// Prototypes
int CompileAndRun(std::vector<std::string> &input);
void CompileProgram(std::vector<std::string> &input, std::vector<Instruction> &target);
int FixProgram(std::vector<Instruction> &program);
bool RunProgramUntilLoop(std::vector<Instruction> program, int &acc);

int main()
{
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day8Test.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    int result = CompileAndRun(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "ACC value: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

int CompileAndRun(std::vector<std::string> &input)
{
    std::vector<Instruction> program{};
    CompileProgram(input, program);

    return FixProgram(program);
}

void CompileProgram(std::vector<std::string> &input, std::vector<Instruction> &target)
{
    std::stringstream sstream;
    std::string instruction{};
    int value{};
    for (std::string s : input)
    {
        sstream.str(s);
        sstream >> instruction >> value;
        sstream.clear();
        Instruction i = Instruction(instruction, value);
        target.push_back(i);
    }
}
/* === ISSUE : Need to ranged-loop with References to instructions vs Values */
int FixProgram(std::vector<Instruction> &program)
{
    int acc{};
    int iter{};
    for (Instruction i : program)
    {
        if (i.inst == "acc")
        {
            if (RunProgramUntilLoop(program, acc) == true)
            {
                std::cout << "Broken Operation Found! " << i.inst << "::" << i.value << '\n';
                break;
            }
        }
        else if (i.inst == "nop")
        {
            i.inst = "jmp";
            std::cout << "was nop is now: " << i.inst << '\n';
            if (RunProgramUntilLoop(program, acc) == true)
            {
                std::cout << "Broken Operation Found! " << i.inst << "::" << i.value << '\n';
                break;
            }
            else
                i.inst = "nop";
        }
        else if (i.inst == "jmp")
        {
            i.inst = "nop";
            std::cout << "was jmp is now: " << i.inst << '\n';
            if (RunProgramUntilLoop(program, acc) == true)
            {
                std::cout << "Broken Operation Found! " << i.inst << "::" << i.value << '\n';
                break;
            }
            else
                i.inst = "jmp";
        }
        iter++;
    }
    std::cout << "iterations: " << iter << " :: size of program: " << program.size() << '\n';

    return acc;
}

bool RunProgramUntilLoop(std::vector<Instruction> program, int &acc)
{
    size_t index{};
    acc = 0;

    while (true)
    {
        if (index >= program.size())
        {
            std::cout << "Program Complete!" << '\n';
            return true;
        }
        try
        {
            if (program.at(index).inst == "acc")
            {
                if (++program.at(index).iteration >= 2)
                    break;
                acc += program.at(index).value;
                index++;
            }
            else if (program.at(index).inst == "jmp")
            {
                if (++program.at(index).iteration >= 2)
                    break;
                index += program.at(index).value;
            }
            else if (program.at(index).inst == "nop")
            {
                if (++program.at(index).iteration >= 2)
                    break;
                index++;
            }
            else
            {
                std::cout << "Error, unrecognized operation!" << '\n';
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Program Error: " << e.what() << '\n';
            break;
        }
    }

    return false;
}