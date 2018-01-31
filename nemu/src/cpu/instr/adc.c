#include"cpu/instr.h"

static void instr_execute_2op(){
		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 opr_dest.val = alu_adc(opr_src.val, opr_dest.val);
		 operand_write(&opr_dest);
}	


make_instr_impl_2op(adc, r, rm, b)	//0x10
make_instr_impl_2op(adc, r, rm, v)	//0x11
make_instr_impl_2op(adc, rm, r, b)	//0x12
make_instr_impl_2op(adc, rm, r, v) 	//0x13
make_instr_impl_2op(adc, i, a, b) 	//0x14
make_instr_impl_2op(adc, i, a ,v) 	//0x15

make_instr_impl_2op(adc, i, rm, b) 	//0x80 - 2
make_instr_impl_2op(adc, i, rm, v)	//0x81 - 2


make_instr_func(adc_si82rm_v){
	int len = 1;
	
	opr_dest.data_size = data_size;
	len += modrm_rm(eip+1, &opr_dest);

	opr_src.data_size = 8;	
	opr_src.type = OPR_IMM;
	opr_src.addr = eip + len;

	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val = sign_ext(opr_src.val, 8);
	opr_dest.val = alu_adc(opr_src.val, opr_dest.val);
	operand_write(&opr_dest);
	print_asm_2("adc", data_size == 16?"w":"l", len+1, &opr_src, &opr_dest);

	return len + 1;
}		// 0x83 - 2
