#include "cpu/instr.h"

static void push_next_eip( uint32_t nex_eip, uint32_t data_size){
		 OPERAND  addr;
		 if(data_size == 32){
			 addr.data_size = 32;
		 	 cpu.esp -= 4;
		 }
		 else{
			addr.data_size = 16;
			cpu.esp -=2;	
		 }
		 //printf("haha\n");
		 addr.type = OPR_MEM;
		 addr.sreg = SREG_DS;					// register type is neccesary!!!
		 addr.addr = cpu.esp;
		 addr.val = nex_eip;
		 operand_write(&addr);
}


static void pop_ret( OPERAND* myeip){
		 myeip->data_size = 32;
		 myeip->type = OPR_MEM;
		 myeip->sreg = SREG_DS;
		 myeip->addr = cpu.esp;
		// myeip->sreg = SREG_CS;
		 cpu.esp += 4;
		 operand_read(myeip);
}
/*static void pop_ret_i_w(OPERAND* myeip){
		 myeip->data_size = 32;
		 myeip->type = OPR_MEM;
		 myeip->addr = cpu.esp;
		 myeip->sreg = SREG_CS;
		 cpu.esp += 2;
		 operand_read(myeip); 
}*/
make_instr_func(call){
		 OPERAND rel;
		 rel.type = OPR_IMM;
		 rel.sreg = SREG_CS;
		 rel.data_size = data_size;
		 rel.addr = eip + 1;
		
		operand_read(&rel); 

		 push_next_eip(eip + data_size/8 + 1, rel.data_size);

   		print_asm_1("call", "",1+data_size / 8, &rel); // **************not complete!!!!!!
		if(rel.data_size == 32){
			int offset = sign_ext(rel.val, data_size);
		// rel.val = rel.val;
		 cpu.eip += offset;
         } 
		else{
			cpu.eip = ( cpu.eip + rel.val)&0x0000FFFF; 
		} 
				 
		//return 0;
		return 1 + data_size / 8;
}				//0xe8


make_instr_func(call_rm_v){
		
		int len = 1;	
		OPERAND rel;
		rel.data_size = data_size;
		rel.sreg = SREG_CS;
		len += modrm_rm(eip + 1, &rel);
		operand_read(&rel);

		
		push_next_eip(eip+len, rel.data_size);

		print_asm_1("call", "", len, &rel);

		if(rel.data_size==32){
				 cpu.eip = sign_ext(rel.val, data_size);
		}
		else{
				 cpu.eip = rel.val&0x0000FFFF;
		}
		
		return 0;  // why 0?

}	//0xFF ----2

make_instr_func(ret){
		OPERAND rel;
		pop_ret(&rel);
		print_asm_0("ret", "", 1);
		cpu.eip = rel.val;
		return 0;
}

make_instr_func(ret_i_near){
		OPERAND rel;	
		pop_ret(&rel);
		opr_src.data_size = 16;
		opr_src.addr = eip+1;
		opr_src.type = OPR_IMM;
		opr_src.sreg = SREG_CS;
		operand_read(&opr_src);
		cpu.esp +=opr_src.val;
		//	cpu.eip &=0x0000FFFF; 

		print_asm_1("ret","", 3, &opr_src);
		cpu.eip = rel.val;
	

		return 0;
}
