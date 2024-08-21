#include <stdio.h>
#include <bitset>
#include <iostream>
int main(){
  char*  mem = new char[100];



  int x = 1;
  x = 1 << 31;
  int y = ~0 &  ~ x;
  std::cout << "bit " <<std::bitset<32>(x) << '\n'; 
  std::cout << "bit " <<std::bitset<32>(y); 
 

  printf("\n X = %d", x);
  printf("\n Y = %d\n", y);
  delete[] mem;
  return 0;
}
