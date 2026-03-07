#include <iostream>
#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include <bit>
#include "iniLib/ini.h"

/* Copyright 2025-2026 Maxwell Doose */
std::filesystem::path fileName;
bool helpArg = false;
bool shellArg = false;

class cpu;
class ppu;
extern cpu* primary;
extern ppu* graphics;

constexpr std::array<std::string, 12> expectedExtensions
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
#ifndef _WIN32
    std::println("emu65\nCopyright 2026 Maxwell Doose");
#else
    std::println("emu65\n\rCopyright 2026 Maxwell Doose");
#endif

    if ((argc == 1) or (!chkFilePresence(passedArgs)))
    {
        std::println("Fatal: No file to run (run with -h for help)");
        return 1;
    }
    if (helpArg)
    {
#ifndef _WIN32
        std::println("Usage: emu65 [-h] | [-s]\n-h: Print help message to the console\n-s: Enter shell mode");
#else
        std::println("Usage: emu65 [-h] | [-s]\r\n-h: Print help message to the console\r\n-s: Enter shell mode");
#endif
        return 0;
    }
    else if (shellArg)
    {
        return shell();
    }
    std::println("Loading {} . . .", static_cast<std::string>(fileName.filename()));
    if (!std::filesystem::exists(fileName))
    {
        std::println("Fatal: File {} doesn't exist", static_cast<std::string>(fileName.filename()));
        return 2;
    }
    if (!chkValidExtension(fileName))
    {
        std::println("Fatal: File {} has invalid extension", static_cast<std::string>(fileName.filename()));
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
    uint8_t where = 0;
    static uint8_t whereRet;
    bool fileFound = false;
    for (const std::string& str : argVec)
    {
        if (where == 0)
        {
            where++;
            continue;
        }
        if (str.starts_with('-') or str.starts_with('/')) // Prevents warnings relating to comparing constant operands with a logical or
        {
            where++;
            if (str == "-h" or "/h")
            {
                helpArg = true;
                return true;
            }
            else if (str == "-s" or "/s")
            {
                shellArg = true;
                return true;
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
