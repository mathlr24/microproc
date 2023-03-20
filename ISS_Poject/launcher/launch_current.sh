#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 arg1 arg2"
    echo "arg1 : assembler file to translate"
    echo "arg2 : name of the data file"
    exit 1
fi

cd ..			#We go back to the parent directory
python3 assembler_code/translator.py $1 storage/traduced_file.bin
gcc -o VM_in_c/ISS VM_in_c/ISS.c
./VM_in_c/ISS storage/traduced_file.bin $2

#Script to launch the whole program.
