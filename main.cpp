#include <cstring>
#include <cstdint>
#include <cmath>
#include "bigNumber.h"
void printNumber(uint64_t* number, int chunks){

}
int main(int argc, char* argv[]) {

  std::string number = argv[1];
  bigNumber* B = new bigNumber();
  
  B->init();
  B->loadStr(number);
  printMem(*B);
  printf("\n");
  B->extend(10, false);
  B->extend(3, true);
  printMem(*B);
  return 0;
}

