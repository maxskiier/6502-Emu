#include <iostream>
#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include "logic.hpp"
#include "mINI/ini.h"

/* Copyright 2025-2026 Maxwell Doose */
std::filesystem::path fileName;
static std::string specificArg;
static constexpr std::array<std::string,12> expectedExtensions
{
    ".bin",
    ".obj",
    ".prg",
    ".o65",
    ".rom",
    ".hex",
    ".neo",
    ".abs",
    ".com",
    ".p00",
    ".nes",
    ".obj"
};

bool chkFilePresence(std::vector<std::string> argVec);
bool chkValidExtension(std::filesystem::path file);
int8_t shell();

int main(int argc, char* argv[])
{
    std::vector<std::string> passedArgs(argv, argv + argc);
    std::println("6502 Emulator\nCopyright 2026 by Maxwell Doose");
    if ((argc == 1) or (!chkFilePresence(passedArgs)))
    {
        std::println("Fatal: No file to run (run with -h for help)");
        return 1;
    }
    if (specificArg == "-s" or "/s")
    {
        shell();
    }
    if (!std::filesystem::exists(fileName))
    {
        std::println("Fatal: File {} doesn't exist", static_cast<std::string>(fileName));
        return 2;
    }
    if (!chkValidExtension(fileName))
    {
        std::println("Fatal: File {} has invalid extension", static_cast<std::string>(fileName));
        char gotChar;
        std::println("Valid extensions: ");
        for (const auto& ext : expectedExtensions)
        {
            std::println("{}", ext);
        }
        return 3;
    }
    return 0;
}

bool chkFilePresence(std::vector<std::string> argVec)
{
    uint8_t where = 1;
    static uint8_t whereRet;
    bool fileFound = false;
    for (const std::string& str : argVec)
    {
        if (str.starts_with('-' or '/'))
        {
            where++;
            if (str.starts_with("-h" or "/h" or "-s" or "/s"))
            {
                specificArg = str;
                fileFound = true;
                return fileFound;
            }
            continue;
        }

        fileName = static_cast<std::filesystem::path>(str);
        fileFound = true;
        whereRet = where;
        where++;
    }
    return fileFound;
}

bool chkValidExtension(std::filesystem::path file)
{
    std::string ext;
    {
        std::string getExt = file.extension().string();
        std::transform(getExt.begin(), getExt.end(), getExt.begin(), ::tolower);
        ext = getExt;
    }
    return std::find(expectedExtensions.begin(), expectedExtensions.end(), ext) != expectedExtensions.end();
}

int8_t shell()
{
    return 0;
}
