#!/bin/bash
python3 assembler_code/translator.py tests_codes/assembleur.txt storage/traduced_file.bin
gcc -o VM_in_c/ISS VM_in_c/ISS.c
./VM_in_c/ISS storage/traduced_file.bin storage/data.bin

#Script pour lancer l'ensemble du programme.
