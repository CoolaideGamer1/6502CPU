#include "src/CPU.h"
#include <iostream>

int main() {
  Mem mem;
  CPU cpu;
  
  mem[0xFFFC] = cpu.op.LDA_IMM;
  mem[0xFFFD] = 12;
  cpu.Init();
  cpu.Execute(2, mem);
  return 0;
}