#include "../headers/logic.hpp"

namespace logic
{

std::string iniInterface::readSettingsINISection(std::string section, std::string key)
{

}
std::string iniInterface::readOpcodesINISection(std::string section, std::string key)
{
    std::string& getOp = opcodes[section][key];
    return getOp;
}
iniInterface ini;
}
