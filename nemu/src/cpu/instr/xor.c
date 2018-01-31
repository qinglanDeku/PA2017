#include "cpu/instr.h"

static void instr_execute_2op(){
		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_dest.val = alu_xor(opr_src.val, opr_dest.val);
		 operand_write(&opr_dest);
}	

/* 0x30 - 0x35 */
make_instr_impl_2op(xor, r, rm, b)
make_instr_impl_2op(xor, r, rm, v)
make_instr_impl_2op(xor, rm, r, b)
make_instr_impl_2op(xor, rm, r, v)
make_instr_impl_2op(xor, i, a, b)
make_instr_impl_2op(xor, i, a, v)
	
make_instr_impl_2op(xor, i, rm, b)	//0x80 - 6
make_instr_impl_2op(xor, i, rm, v)	//0x81 - 6

make_instr_func(xor_si82rm_v){
		 int len = 1;

		 opr_dest.data_size = data_size;
		 len += modrm_rm(eip+1, &opr_dest);

		 opr_src.data_size = 8;
		 opr_src.type = OPR_IMM;
		 opr_src.addr = eip + len;

		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_src.val = sign_ext(opr_src.val, 8);
		 opr_dest.val = alu_xor(opr_src.val, opr_dest.val);
		 operand_write(&opr_dest);
		 print_asm_2("xor", "", len+1, &opr_src, &opr_dest);

		 return len + 1;
}

