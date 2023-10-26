#include <iostream>
#include "src/CPU.h"

int main() {
  Mem mem;
  CPU cpu;
  cpu.Init();
  mem[0xFFFC] = cpu.LDA_IMM;
  mem[0xFFFD] = 10;
  mem[0xFFFE] = cpu.TAX_IM;
  cpu.Execute(4, mem);
  return 0;
}