#include <iostream>
#include <string>

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;

struct opcodes {
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

  // TRANSFER INSTRUCTIONS

  // TAX (Transfer Accumulator to Register X)
  static constexpr uint8 TAX_IM = 0xAA;
  // TAY (Transfer Accumulator to Register Y)
  static constexpr uint8 TAY_IM = 0xA8;
  // TSX (Transfer Stack Pointer to Register X)
  static constexpr uint8 TSX_IM = 0xBA;
  // TYA (Transfer Register Y to Accumulator)
  static constexpr uint8 TXA_IM = 0x8A;
  // TXS (Transfer Index X To Stack Pointer)
  static constexpr uint8 TXS_IM = 0x9A;
  // TYA (Transfer Index Y To Accumulator)
  static constexpr uint8 TYA_IM = 0x98;

  // STACK INSTRUCTIONS

  // PHA (Push Accumulator On Stack)
  static constexpr uint8 PHA_IM = 0x48;
  // PHP (Push Processor Status On Stack)
  static constexpr uint8 PHP_IM = 0x08;
  // PLA (Pull Accumulator From Stack)
  static constexpr uint8 PLA_IM = 0x68;
  // PLP (Pull Processor Status From Stack)
  static constexpr uint8 PLP_IM = 0x28;

  // SHIFT INSTRUCTIONS

  // ASL (Arithmetic Shift Left)
  static constexpr uint8 ASL_A = 0x0A;
  static constexpr uint8 ASL_AB = 0x0E;
  static constexpr uint8 ASL_XIA = 0x1E;
  static constexpr uint8 ASL_ZP = 0x06;
  static constexpr uint8 ASL_XIZP = 0x16;
  // LSR (Logical Shfit Right)
  static constexpr uint8 LSR_A = 0x4A;
  static constexpr uint8 LSR_AB = 0x4E;
  static constexpr uint8 LSR_XIA = 0x5E;
  static constexpr uint8 LSR_ZP = 0x46;
  static constexpr uint8 LSR_XIZP = 0x56;
  // ROL (Rotate Left)
  static constexpr uint8 ROL_A = 0x2A;
  static constexpr uint8 ROL_AB = 0x2E;
  static constexpr uint8 ROL_ZIA = 0x3E;
  static constexpr uint8 ROL_ZP = 0x26;
  static constexpr uint8 ROL_XIZP = 0x36;
  // ROR (Rotate Right)
  static constexpr uint8 ROR_A = 0x6A;
  static constexpr uint8 ROR_AB = 0x6E;
  static constexpr uint8 ROR_ZIA = 0x7E;
  static constexpr uint8 ROR_ZP = 0x66;
  static constexpr uint8 ROR_XIZP = 0x76;

  // LOGIC INSTRUCTIONS

  // AND ("AND" Memory with Accumulator)
  static constexpr uint8 AND_IMM = 0x29;
  static constexpr uint8 AND_AB = 0x2D;
  static constexpr uint8 AND_XIAB = 0x3D;
  static constexpr uint8 AND_YIAB = 0x39;
  static constexpr uint8 AND_ZP = 0x25;
  static constexpr uint8 AND_XIZP = 0x35;
  static constexpr uint8 AND_XIZPI = 0x21;
  static constexpr uint8 AND_ZPIYI = 0x31;
  // BIT (Test Bits in Memory with Accumulator)
  static constexpr uint8 BIT_AB = 0x2C;
  static constexpr uint8 BIT_ZP = 0x24;
  // EOR ("Exclusive OR" Memory with Accumulator)
  static constexpr uint8 EOR_IMM = 0x49;
  static constexpr uint8 EOR_AB = 0x4D;
  static constexpr uint8 EOR_XIAB = 0x5D;
  static constexpr uint8 EOR_YIAB = 0x59;
  static constexpr uint8 EOR_ZP = 0x45;
  static constexpr uint8 EOR_XIZP = 0x55;
  static constexpr uint8 EOR_XIZPI = 0x41;
  static constexpr uint8 EOR_ZPIYI = 0x51;
  // ORA ("OR" Memory with Accumulator)
  static constexpr uint8 ORA_IMM = 0x09;
  static constexpr uint8 ORA_AB = 0x0D;
  static constexpr uint8 ORA_XIAB = 0x1D;
  static constexpr uint8 ORA_YIAB = 0x19;
  static constexpr uint8 ORA_ZP = 0x05;
  static constexpr uint8 ORA_XIZP = 0x15;
  static constexpr uint8 ORA_XIZPI = 0x01;
  static constexpr uint8 ORA_ZPIYI = 0x11;

