#ifndef __INSTR_INT_H__
#define __INSTR_INT_H__

make_instr_func(INT);       //0xcd
make_instr_func(IRET);      //0xcf

void raise_sw_intr(uint8_t intr_no);

#endif 