cmake_minimum_required(VERSION 3.16)

project(6502Emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(6502Emulator main.cpp
    logic.hpp
    csv/opcodes.csv
    settings.ini)

include(GNUInstallDirs)
install(TARGETS 6502Emulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
