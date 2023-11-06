#!/bin/bash
set -e

test_dir="./test"

# Compile all .vex files in the source directory and output to the destination directory
for file in $test_dir/*.vex
do
    if [ -f "$file" ]; then
        echo "Compiling $file"
        ./build/vex "$file" --print-ir
    fi
done