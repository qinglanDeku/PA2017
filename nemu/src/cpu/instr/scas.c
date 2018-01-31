#include "cpu/instr.h"

//this instruction is special for it uses src - dest  and it must depend on SREG_ES
static void instr_execute_2op(){
		 operand_read(&opr_src);
		 operand_read(&opr_dest);
		 alu_sub(opr_dest.val, opr_src.val);
		 if(cpu.eflags.DF == 0)
				 opr_dest.val += opr_dest.data_size/8;
		 else
				 opr_dest.val -= opr_dest.data_size/8;
		 operand_write(&opr_dest);
}	

make_instr_func(scas_b){

		 opr_src.data_size = 8;
		 opr_src.type = OPR_REG;
		 opr_src.addr = 0x0;



		 opr_dest.data_size = 32;
		 opr_dest.type = OPR_MEM;
		 opr_dest.addr = cpu.edi;
		 opr_dest.sreg = SREG_ES;

		 instr_execute_2op();

		 return 1;
}

make_instr_func(scas_v){
		 opr_src.data_size = data_size;
		 opr_src.type = OPR_REG;
		 opr_src.addr = 0x0;

		 opr_dest.data_size = data_size;
		 opr_dest.type = OPR_MEM;
		 opr_dest.addr = cpu.edi;
		 opr_dest.sreg = SREG_ES;

		 instr_execute_2op();
		 return 1;
}
