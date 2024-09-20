#!/bin/bash

nasm -f  elf64 over.asm  -o  over.o
g++ -c test3.cpp -o main.o
g++ main.o  over.o  -o main


