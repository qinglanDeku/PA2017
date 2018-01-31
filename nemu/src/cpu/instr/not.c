#include"cpu/instr.h"

static void instr_execute_1op(){
		 opr_dest.data_size = opr_src.data_size;
		 opr_dest.type = opr_src.type;
		 opr_dest.addr = opr_src.addr;
		 operand_read(&opr_src);
		 opr_dest.val = ~opr_src.val;
		 operand_write(&opr_dest);
}

make_instr_impl_1op(not, rm, b)		//0xF6 -2
make_instr_impl_1op(not, rm, v)		//0xF7 - 2
