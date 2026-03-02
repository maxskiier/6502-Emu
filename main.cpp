#include <iostream>
#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include "logic.hpp"
#include "mINI/ini.h"

/* Copyright 2025-2026 Maxwell Doose */
std::filesystem::path fileName;

bool chkFilePresence(std::vector<std::string> argVec);

int main(int argc, char* argv[])
{
    std::vector<std::string> passedArgs(argv, argv + argc);
    std::println("6502 Emulator\nCopyright 2026 by Maxwell Doose");
    if (argc == 1 or !chkFilePresence(passedArgs))
    {
        std::println("Fatal: No file to run (run with -h for help)");
        return 1;
    }
    return 0;
}

bool chkFilePresence(std::vector<std::string> argVec)
{
    static constexpr char argChar = '-';
    uint8_t where = 1;
    uint8_t whereRet;
    bool fileFound = false;
    for (const auto& str : argVec)
    {
        if (str.starts_with(!argChar))
        {
            fileName = static_cast<std::filesystem::path>(str);
            fileFound = true;
        }
        where++;
    }
    return fileFound;
}
