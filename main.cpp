#include <climits>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <iostream>
#include "bigNumber.h"





  
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
    printf("A = \n");
    bigPrint(*A);
    printf("\n");
    
    printf("B = \n");
    bigPrint(*b);  
    printf("\n");
  
    printf("C = \n");

    bigAdd(A, b, c);
    
/*
  printMem(*b);
  printf("\n");
  printMem(*c);
  printf("\n");
*/
 bigPrint(*c);
  //bigPrint(*c);

  printf("\n");
  return 0;
}
