#include"cpu/instr.h"

static void instr_execute_2op(){
		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_dest.val = alu_sbb(opr_src.val, opr_dest.val);
		 operand_write(&opr_dest);
}	


make_instr_impl_2op(sbb, r, rm, b)	//0x18
make_instr_impl_2op(sbb, r, rm, v)	//0x19
make_instr_impl_2op(sbb, rm, r, b)	//0x1A
make_instr_impl_2op(sbb, rm, r, v) 	//0x1B
make_instr_impl_2op(sbb, i, a, b) 	//0x1C
make_instr_impl_2op(sbb, i, a ,v) 	//0x1D

make_instr_impl_2op(sbb, i, rm, b) 	//0x80 - 3
make_instr_impl_2op(sbb, i, rm, v)	//0x81 - 3


make_instr_func(sbb_si82rm_v){
	int len = 1;
	
	opr_dest.data_size = data_size;
	len += modrm_rm(eip+1, &opr_dest);

	opr_src.data_size = 8;	
	opr_src.type = OPR_IMM;
	opr_src.addr = eip + len;

	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val, 8);
	opr_dest.val = alu_sbb(opr_src.val, opr_dest.val);
	operand_write(&opr_dest);
	print_asm_2("sbb", data_size == 16?"w":"l", len+1, &opr_src, &opr_dest);

	return len + 1;
}		// 0x83 - 3
