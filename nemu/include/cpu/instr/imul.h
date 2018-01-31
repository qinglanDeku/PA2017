#ifndef __INSTR_IMUL_H__
#define __INSTR_IMUL_H__

make_instr_func(imul_rm2r_v);		//0x0FAF
make_instr_func(imul_rm2a_b);		//0xF6 - 5
make_instr_func(imul_rm2a_v);		//0xF7 - 5



make_instr_func(imul_irm2r_v);		//0x69
make_instr_func(imul_i8rm2r_v);		//0x6B

#endif
