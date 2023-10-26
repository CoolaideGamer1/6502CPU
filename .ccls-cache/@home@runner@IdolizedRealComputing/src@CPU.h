9#include <iostream>
#include <string>

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;

struct Mem {
  static const int max_mem = 1024 * 64;
  uint8 mem[max_mem];

  int address;
  int data;

  void Init() {
    for (int i = 0; i < max_mem; i++) {
      mem[i] = static_cast<uint8>(0);
    }
  }
  uint8 &operator[](uint32 Address) { return mem[Address]; }
  uint8 operator[](uint32 Address) const { return mem[Address]; }
};

struct CPU {
  Mem mem;

  // Registers
  uint16 PC;
  uint16 SP;
  uint8 A;
  uint8 X;
  uint8 Y;
  class SR {
  public:
    uint8 N : 1;
    uint8 V : 1;
    uint8 B : 1;
    uint8 D : 1;
    uint8 I : 1;
    uint8 Z : 1;
    uint8 C : 1;
  };

  // opcodes
  // TRANSFER INSTRUCTIONS
  static constexpr uint8 LDA_IMM = 0xA9;
  static constexpr uint8 LDA_ZP = 0xA5;
  static constexpr uint8 LDA_ZPX = 0xB5;
  static constexpr uint8 LDA_AB = 0xAD;
  static constexpr uint8 LDA_ABX = 0xBD;
  static constexpr uint8 LDA_ABY = 0xB9;
  static constexpr uint8 LDA_ZPXI = 0xA1;
  static constexpr uint8 LDA_ZPYI = 0xB1;
  // LDX (Load Register X with Memory)
  static constexpr uint8 LDX_IMM = 0xA2;
  static constexpr uint8 LDX_ZP = 0xA6;
  static constexpr uint8 LDX_ZPY = 0xB6;
  static constexpr uint8 LDX_AB = 0xAE;
  static constexpr uint8 LDX_ABY = 0xBE;
  // LDY (Load Register Y with Memory)
  static constexpr uint8 LDY_IMM = 0xA0;
  static constexpr uint8 LDY_ZP = 0xA4;
  static constexpr uint8 LDY_ZPX = 0xB4;
  static constexpr uint8 LDY_AB = 0xAC;
  static constexpr uint8 LDY_ABX = 0xBC;
  // STA (Store Accumulator in Memory)
  static constexpr uint8 STA_ZP = 0x85;
  static constexpr uint8 STA_ZPX = 0x95;
  static constexpr uint8 STA_AB = 0x8D;
  static constexpr uint8 STA_ABX = 0x9D;
  static constexpr uint8 STA_ABY = 0x99;
  // STX (Store Register X in Memory)
  static constexpr uint8 STX_AP = 0x86;
  static constexpr uint8 STX_ZPY = 0x96;
  static constexpr uint8 STX_AB = 0x8E;
  // STY (Store Register Y in Memory)
  static constexpr uint8 STY_AP = 0x84;
  static constexpr uint8 STY_ZPX = 0x94;
  static constexpr uint8 STY_AB = 0x8C;
  // TAX (Transfer Accumulator to Register X)
  static constexpr uint8 TAX_IM = 0xAA;
  // TAY (Transfer Accumulator to Register Y)
  static constexpr uint8 TAY_IM = 0xA8;
  // TSX (Transfer Stack Pointer to Register X)
  static constexpr uint8 TXS_IM = 0x9A;
  // TYA (Transfer Register Y to Accumulator)
  static constexpr uint8 TYA_IM = 0x98;

  // STACK INSTRUCTIONS
  // NEED TO ALL OTHER IMPLEMENT

  enum AModes {
    Implied,
    Accumulator,
    Immediate,
    Absolute,
    XIndexedAbsolute,
    YIndexedAbsolute,
    AbsoluteIndirect,
    ZeroPage,
    XIndexedZeroPage,
    YIndexedZeroPage,
    XIndexedZeroPageIndirect,
    ZeroPageIndirectYIndexed,
    Relative
  };

