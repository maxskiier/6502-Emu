#include <iostream>
#include <print>
#include <fstream>
#include "logic.hpp"

/* Copyright 2025-2026 Maxwell Doose */

int main(int argc, char* argv[])
{
    std::vector<std::string> passedArgs(argv, argv + argc);
    if (argc == 1)
    {
        std::println("6502 Emulator\nCopyright 2026 by Maxwell Doose\nStart by passing a file to run (must be 32768 bytes/32KiB).");
        return 1;
    }
    return 0;
}
