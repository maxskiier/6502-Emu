cmake_minimum_required(VERSION 3.16)

project(6502Emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(6502Emulator main.cpp
    headers/logic.hpp
    headers/addrSpace.hpp
    headers/ppu.hpp
    headers/baseEngine.hpp
    headers/cpu.hpp
    implementations/baseEngine.cpp
    implementations/cpu.cpp
    implementations/logic.cpp
    implementations/ppu.cpp
    implementations/addrSpace.cpp
    headers/engineImplementations/win32.hpp
    headers/engineImplementations/wayland.hpp
    CONTRIBUTING.md
)

include(GNUInstallDirs)
install(TARGETS 6502Emulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
