#!/bin/bash

input_files=("number1" "number5" "number10" "number50" "number100" "number500" "number1000" "number5000" "number10000")
echo "GPM run"
for input_file in "${input_files[@]}"; do
    ./test "$input_file" &   
    wait
done
echo  "DIY run"
for input_file in "${input_files[@]}"; do
    ./math.program "$input_file" &
    wait
done