  // ARITHMETIC INSTRUCTIONS

  // ADC (Add Memory to Accumulator with Carry)
  static constexpr uint8 ADC_IMM = 0x69;
  static constexpr uint8 ADC_AB = 0x6D;
  static constexpr uint8 ADC_XIAB = 0x7D;
  static constexpr uint8 ADC_YIAB = 0x79;
  static constexpr uint8 ADC_ZP = 0x65;
  static constexpr uint8 ADC_XIZP = 0x75;
  static constexpr uint8 ADC_XIZPI = 0x61;
  static constexpr uint8 ADC_ZPIYI = 0x71;
  // CMP (Compare Memory and Accumulator)
  static constexpr uint8 CMP_IMM = 0xC9;
  static constexpr uint8 CMP_AB = 0xCD;
  static constexpr uint8 CMP_XIAB = 0xDD;
  static constexpr uint8 CMP_YIAB = 0xD9;
  static constexpr uint8 CMP_ZP = 0xC5;
  static constexpr uint8 CMP_XIZP = 0xD5;
  static constexpr uint8 CMP_XIZPI = 0xC1;
  static constexpr uint8 CMP_ZPIYI = 0xD1;
  // CPX (Compare Index Register X To Memory)
  static constexpr uint8 CPX_IMM = 0xE0;
  static constexpr uint8 CPX_AB = 0xEC;
  static constexpr uint8 CPX_ZP = 0xE4;
  // CPY (Compre Index Register Y To Memory)
  static constexpr uint8 CPY_IMM = 0xC0;
  static constexpr uint8 CPY_AB = 0xCC;
  static constexpr uint8 CPY_ZP = 0xC4;
  // SBC (Subtract Memory from Accumulator with Borrow)
  static constexpr uint8 SBC_IMM = 0xE9;
  static constexpr uint8 SBC_AB = 0xED;
  static constexpr uint8 SBC_XIAB = 0xFD;
  static constexpr uint8 SBC_YIAB = 0xF9;
  static constexpr uint8 SBC_ZP = 0xE5;
  static constexpr uint8 SBC_XIZP = 0xF5;
  static constexpr uint8 SBC_XIZPI = 0xE1;
  static constexpr uint8 SBC_ZPIYI = 0xF1;

  // INCREMENT INSTRUCTIONS

  // DEC (Decrement Memory By One)
  static constexpr uint8 DEC_AB = 0xCE;
  static constexpr uint8 DEC_XIAB = 0xDE;
  static constexpr uint8 DEC_ZP = 0xC6;
  static constexpr uint8 DEC_XIZP = 0xD6;
  // DEX (Decrement Index Register X By One)
  static constexpr uint8 DEX_IM = 0xCA;
  // DEY (Decrement Index Register Y By One)
  static constexpr uint8 DEY_IM = 0x88;
  // INC (Increment Memory By One)
  static constexpr uint8 INC_AB = 0xEE;
  static constexpr uint8 INC_XIAB = 0xFE;
  static constexpr uint8 INC_ZP = 0xE6;
  static constexpr uint8 INC_XIZP = 0xF6;
  // INX (Increment Index Register X By One)
  static constexpr uint8 INX_IM = 0xE8;
  // INY (Increment Index Register Y By One)
  static constexpr uint8 INY_IM = 0xC8;

  // CONTROL INSTRUCTIONS

