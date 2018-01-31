#include"cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_sub(opr_src.val, opr_dest.val);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sub, r, rm, b)	//0x28
make_instr_impl_2op(sub, r, rm, v)	//0x29
make_instr_impl_2op(sub, rm, r, b)	//0x2A
make_instr_impl_2op(sub, rm, r, v)	//0x2B
make_instr_impl_2op(sub, i, a, b)	//0x2C
make_instr_impl_2op(sub, i, a, v)	//0x2D

make_instr_impl_2op(sub, i, rm, b)	//0x80
make_instr_impl_2op(sub, i, rm, v)	//0x81

make_instr_func(sub_si82rm_v){
	int len = 1;

	opr_dest.data_size = data_size;
	len += modrm_rm(eip+1, &opr_dest);
	
	opr_src.data_size = 8;
	opr_src.type = OPR_IMM;
	opr_src.addr = eip + len;
	
	operand_read(&opr_dest);
	operand_read(&opr_src);
	opr_src.val = sign_ext(opr_src.val, 8);
	opr_dest.val = alu_sub(opr_src.val, opr_dest.val);
	operand_write(&opr_dest);
	print_asm_2("sub", "", len, &opr_src, &opr_dest);

	return len + 1;
}

