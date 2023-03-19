#!/bin/bash
cd ..
python3 assembler_code/translator.py tests_codes/syracuse.txt storage/traduced_file.bin
gcc -o VM_in_c/ISS VM_in_c/ISS.c
./VM_in_c/ISS storage/traduced_file.bin storage/data_suite.bin

#Script pour lancer l'ensemble du programme.
