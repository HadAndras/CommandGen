cmake_minimum_required(VERSION 3.31)
project(CommandGen_main C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(CommandGen_main
        src/command.c
        src/command.h
        src/main.c
        src/main.h
        src/prompt.c
        src/prompt.h
        src/ReadingMode.c
        src/ReadingMode.h
        src/ReadCommands.c
        src/ReadCommands.h
)
