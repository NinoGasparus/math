#!/bin/bash


cd build
nasm -f  elf64 ../addRegisters.asm  -o addRegisters.o

g++ -c -oo ../main.cpp -o main.o
g++ -c -oo ../bigNumber.cpp  -o bigNumber.o
g++ -c -oo ../bigFunctions.cpp -o bigFunctions.o
g++ addRegisters.o main.o bigNumber.o bigFunctions.o  -o ../math.program

#g++  -oo main.cpp bigNumber.cpp bigFunctions.cpp -o math.program
