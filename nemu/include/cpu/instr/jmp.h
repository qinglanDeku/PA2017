#ifndef __INSTR_JMP_H__
#define __INSTR_JMP_H__

make_instr_func(jmp_near);	//0xE9
make_instr_func(jmp_short);	//0xEB
make_instr_func(jmp_near_rm);	//0xFF - 4
make_instr_func(ljmp);   //0xea
#endif
