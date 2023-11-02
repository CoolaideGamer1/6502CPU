#include "src/CPU.h"
#include <iostream>

int main() {
  Mem mem;
  CPU cpu;
  mem[0xFFFC] = cpu.LDA_AB;
  mem[0xFFFD] = 12;
  mem[0xFFFE] = 1;
  cpu.Execute(4, mem);
  return 0;
}