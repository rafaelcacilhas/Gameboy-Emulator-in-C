#pragma once
#include <common.h>

typedef enum {
  AM_IMP,
  AM_R_D16,
  AM_R,
  AM_D16,
} address_mode;

typedef enum{
  RT_NONE,
  RT_A,
  RT_F,
  RT_B,
  RT_C
} register_type;

typedef enum{
  IN_NONE,
  IN_NOP,
  IN_LOAD,
  IN_INCREASE,
  IN_DECREASE,
  IN_RLCA,
  IN_ADDITION,
  IN_RRCA,
  IN_STOP
} instruction_type;

typedef enum{
  CT_NONE,
  CT_NZ,
  CT_Z,
  CT_NC,
  CT_,C
} condition_type;

typedef struct{
  instruction_type type;
  address_mode mode;
  register_type register_1;
  register_type register_2;
  condition_type  condition;
  u8 param;
} instruction;

instruction *instruction_by_opcode(u8 opcode);

char *instruction_name(instruction_type type);
