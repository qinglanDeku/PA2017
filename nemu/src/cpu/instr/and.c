#include"cpu/instr.h"

static void instr_execute_2op(){
		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_dest.val = alu_and(opr_src.val, opr_dest.val);
		 operand_write(&opr_dest);
}	

/* 0x20 - 0x25*/
make_instr_impl_2op(and, r, rm, b)
make_instr_impl_2op(and, r, rm, v)
make_instr_impl_2op(and, rm, r, b)
make_instr_impl_2op(and, rm, r, v)
make_instr_impl_2op(and, i, a, b)
make_instr_impl_2op(and, i, a, v)

make_instr_impl_2op(and, i, rm, b)	//0x80 - 4
make_instr_impl_2op(and, i, rm, v)	//0x81 - 4

make_instr_func(and_si82rm_v){
		int len = 1;

		opr_dest.data_size = data_size;
		len += modrm_rm(eip+1, &opr_dest);

		opr_src.data_size = 8;
		opr_src.type = OPR_IMM;
		opr_src.addr = eip + len;

		operand_read(&opr_src);
		operand_read(&opr_dest);
		opr_src.val = sign_ext(opr_src.val, 8);
		opr_dest.val = alu_and(opr_src.val, opr_dest.val);
		operand_write(&opr_dest);
		print_asm_2("and", "", len+1, &opr_src, &opr_dest);
		
		return len + 1;
}
// 0x83 -4
