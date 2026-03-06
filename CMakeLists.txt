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
)
target_compile_options(6502Emulator PRIVATE -v)

include(GNUInstallDirs)
install(TARGETS 6502Emulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
