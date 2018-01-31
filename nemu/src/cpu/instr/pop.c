#include "cpu/instr.h"
static void instr_execute_2op(){
		 operand_read(&opr_src);
		 opr_dest.val = opr_src.val;
		 operand_write(&opr_dest);
}	
static void instr_execute_2op2(){
	 	operand_read(&opr_src);
		 opr_dest.val = opr_src.val;
		 operand_write(&opr_dest);
		 cpu.esp += data_size/8;
}


make_instr_func(pop_reg_l){
		 opr_src.data_size = 32;
		 opr_src.type = OPR_MEM;
		 opr_src.sreg = SREG_DS;
		 opr_src.addr = cpu.esp;

		 opr_dest.data_size = 32;
		 opr_dest.type = OPR_REG;
		 opr_dest.addr = opcode & 0x7;

		 print_asm_1("pop", "", 1, &opr_dest);

		 instr_execute_2op();

		 cpu.esp += 4;

		 return 1;
}	//0x58 -- 0x5F


make_instr_func(pop_m_v){
		 int len = 1;
		 opr_dest.data_size = data_size;
		 len += modrm_rm(eip + 1, &opr_dest);

		 opr_src.data_size = data_size;
		 opr_src.type = OPR_MEM;
		 opr_src.addr = cpu.esp;

		 print_asm_1("pop", data_size == 16?"w":"l", len, &opr_dest);

		 instr_execute_2op();
	   		
		 cpu.esp += (data_size/8);
		 return len;
} 	//0x8F

make_instr_func(popa){
	opr_src.data_size = data_size;
	opr_src.type = OPR_MEM;
	opr_src.sreg = SREG_DS;
	
	opr_dest.data_size = data_size;
	opr_dest.type = OPR_REG;
	if(data_size ==16){
		opr_dest.addr = 7;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 6;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 5;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		cpu.esp += 2;

		opr_dest.addr = 3;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 2;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 1;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 0;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();
	}
	else{
		opr_dest.addr = 7;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 6;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 5;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		cpu.esp +=4;

		opr_dest.addr = 3;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 2;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 1;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();

		opr_dest.addr = 0;
		opr_src.addr = cpu.esp;
		instr_execute_2op2();
	}
	return 1;
}		//0x61

