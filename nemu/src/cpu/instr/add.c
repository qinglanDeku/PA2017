#include"cpu/instr.h"

static void instr_execute_2op() {
		 operand_read( &opr_src);
		 operand_read(&opr_dest);
		opr_dest.val = alu_add(opr_src.val, opr_dest.val);
		//printf("src = %d, dest = %d",opr_src.val, opr_dest.val);	
	   	operand_write( &opr_dest);
}


make_instr_impl_2op(add, r, rm, b) //0x00
make_instr_impl_2op(add, r, rm, v) //0x01
make_instr_impl_2op(add, rm, r, b) //0x02
make_instr_impl_2op(add, rm, r, v) //0x03
make_instr_impl_2op(add, i, a, b) //0x04
make_instr_impl_2op(add, i, a, v) //0x05

make_instr_impl_2op(add, i, rm, b) //0x80
make_instr_impl_2op(add, i, rm, v) //0x81


make_instr_func(add_si82rm_v){
		int len = 1;

		opr_dest.data_size = data_size;
		len += modrm_rm(eip+1, &opr_dest);
		
		opr_src.data_size = 8;
		opr_src.type = OPR_IMM;
		opr_src.addr = eip + len;
		
		operand_read(&opr_src);
		operand_read(&opr_dest);
		opr_src.val = sign_ext(opr_src.val, 8);
		opr_dest.val = alu_add(opr_src.val, opr_dest.val);
		operand_write(&opr_dest);
		print_asm_2("add", data_size == 16?"w":"l", len+1, &opr_src, &opr_dest);
		
		return len + 1;	

} //0x83



/*make_instr_func(add_r2rm_b){
		decode_data_size_b
		int len = 1;
		decode_operand_r2rm
		instr_execute_2op();
		return len;	
} 	//0x00

make_instr_func(add_r2rm_v){
		decode_data_size_v
		int len = 1;
		decode_operand_r2rm
		instr_execute_2op();
		return len;	

}//0x01  

make_instr_func(add_rm2r_b){
		decode_data_size_b	

}//0x02*/
