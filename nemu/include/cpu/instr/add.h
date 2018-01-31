#ifndef __INSTR_ADD_H__
#define __INSTR_ADD_H__

make_instr_func(add_r2rm_b);//opcode 0x00
make_instr_func(add_r2rm_v);//opcode 0x01
make_instr_func(add_rm2r_b);//opcode 0x02
make_instr_func(add_rm2r_v);//opcode 0x03
make_instr_func(add_i2a_b);//opcode 0x04
make_instr_func(add_i2a_v);//opcode 0x05

make_instr_func(add_i2rm_b);//opcode 0x80
make_instr_func(add_i2rm_v);//opcode 0x81

make_instr_func(add_si82rm_v); //opcode 0x83

#endif
