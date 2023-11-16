#include "src/CPU.h"
#include <iostream>

int main() {
  Mem mem;
  CPU cpu;
  cpu.Init(2);
  mem[0xFFFC] = 0xA9;
  mem[0xFFFD] = 12;
  cpu.Execute(2, mem);
  return 0;
}