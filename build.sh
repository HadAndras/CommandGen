#!/bin/bash

# Get the list of source and header files in the src directory
files=$(ls src/*.c src/*.h)
# Compile all source and header files using gcc
gcc $files -o CommandGen.exe

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful! CommandGen.exe is created."
else
    echo "Build failed! Please check the compilation errors."
fi