#ifndef __INSTR_JCC_H__
#define __INSTR_JCC_H__

make_instr_func(jo_short_);	  //0x70	OF == 1
make_instr_func(jno_short_);  //0x71	OF == 0
make_instr_func(jb_short_);		//0x72	CF == 1
make_instr_func(jae_short_);	//0x73 	CF == 0
make_instr_func(je_short_);   //0x74	ZF == 1
make_instr_func(jne_short_);	//0x75	ZF == 0
make_instr_func(jna_short_);	//0x76	CF == 1 || ZF == 1
make_instr_func(ja_short_);		//0x77	CF == 0 && ZF == 0
make_instr_func(js_short_);		//0x78  SF == 1
make_instr_func(jns_short_);	//0x79  SF == 0
make_instr_func(jp_short_);		//0x7A 	PF == 1
make_instr_func(jnp_short_);	//0x7B  PF == 0
make_instr_func(jl_short_);		//0x7C  SF != OF
make_instr_func(jge_short_);	//0x7D 	SF == OF
make_instr_func(jle_short_);	//0x7E 	ZF == 1 || SF != OF
make_instr_func(jg_short_);		//0x7F  ZF ==0 && SF == OF

make_instr_func(jecxz_short_);	//0xE3	ecx == 0


make_instr_func(jo_near);		//0x0F80
make_instr_func(jno_near);		//0x0F81
make_instr_func(jb_near);		//0x0F82
make_instr_func(jae_near);		//0x0F83
make_instr_func(je_near);		//0x0F84
make_instr_func(jne_near);		//0x0F85
make_instr_func(jna_near);		//0x0F86
make_instr_func(ja_near);		//0x0F87
make_instr_func(js_near);		//0x0F88
make_instr_func(jns_near);		//0x0F89
make_instr_func(jp_near);		//0x0F8A
make_instr_func(jnp_near);		//0x0F8B
make_instr_func(jl_near);		//0x0F8C
make_instr_func(jge_near);		//0x0F8D
make_instr_func(jle_near);		//0x0F8E
make_instr_func(jg_near);		//0x0F8F


#endif
