#include "cpu/instr.h"
make_instr_func(jmp_near) {
	//printf("JMP_NEAR\n");
        OPERAND rel;
        rel.type = OPR_IMM;
		rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;
		//printf("jmp here!");
        operand_read(&rel);

	int offset = sign_ext(rel.val, data_size);
//	print_asm_1("jmp", "", 2, &rel);
	print_asm_1("jmp","",1+data_size / 8, &rel);
	cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_short){
		 OPERAND rel;
		 rel.type = OPR_IMM;
		 rel.sreg = SREG_CS;
		 rel.data_size = 8;
		 rel.addr = eip + 1;
		 operand_read(&rel);
		 print_asm_1("jmp", "", 2, &rel);
		 rel.val = sign_ext(rel.val, 8);
		 cpu.eip += rel.val;

		 return 2;
}

make_instr_func(jmp_near_rm){
		 int len = 1;
		 //printf("JUMPHERE\n");
		 opr_src.data_size = data_size;
		 opr_src.sreg = SREG_DS;
		 //opr_src.sreg = SREG_CS;
		 len += modrm_rm(eip + 1, &opr_src);
		 operand_read(&opr_src);

		 /*OPERAND rel;
		 rel.type = OPR_MEM;
		 rel.sreg = SREG_CS;
		 rel.data_size = data_size;
		 rel.addr = opr_src.val;
		 operand_read(&rel);*/
		 int offset = sign_ext(opr_src.val, data_size);
		
		 print_asm_1("jmp","", len, &opr_src);
		 
		 cpu.eip = offset;
		 //printf("eip = %x\n" , cpu.eip);
		 //printf("EAX = %x\n", cpu.eax);
		 return 0;

}		//0xFF - 4

make_instr_func(ljmp){
	//printf("ljmp\n");
	//int len = 1;
	OPERAND temp1, temp2;		//temp1 for cs, temp2 for eip(ip)
	temp1.type = temp2.type = OPR_IMM;
	temp1.data_size = 16;
	temp2.data_size = data_size;
	temp2.addr = cpu.eip+ 1;
	temp1.addr = cpu.eip + 1+data_size/8;

	operand_read(&temp1);
	operand_read(&temp2);
	//printf("temp1 = %x\n", temp1.val);
	//printf("temp2 = %x\n", temp2.val);

	cpu.segReg[1].val = temp1.val;
	if (data_size == 16)	
		cpu.eip = temp2.val& 0x0000ffff;
	else	cpu.eip = temp2.val;
	//printf("eip - before = %x", eip)
	
	load_sreg(1);

	//len += 2 + data_size/8;
	return 0 ;

}   //0xea