  // BRK (Break Command)
  static constexpr uint8 BRK_IM = 0x00;
  // JMP (JMP Indirect)
  static constexpr uint8 JMP_AB = 0x4c;
  static constexpr uint8 JMP_ABI = 0x6C;
  // JSR (Jump to Subroutine)
  static constexpr uint8 JSR_AB = 0x20;
  // RTI (Return From Interrupt)
  static constexpr uint8 RTI_IM = 0x40;
  // RTS (Return From Subroutine)
  static constexpr uint8 RTS_IM = 0x60;

  // BRANCH INSTRUCTIONS

  // BCC (Branch on Carry Clear)
  static constexpr uint8 BCC_R = 0x90;
  // BCS (Branch on Carry Set)
  static constexpr uint8 BCS_R = 0xB0;
  // BEQ (Branch on Result Zero)
  static constexpr uint8 BEQ_R = 0xF0;
  // BMI (Branch on Result Minus)
  static constexpr uint8 BMI_R = 0x30;
  // BNE (Branch on Result Not Zero)
  static constexpr uint8 BNE_R = 0xD0;
  // BPL (Branch on Result Plus)
  static constexpr uint8 BPL_R = 0x10;
  // BVC (Branch on Overflow Clear)
  static constexpr uint8 BVC_R = 0x50;
  // BVS (Branch on Overflow Set)
  static constexpr uint8 BVS_R = 0x70;

  // FLAG INSTRUCTIONS

  // CLC (Clear Carry Flag)
  static constexpr uint8 CLC_IM = 0x18;
  // CLD (Clear Decimal Mode)
  static constexpr uint8 CLD_IM = 0xD8;
  // CLI (Clear Interrupt Disable)
  static constexpr uint8 CLI_IM = 0x58;
  // CLV (Clear Overflow Flag)
  static constexpr uint8 CLV_IM = 0xB8;
  // SEC (Set Carry Flag)
  static constexpr uint8 SEC_IM = 0x38;
  // SED (Set Deciaml Mode)
  static constexpr uint8 SED_IM = 0xF8;
  // SEI (Set Interrupt Disbale)
  static constexpr uint8 SEI_IM = 0x78;

  // NOP

  // NOP (No Operation)
  static constexpr uint8 NOP_IM = 0xEA;
};
struct Mem {
  static const int max_mem = 1024 * 64;
  uint8 mem[max_mem];

  int address;
  int data;

  static const int ZP_MAX = max_mem - 63488;

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
  opcodes op;
  // Registers
  uint16 PC;
  uint16 SP;
  uint8 A;
  uint8 X;
  uint8 Y;

  uint8 SR_N : 1;
  uint8 SR_V : 1;
  uint8 SR_B : 1;
  uint8 SR_D : 1;
  uint8 SR_I : 1;
  uint8 SR_Z : 1;
  uint8 SR_C : 1;

  int ID;

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

  // Fetching takes data from Program counter
  uint8 FetchUINT8(uint32 &Cycles, Mem &memory) {
    uint8 Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
  }
  // Reading takes data from Address of Program counter
  uint8 ReadUINT8(uint8 Address, uint32 &Cycles, Mem &memory) {
    uint8 Data = memory[Address];
    Cycles--;
    return Data;
  }
  // If address is above zeropage then decrement &Cycles
  void PageIsCrossed(uint32 &Cycles, Mem &memory, uint8 Address) {
    if (Address > memory.ZP_MAX) {
      Cycles--;
    }
  }

  void Init(int cores){
    for(int i = 0; i < cores; i++){
      CPUInitBackground(i);
    }
  }

