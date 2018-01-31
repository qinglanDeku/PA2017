#ifndef __INSTR_CALL_H__
#define __INSTR_CALL_H__

make_instr_func(call);				//0xe8
make_instr_func(call_rm_v);			//0xff ---2
make_instr_func(ret);				//0xC3
make_instr_func(ret_i_near);		//0xC2


#endif
