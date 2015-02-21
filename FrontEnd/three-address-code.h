#ifndef THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_H

#include "symbol-table.h"

#define LABEL "L"

typedef enum optype {
  TAC_Assg,
  TAC_Plus,
  TAC_Return
} optype;

typedef enum addrtype {
  AT_Intcon, // integer constant
  AT_Stringcon, // string constant
  AT_StRef // symbol table reference
} addrtype;

typedef struct address {
  enum addrtype atype;
  union {
    int iconst;
    char *strconst;
    symtabnode *stptr;
  } val;
} address;

typedef struct instr {
  enum optype op;
  struct address *dest, *operand1, *operand2;
  struct instr *prev;
  struct instr *next;
} instr;

typedef struct three_addr_code {
  struct instr *start;
  struct instr *end;
} three_addr_code;

#endif
