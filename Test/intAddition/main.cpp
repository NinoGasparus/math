#include <climits>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include "bigNumber.h"




//flags
//lf loads file into  a  and b
//la loads arguments into a and b 
  
int main(int argc, char* argv[]) {

  if(argc < 3){
    printf("not enough args\n");
    return 1;
  }

  
  bigNumber* a = new bigNumber();
  bigNumber* b = new bigNumber();
  bigNumber* c = new bigNumber();
  a->init();
  b->init();
  c->init();


  if(argv[1] == "-lf"){
    a->loadStr(argv[2]);
  }else{
    a->loadint(std::stoul(argv[2]));
  }

  if(argv[3] == "-lf"){
    b->loadStr(argv[4]);
  }else{
    b->loadint(std::stoul(argv[4]));
  }
  
  bigAdd(a, b, c);
  bigPrint(c);
  return 0;
}
