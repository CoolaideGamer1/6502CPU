#include <iostream>

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
  uint8 AC;
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
  static constexpr uint LDA_ABX = 0xBD;
  static constexpr uint8 LDA_ABY = 0xB9;
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
    AC = 0;
    X = 0;
    Y = 0;
  }

  void Execute(uint32 Cycles, Mem &memory) {
    SR sr;
    while (Cycles > 0) {
      uint8 Ins = FetchUINT8(Cycles, memory);
      switch (Ins) {
        // LDA Instructions
      case LDA_IMM: {
        uint8 Value = FetchUINT8(Cycles, memory);
        AC = Value;
        sr.Z = (AC == 0);
        sr.N = (AC & 0b0000000) > 0;
      } break;
      case LDX_IMM: {
        uint8 Value = FetchUINT8(Cycles, memory);
        X = Value;
        sr.Z = (AC == 0);
        sr.N = (AC & 0b0000000) > 0;
      }
      case LDY_IMM: {
        uint8 Value = FetchUINT8(Cycles, memory);
        X = Value;
        sr.Z = (AC == 0);
        sr.N = (AC & 0b0000000) > 0;
      }
      case TAX_IM: {
        X = AC;
        Cycles--;
        sr.Z = (AC == 0);
        sr.N = (AC & 0b0000000) > 0;
      }
      default: {
        std::cout << "No Instruction Found" << std::endl;
      }
      }
    }
  }
};