  int concat(int a, int b) {

    std::string s1 = std::to_string(a);
    std::string s2 = std::to_string(b);
    std::string s = s1 + s2;

    int c = std::stoi(s);

    return c;
  }

  // Instruction Implementation
  void LDA(AModes amode, uint32 &Cycles, Mem &memory) {
    SR sr;
    switch (amode) {
    case Immediate: {
      uint8 Address = FetchUINT8(Cycles, memory);
      A = Address;
      sr.Z = (A == 0);
      sr.N = (A & 0b0000000) > 0;
    } break;
    case Absolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      A = ReadUINT8(Address, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case XIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case YIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += Y;
      A = ReadUINT8(Address, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      A = ReadUINT8(Address, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case XIndexedZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case XIndexedZeroPageIndirect: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += X;
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address + 1, Cycles, memory);
      uint16 IndirectAddress = concat(HighAddr, LowAddr);
      A = ReadUINT8(IndirectAddress, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    case ZeroPageIndirectYIndexed: {
      uint8 Address = FetchUINT8(Cycles, memory);
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address + 1, Cycles, memory);
      uint16 IndirectAddress = concat(HighAddr, LowAddr) + Y;
      A = ReadUINT8(IndirectAddress, Cycles, memory);
      sr.Z = (A == 0);
      sr.N = (A & 0b10000000) > 0;
    } break;
    default: {
      std::cout << "No Addressing mode handled." << std::endl;
    }
    }
  }
  void LDX(AModes amode, uint32 &Cycles, Mem &memory) {
  SR sr;
  switch (amode) {
  case Immediate: {
      uint8 Address = FetchUINT8(Cycles, memory);
      X = Address;
      if(Address == 0){ sr.Z = 1; }
      sr.N = (X & 0b10000000) > 0;
  } break;
  case Absolute:{
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      X = ReadUINT8(Address, Cycles, memory);
      sr.Z = (X == 0);
      sr.N = (X & 0b10000000) > 0;
  } break;
  case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      X = ReadUINT8(Address, Cycles, memory);
      sr.Z = (X == 0);
      sr.N = (X & 0b10000000) > 0;
  } break;
  case YIndexedAbsolute:{
    uint8 LowAddr = FetchUINT8(Cycles, memory);
    uint8 HighAddr = FetchUINT8(Cycles, memory);
    X = concat(concat(HighAddr, LowAddr), Y);
    sr.Z = (X == 0);
    sr.N = (X & 0b10000000) > 0;
  } break;
  case YIndexedZeroPage:{
    uint8 Address = FetchUINT8(Cycles, memory);
    X = concat(Address, Y);
    sr.Z = (X == 0);
    sr.N = (X & 0b10000000) > 0;
  } break;
  default: {
      std::cout << "No Addressing mode handled." << std::endl;
  }
  }
}
  void LDY(AModes amode, uint32 &Cycles, Mem &memory){
    SR sr;
    switch (amode){
      case Immediate:{
        uint8 Address = FetchUINT8(Cycles, memory);
        Y = Address;
        sr.Z = (Y == 0);
        sr.N = (Y & 0b10000000) > 0;
      } break;
      case Absolute:{
        uint8 LowAddr = FetchUINT8(Cycles, memory);
        uint8 HighAddr = FetchUINT8(Cycles, memory);
        Y = concat(HighAddr, LowAddr);
        sr.Z = (Y == 0);
        sr.N = (Y & 0b10000000) > 0;
      } break;
      case XIndexedAbsolute:{
        uint8 LowAddr = FetchUINT8(Cycles, memory);
        uint8 HighAddr = FetchUINT8(Cycles, memory);
        Y = concat(HighAddr, LowAddr) + X;
        sr.Z = (Y == 0);
        sr.N = (Y & 0b10000000) > 0;
      } break;
      case ZeroPage:{
        uint8 Address = FetchUINT8(Cycles, memory);
        Y = ReadUINT8(Address, Cycles, memory);
        sr.Z = (Y == 0);
        sr.N = (Y & 0b10000000) > 0;
      } break;
      case XIndexedZeroPage:{
        uint8 Address = FetchUINT8(Cycles, memory);
        Y = concat(Address, X);
        sr.Z = (X == 0);
        sr.N = (X & 0b10000000) > 0;
      } break;
      default:{
        std::cout << "No Addressing mode handled." << std::endl;
      } 
    }
  }
  void STA(AModes amode, uint32 &Cycles, Mem &memory){
    SR sr;
    switch (amode){
      case Absolute:{
        uint8 HighAddr = FetchUINT8(Cycles, memory);
        uint8 LowAddr = FetchUINT8(Cycles, memory);
        uint16 Address = concat(HighAddr, LowAddr);
        Address = A;
      } break;
      default:{
        std::cout << "No Addressing mode handled." << std::endl;
      }
    }
  }

  uint8 FetchUINT8(uint32 &Cycles, Mem &memory) {
    uint8 Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
  }
  uint8 ReadUINT8(uint8 Address, uint32 &Cycles, Mem &memory) {
    uint8 Data = memory[Address];
    Cycles--;
    return Data;
  }

  void Init() {
    SR sr;
    mem.Init();
    PC = 0xFFFC;
    SP = 0x100;
    sr.C = sr.Z = sr.I = sr.D = sr.B = sr.V = sr.N = 0;
    A = X = Y = 0;
  }

  void Execute(uint32 Cycles, Mem &memory) {
    SR sr;
    while (Cycles > 0) {
      uint8 Ins = FetchUINT8(Cycles, memory);
      switch (Ins) {
        // LDA
      case LDA_IMM: {
        LDA(Immediate, Cycles, memory);
      } break;
      case LDA_ZP: {
        LDA(ZeroPage, Cycles, memory);
      } break;
      case LDA_ZPX: {
        LDA(XIndexedZeroPage, Cycles, memory);
      } break;
      case LDA_AB: {
        LDA(Absolute, Cycles, memory);
      } break;
      case LDA_ABX: {
        LDA(XIndexedAbsolute, Cycles, memory);
      } break;
      case LDA_ABY: {
        LDA(YIndexedAbsolute, Cycles, memory);
      } break;
      case LDA_ZPXI: {
        LDA(XIndexedZeroPageIndirect, Cycles, memory);
      } break;
      case LDA_ZPYI: {
        LDA(ZeroPageIndirectYIndexed, Cycles, memory);
      } break;
        // LDX
      case LDX_IMM:{
        LDX(Immediate, Cycles, memory);
      } break;
      case LDX_AB:{
        LDX(Absolute, Cycles, memory);
      } break;
      case LDX_ZP:{
        LDX(ZeroPage, Cycles, memory);
      } break;
      case LDX_ABY:{
        LDX(YIndexedAbsolute, Cycles, memory);
      } break;
      case LDX_ZPY:{
        LDX(YIndexedZeroPage, Cycles, memory);
      } break;
        // LDY
      case LDY_IMM:{
        LDY(Immediate, Cycles, memory);
      } break;
      case LDY_AB:{
        LDY(Absolute, Cycles, memory);
      } break;
      case LDY_ABX:{
        LDY(XIndexedAbsolute, Cycles, memory);
      } break;
      case LDY_ZP:{
        LDY(ZeroPage, Cycles, memory);
      } break;
      case LDY_ZPX:{
        LDY(XIndexedZeroPage, Cycles, memory);
      } break;
        //STA
        case STA_AB:{
          
        } break;
      default: {
        std::cout << "No Instruction Found" << std::endl;
      }
      }
    }
  }
};