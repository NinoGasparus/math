#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <cstdint>
#include <cmath>
uint64_t betterPOW(int exp) {
    uint64_t base = 1;
    for (int i = 0; i < exp; i++) {
        base *= 10;
    }
    return base;
}

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string number;
    file >> number;
    file.close();

    auto start = std::chrono::high_resolution_clock::now();
    int blockCount = std::floor(number.size() / 19) + 1;

    uint64_t* memory = new uint64_t[blockCount];
    std::memset(memory, 0, blockCount * sizeof(uint64_t));

    char* d10Word = new char[number.size()];
    for (size_t i = 0; i < number.size(); i++) {
        d10Word[i] = number[i] - '0';
    }

    // Length of the number
    uint64_t asizee = number.size();

    // Current buffer being written to
    int bufIndex = 0;
    // Exponent
    int exp = 0;

    for (int i = 0; i < (int)asizee / 19 + 1; i++) {
        int chunkSize = 19;
        if (i * 19 + 19 > asizee - 1) {
            chunkSize = asizee - i * 19;
        }
        for (int j = 0; j < chunkSize; j++) {
            memory[bufIndex] += betterPOW(exp) * d10Word[(asizee - 1) - (i * 19 + j)];
            exp++;
        }
        exp = 0;
        bufIndex++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    delete[] memory;
    delete[] d10Word;

    return 0;
}

