#include <iostream>
#include <print>
#include "cpu.hpp"
#include "addrSpace.hpp"



int main(int argc, char* argv[])
{
    std::vector<std::string> passedArgs(argv, argv + argc);
    if (argc == 1)
    {
        std::println("6502 Emulator\nCopyright 2026 by Maxwell Doose\nStart by passing a file to run (must be 65536 bytes/64Kib).");
        return 0;
    }
    return 0;
}
