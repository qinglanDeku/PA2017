#include"cpu/instr.h"
static	OPERAND esp;
static void get_esp_l(OPERAND* esp1){ 
		esp1->data_size = 32;
		esp1->type = OPR_REG;
		esp1->sreg = SREG_DS;
		esp1->addr = 0x4;
		operand_read(esp1);
		esp1->val -=4;
		operand_write(esp1);
}


static void instr_execute_2op(){
			operand_read(&opr_src);
	   		opr_dest.val = opr_src.val;
			operand_write(&opr_dest);		
}

static void pushin16(){
	cpu.esp -= 2;
	opr_src.addr = cpu.esp;
	operand_write(&opr_src);
}

static void pushin32(){
	cpu.esp -= 4;
	opr_src.addr = cpu.esp;
	operand_write(&opr_src);
}

make_instr_func(push_reg_l){
	opr_src.data_size = 32;
	opr_src.type = OPR_REG;
	opr_src.sreg = SREG_DS;
	opr_src.addr = opcode & 0x7;
	if (opr_src.addr != 4){

		get_esp_l(&esp);
	//printf("push\n");
	

	
		opr_dest.data_size = 32;
		opr_dest.type = OPR_MEM;
		opr_dest.sreg = SREG_DS;
		opr_dest.addr = esp.val;
		instr_execute_2op();
	}
	else{
		opr_src.val = cpu.esp;
		opr_dest.data_size = 32;
		opr_dest.type = OPR_MEM;
		opr_dest.sreg = SREG_DS;
		cpu.esp -= 4;
		opr_dest.addr = cpu.esp;
		opr_dest.val = opr_src.val;
		operand_write(&opr_dest);
	}
	
	print_asm_1("push","", 1, &opr_src);
	return 1;

}

make_instr_func(push_m_v){
		int len = 1;
		opr_src.data_size = data_size;
		len += modrm_rm(eip+1, &opr_src);
		
		opr_dest.data_size = data_size;
		opr_dest.type = OPR_MEM;
		opr_dest.sreg = SREG_DS;
		cpu.esp -= (data_size/8);
		opr_dest.addr = cpu.esp;

		print_asm_1("push", data_size == 16? "w":"l", len, &opr_src);
		instr_execute_2op();
	   	return len;	
}

make_instr_func(push_i_b){
		 opr_src.data_size = 8;
		 opr_src.type = OPR_IMM;
		 opr_src.sreg = SREG_CS;
		 opr_src.addr = eip + 1;
		 
		 opr_dest.data_size = 32;
		 opr_dest.type = OPR_MEM;
		 opr_dest.sreg = SREG_DS;
		 cpu.esp -= 4;
		 opr_dest.addr = cpu.esp;

		 print_asm_1("push", "b", 2, &opr_src);
		 operand_read(&opr_src);
		 opr_src.val = sign_ext(opr_src.val, 8);
	   	 opr_dest.val = opr_src.val;
		 operand_write(&opr_dest);		
		 return 2;
}		//0x6A

make_instr_func(push_i_v){
		 opr_src.data_size = data_size;
		 opr_src.type = OPR_IMM;
		 opr_src.sreg = SREG_CS;
		 opr_src.addr = eip + 1;

		 opr_dest.data_size = data_size;
		 opr_dest.type = OPR_MEM;
		 opr_dest.sreg = SREG_DS;
		 cpu.esp -= (data_size/8);
		 opr_dest.addr = cpu.esp;

		 print_asm_1("push", data_size == 16?"w":"l", 1+data_size/8, &opr_dest);
		 instr_execute_2op();
		
		 return 1 + data_size/8;
}	//0x68

make_instr_func(pusha){
	uint32_t  temp = cpu.esp;
	opr_src.data_size = data_size;
	opr_src.type = OPR_MEM;
	opr_src.sreg = SREG_DS;
	//printf("cpu.esp = %x\n", cpu.esp);
	if(data_size == 16){
		
		opr_src.val = cpu.eax & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.ecx & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.edx & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.ebx & 0x0000ffff;
		pushin16();
		opr_src.val = temp & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.ebp & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.esi & 0x0000ffff;
		pushin16();
		opr_src.val = cpu.edi & 0x0000ffff;
		pushin16();
	}
	else{
		opr_src.val = cpu.eax ;
		pushin32();
		opr_src.val = cpu.ecx ;
		pushin32();
		opr_src.val = cpu.edx ; 
		pushin32();
		opr_src.val = cpu.ebx ;
		pushin32();
		opr_src.val = temp ;
		pushin32();
		opr_src.val = cpu.ebp ;
		pushin32();
		opr_src.val = cpu.esi ;
		pushin32();
		opr_src.val = cpu.edi ;
		pushin32();
	}
	print_asm_0("pusha", "", 1);
	//printf("esp = %x \n", cpu.esp);
	return 1;
}		//0x60
