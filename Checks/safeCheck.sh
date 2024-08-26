#!/bin/bash

input_files=("number1" "number5" "number10" "number50" "number100" "number500" "number1000" "number5000" "number10000")

compute_hash() {
    local file=$1
    sha256sum "$file" | awk '{print $1}'
}

echo "DIY run"

for input_file in "${input_files[@]}"; do
    ./math.program "$input_file" > "${input_file}.check"
    
    number=$(cat "${input_file}.check")
    
    number_hash=$(echo -n "$number" | sha256sum | awk '{print $1}')
    check_file_hash=$(compute_hash "${input_file}.check")
    
    echo "Hash of the number: $number_hash"
    echo "Hash of the check file: $check_file_hash"
    
    if [ "$number_hash" == "$check_file_hash" ]; then
        echo "OK"
    else
        echo "FAILED"
    fi
    
    rm "${input_file}.check"
done

