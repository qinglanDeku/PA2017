#include "cpu/instr.h"

make_instr_func(leave){
	OPERAND l_esp, l_ebp, l_addr;
	l_esp.data_size = data_size;
	l_ebp.data_size = data_size;
	l_esp.type = OPR_REG;
	l_ebp.type = OPR_REG;	
	l_esp.addr = 0x4;
	l_ebp.addr = 0x5;

	operand_read(&l_ebp);
	l_esp.val = l_ebp.val;
	operand_write(&l_esp);

	//fisrt step of leave
	
	l_addr.data_size = data_size;
	l_addr.type = OPR_MEM;
	l_addr.addr = cpu.esp;
	l_addr.sreg = SREG_CS;
	operand_read(&l_addr);
	l_ebp.val = l_addr.val;
	operand_write(&l_ebp);
	cpu.esp += data_size/8;

	print_asm_0("leave", "", 1);
	
	return 1;
	
}
