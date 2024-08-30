#include <cstring>
#include <cstdint>
#include <cmath>
#include <iostream>
#include "bigNumber.h"
void printNumber(uint64_t* number, int chunks){

}
int main(int argc, char* argv[]) {

  /*std::string number = argv[1];
  bigNumber* B = new bigNumber();
  
  B->init();
  B->loadStr(number);
  printMem(*B);


  printf("\n");
  B->extend(10, false);
  B->extend(3, true);
  printMem(*B); */

//  std::cout << getOverflow(0UL, 1231546);

  bigNumber* A = new bigNumber();
  bigNumber* b = new bigNumber();
  bigNumber* c = new bigNumber();
  A->init();
  b->init();
  c->init();

 // A->loadStr(argv[1]);
  //b->loadStr(argv[2]);
  //
  A->loadFile("Checks/number1");
  b->loadFile("Checks/number1");
  c->loadStr("1");
  /*printMem(*A);
  printf("\n");
  printMem(*b);
  printf("\n");
  printMem(*c);

  printf("\n");
  buffersEaqualize(A, b, c);
  printMem(*A);
  printf("\n");
  printMem(*b);
  printf("\n");
  printMem(*c);
  printf("\n");
  printf("\n");
  printf("\n");
  */
  bigAdd(A, b, c);

  //bigPrint(*A);
 // printf("\n");
  //bigPrint(*b);
 // printf("\n");
  bigPrint(*c);
  printf("\n");
  return 0;
}
