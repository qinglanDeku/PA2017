#include"cpu/instr.h"

static void instr_execute_1op(){
		 operand_read(&opr_dest);
		 uint8_t temp = cpu.eflags.CF;
		 opr_dest.val =  alu_add(1, opr_dest.val);	
		 cpu.eflags.CF = temp;
		 operand_write(&opr_dest);
}

make_instr_func(inc_r_v){
		opr_dest.data_size = data_size;
		opr_dest.type = OPR_REG;
		opr_dest.addr = opcode&0x07;
		
		print_asm_1("inc", data_size == 16?"w":"l", 1, &opr_dest);

		instr_execute_1op();
		return 1;	
}

make_instr_func(inc_rm_b){
		 int len = 1;
		 opr_dest.data_size = 8;
		 len += modrm_rm(eip+1,&opr_dest);
		 
		 print_asm_1("inc", "b", len, &opr_dest);

		 instr_execute_1op();
		 return len;
}

make_instr_func(inc_rm_v){
		 int len = 1;
		 opr_dest.data_size = data_size;
		 len += modrm_rm(eip+1, &opr_dest);

		 print_asm_1("inc", data_size == 16?"w":"l", len, &opr_dest);

		 instr_execute_1op();
		 return len;
}
