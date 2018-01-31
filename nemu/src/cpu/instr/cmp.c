#include"cpu/instr.h"
static void instr_execute_2op(){
		operand_read(&opr_src);
	   	operand_read(&opr_dest);
	 	alu_sub(opr_src.val, opr_dest.val);
}

make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, rm, r, v) 
make_instr_impl_2op(cmp, r, rm, b) 
make_instr_impl_2op(cmp, r, rm, v) 
make_instr_impl_2op(cmp, i, a, b) 
make_instr_impl_2op(cmp, i, a, v) 
// 0x38--0x3d

make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, i, rm, v)

make_instr_func(cmp_si82rm_v){
		 int len = 1;
		 
		 opr_dest.data_size = data_size;
		 len += modrm_rm(eip+1, &opr_dest);

		 opr_src.data_size = 8;
		 opr_src.type = OPR_IMM;
		 opr_src.addr = eip + len;

		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_src.val = sign_ext(opr_src.val, 8);
		 alu_sub(opr_src.val, opr_dest.val);
	     print_asm_2("cmp", "", len, &opr_src, &opr_dest);
		 return len + 1;	 
		
}
