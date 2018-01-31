#ifndef __INSTR_SBB_H__
#define __INSTR_SBB_H__

make_instr_func(sbb_r2rm_b);	//0x18
make_instr_func(sbb_r2rm_v);	//0x19
make_instr_func(sbb_rm2r_b);	//0x1A
make_instr_func(sbb_rm2r_v);	//0x1B
make_instr_func(sbb_i2a_b);		//0x1C
make_instr_func(sbb_i2a_v);		//0x1D

make_instr_func(sbb_i2rm_b);	//0x80 - 3
make_instr_func(sbb_i2rm_v);	//0x81 - 3

make_instr_func(sbb_si82rm_v);	//0x83 - 3

#endif