  // Instruction Implementation
  void LDA(AModes amode, uint32 &Cycles, Mem &memory) {
    switch (amode) {
    case Immediate: {
      uint8 Address = FetchUINT8(Cycles, memory);
      A = Address;
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
    } break;
    case Absolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
    } break;
    case XIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
      PageIsCrossed(Cycles, memory, Address);
    } break;
    case YIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += Y;
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
      PageIsCrossed(Cycles, memory, Address);
    } break;
    case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
    } break;
    case XIndexedZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
      Cycles--;
    } break;
    case XIndexedZeroPageIndirect: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += X;
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address + 1, Cycles, memory);
      uint16 IndirectAddress = concat(HighAddr, LowAddr);
      A = ReadUINT8(IndirectAddress, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
      Cycles--;
    } break;
    case ZeroPageIndirectYIndexed: {
      uint8 Address = FetchUINT8(Cycles, memory);
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address + 1, Cycles, memory);
      uint16 IndirectAddress = concat(HighAddr, LowAddr) + Y;
      A = ReadUINT8(IndirectAddress, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b0000000) > 0;
      PageIsCrossed(Cycles, memory, Address);
    } break;
    default: {
      std::cout << "No Addressing mode handled." << std::endl;
    }
    }
  }
  void LDX(AModes amode, uint32 &Cycles, Mem &memory) {
    switch (amode) {
    case Immediate: {
      uint8 Address = FetchUINT8(Cycles, memory);
      X = Address;
      if (Address == 0) {
        SR_Z = 1;
      }
      SR_N = (X & 0b10000000) > 0;
    } break;
    case Absolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      X = ReadUINT8(Address, Cycles, memory);
      SR_Z = (X == 0);
      SR_N = (X & 0b10000000) > 0;
    } break;
    case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      X = ReadUINT8(Address, Cycles, memory);
      SR_Z = (X == 0);
      SR_N = (X & 0b10000000) > 0;
    } break;
    case YIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      X = Address + Y;
      Cycles--;
      SR_Z = (X == 0);
      SR_N = (X & 0b10000000) > 0;
      PageIsCrossed(Cycles, memory, Address);
    } break;
    case YIndexedZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      X = concat(Address, Y);
      Cycles--;
      Cycles--;
      SR_Z = (X == 0);
      SR_N = (X & 0b10000000) > 0;
    } break;
    default: {
      std::cout << "No Addressing mode handled." << std::endl;
    }
    }
  }
  void LDY(AModes amode, uint32 &Cycles, Mem &memory) {
    switch (amode) {
    case Immediate: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Y = Address;
      SR_Z = (Y == 0);
      SR_N = (Y & 0b10000000) > 0;
    } break;
    case Absolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      Y = concat(HighAddr, LowAddr);
      SR_Z = (Y == 0);
      SR_N = (Y & 0b10000000) > 0;
    } break;
    case XIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Y = concat(HighAddr, LowAddr) + X;
      Cycles--;
      PageIsCrossed(Cycles, memory, Address);
      SR_Z = (Y == 0);
      SR_N = (Y & 0b10000000) > 0;
    } break;
    case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Y = ReadUINT8(Address, Cycles, memory);
      SR_Z = (Y == 0);
      SR_N = (Y & 0b10000000) > 0;
    } break;
    case XIndexedZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Y = concat(Address, X);
      Cycles--;
      Cycles--;
      SR_Z = (Y == 0);
      SR_N = (Y & 0b10000000) > 0;
    } break;
    default: {
      std::cout << "No Addressing mode handled." << std::endl;
    }
    }
  }
  void STA(AModes amode, uint32 &Cycles, Mem &memory) {
    switch (amode) {
    case Absolute: {
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Cycles--;
      Address = A;
    } break;
    case XIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      Cycles--;
      SR_Z = (A == 0);
      SR_N = (A & 0b10000000) > 0;
    } break;
    case YIndexedAbsolute: {
      uint8 LowAddr = FetchUINT8(Cycles, memory);
      uint8 HighAddr = FetchUINT8(Cycles, memory);
      uint16 Address = concat(HighAddr, LowAddr);
      Address += X;
      A = ReadUINT8(Address, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b10000000) > 0;
    } break;
    case ZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
      A = concat(0x00, Address);
      SR_Z = (A == 0);
      SR_N = (A & 0b10000000) > 0;
    } break;
    case XIndexedZeroPage: {
      uint8 Address = FetchUINT8(Cycles, memory);
    } break;
    case XIndexedZeroPageIndirect: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += X;
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address, Cycles, memory);
      uint16 IndirectAddress = concat(HighAddr, LowAddr);
      Address = ReadUINT8(IndirectAddress, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b10000000) > 0;
    } break;
    case ZeroPageIndirectYIndexed: {
      uint8 Address = FetchUINT8(Cycles, memory);
      Address += Y;
      uint8 LowAddr = ReadUINT8(Address, Cycles, memory);
      uint8 HighAddr = ReadUINT8(Address, Cycles, memory);
      uint16 IndrectAddress = concat(HighAddr, LowAddr);
      Address = ReadUINT8(IndrectAddress, Cycles, memory);
      SR_Z = (A == 0);
      SR_N = (A & 0b10000000) > 0;
    } break;
    default: {
      std::cout << "No Addressing mode handled." << std::endl;
    }
    }
  }


  void Execute(uint32 Cycles, Mem &memory) {
    opcodes OP;
    while (Cycles > 0) {
      uint8 Ins = FetchUINT8(Cycles, memory);
      switch (Ins) {
        // LDA
      case OP.LDA_IMM: {
        LDA(Immediate, Cycles, memory);
      } break;
      case OP.LDA_ZP: {
        LDA(ZeroPage, Cycles, memory);
      } break;
      case OP.LDA_ZPX: {
        LDA(XIndexedZeroPage, Cycles, memory);
      } break;
      case OP.LDA_AB: {
        LDA(Absolute, Cycles, memory);
      } break;
      case OP.LDA_ABX: {
        LDA(XIndexedAbsolute, Cycles, memory);
      } break;
      case OP.LDA_ABY: {
        LDA(YIndexedAbsolute, Cycles, memory);
      } break;
      case OP.LDA_ZPXI: {
        LDA(XIndexedZeroPageIndirect, Cycles, memory);
      } break;
      case OP.LDA_ZPYI: {
        LDA(ZeroPageIndirectYIndexed, Cycles, memory);
      } break;
        // LDX
      case OP.LDX_IMM: {
        LDX(Immediate, Cycles, memory);
      } break;
      case OP.LDX_AB: {
        LDX(Absolute, Cycles, memory);
      } break;
      case OP.LDX_ZP: {
        LDX(ZeroPage, Cycles, memory);
      } break;
      case OP.LDX_ABY: {
        LDX(YIndexedAbsolute, Cycles, memory);
      } break;
      case OP.LDX_ZPY: {
        LDX(YIndexedZeroPage, Cycles, memory);
      } break;
        // LDY
      case OP.LDY_IMM: {
        LDY(Immediate, Cycles, memory);
      } break;
      case OP.LDY_AB: {
        LDY(Absolute, Cycles, memory);
      } break;
      case OP.LDY_ABX: {
        LDY(XIndexedAbsolute, Cycles, memory);
      } break;
      case OP.LDY_ZP: {
        LDY(ZeroPage, Cycles, memory);
      } break;
      case OP.LDY_ZPX: {
        LDY(XIndexedZeroPage, Cycles, memory);
      } break;
        // STA
      case OP.STA_AB: {
        STA(Absolute, Cycles, memory);
      } break;
      case OP.STA_ABX: {
        STA(XIndexedAbsolute, Cycles, memory);
      } break;
      case OP.STA_ABY: {
        STA(YIndexedAbsolute, Cycles, memory);
      } break;
      default: {
        std::cout << "No Instruction Found" << std::endl;
      }
      }
    }
  }
private:
  void CPUInitBackground(int id) {
    CPU cpu;
    cpu.mem.Init();
    cpu.ID = id;
    cpu.PC = 0xFFFC;
    cpu.SP = 0x100;
    cpu.A = cpu.X = cpu.Y = 0;
    cpu.SR_C = cpu.SR_Z = cpu.SR_I = cpu.SR_D = cpu.SR_B = cpu.SR_V = cpu.SR_N = 0;
  }
};