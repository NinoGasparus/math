#include <climits>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <iostream>
#include "bigNumber.h"
void printNumber(uint64_t* number, int chunks){

}
int main(int argc, char* argv[]) {


  bigNumber* A = new bigNumber();
  bigNumber* b = new bigNumber();
  bigNumber* c = new bigNumber();
  A->init();
  b->init();
  c->init();

 A->loadFile("Checks/number1");
 b->loadFile("Checks/number1");

  c->loadStr("1");
  
  
  //std::cout << A->blockCount;
  //printMem(*A); 
    


  bigAdd(A, b, c);
    
/*
  printMem(*b);
  printf("\n");
  printMem(*c);
  printf("\n");
*/
 printMem((*c));
  bigPrint(*c);

  printf("\n");
  return 0;
}
