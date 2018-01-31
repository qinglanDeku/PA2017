#include "cpu/instr.h"

static void instr_execute_1op_cc_pass() {
	opr_src.val = 1;
	operand_write(&opr_src);
}

static void instr_execute_1op_cc_fail() {
	opr_src.val = 0;
	operand_write(&opr_src);
}


//all have a prefix of 0x0F***********
make_instr_impl_1op_cc(set, rm, b, ne)		//0x95
make_instr_impl_1op_cc(set, rm, b, a)		//0x97
make_instr_impl_1op_cc(set, rm, b, ae)		//0x93
make_instr_impl_1op_cc(set, rm, b, be)		//0x96
make_instr_impl_1op_cc(set, rm, b, c)		//0x92
make_instr_impl_1op_cc(set, rm, b, e)		//0x94
make_instr_impl_1op_cc(set, rm, b, g)		//0x9F
make_instr_impl_1op_cc(set, rm, b, ge)		//0x9D
make_instr_impl_1op_cc(set, rm, b, l)		//0x9C
make_instr_impl_1op_cc(set, rm, b, le)		//0x9E
make_instr_impl_1op_cc(set, rm, b, no)		//0x91
make_instr_impl_1op_cc(set, rm, b, np)		//0x9B
make_instr_impl_1op_cc(set, rm, b, ns)		//0x99
make_instr_impl_1op_cc(set, rm, b, o)		//0x90
make_instr_impl_1op_cc(set, rm, b, p)		//0x9A
make_instr_impl_1op_cc(set, rm, b, s)		//0x98
