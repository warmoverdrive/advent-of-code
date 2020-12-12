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
int RunProgramUntilLoop(std::vector<Instruction> &program);

int main()
{
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day8Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    int result = CompileAndRun(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "ACC value before loop: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

int CompileAndRun(std::vector<std::string> &input)
{
    std::vector<Instruction> program{};
    CompileProgram(input, program);

    return RunProgramUntilLoop(program);
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

int RunProgramUntilLoop(std::vector<Instruction> &program)
{
    int acc{};
    size_t index{};

    while (true)
    {
        try
        {
            if (program.at(index).inst == "acc")
            {
                if (++program.at(index).iteration == 2)
                    break;
                acc += program.at(index).value;
                index++;
            }
            else if (program.at(index).inst == "jmp")
            {
                if (++program.at(index).iteration == 2)
                    break;
                index += program.at(index).value;
            }
            else if (program.at(index).inst == "nop")
            {
                if (++program.at(index).iteration == 2)
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

    return acc;
}