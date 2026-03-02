#include <iostream>
#include <print>
#include <fstream>
#include "logic.hpp"
#include "mINI/ini.h"

/* Copyright 2025-2026 Maxwell Doose */

int main(int argc, char* argv[])
{
    std::vector<std::string> passedArgs(argv, argv + argc);
    std::println("6502 Emulator\nCopyright 2026 by Maxwell Doose");
    if (argc == 1)
    {
        std::println("Fatal: No file to run (run with -h or --help for help)");
        return 1;
    }
    return 0;
}
