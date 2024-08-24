#include <chrono>
#include <fstream>
#include <iostream>
#include <mpfr.h>
#include <cstring>
#include <gmp.h>

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string number;
    file >> number;
    file.close();

    auto start = std::chrono::high_resolution_clock::now();

    const char *input = number.c_str();

    int decimal_digits = std::strlen(input);
    mpfr_prec_t precision = static_cast<mpfr_prec_t>(decimal_digits * 3.32);

    mpfr_t num;
    mpfr_init2(num, precision);
    mpfr_set_str(num, input, 10, MPFR_RNDN);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    mpfr_clear(num);

    return 0;
}

