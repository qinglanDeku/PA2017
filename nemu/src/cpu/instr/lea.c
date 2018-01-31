#include"cpu/instr.h"

static void instr_execute_2op(){
		 opr_dest.val = opr_src.addr;
		 operand_write(&opr_dest); 
} 
make_instr_func(lea){
	int len = 1;
	opr_src.data_size = data_size;
	opr_dest.data_size = data_size;
	len += modrm_r_rm(eip + 1, &opr_dest ,&opr_src);
	print_asm_2("lea",opr_dest.data_size == 16?"w":"l", len,&opr_src, &opr_dest);
	instr_execute_2op();
	return len;
}
