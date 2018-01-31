#ifndef __INSTR_PUSH_H__
#define __INSTR_PUSH_H__
make_instr_func(push_reg_l);	//0x50 - 0x57
make_instr_func(push_m_v);		//0xFF
make_instr_func(push_i_b);		//0x6A
make_instr_func(push_i_v);		//0x68
make_instr_func(pusha);         //0x60
#endif
