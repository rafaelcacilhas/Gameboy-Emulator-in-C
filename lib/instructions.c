#include <instructions.h>
#include <cpu.h>

instruction instructions[0x100] = {
  [0x00] = {IN_NOP, AM_IMP},
};

  instruction *instruction_by_opcode(u8 opcode){
  if(instructions[opcode].type == IN_NONE)
  return &instructions[opcode];
}
