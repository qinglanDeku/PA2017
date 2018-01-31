#include"cpu/instr.h"

make_instr_func(INT){

    OPERAND Num;
    Num.data_size = data_size;
    Num.type = OPR_IMM;
    Num.sreg = SREG_CS;
    Num.addr = eip + 1;
    operand_read(&Num);
   // printf("cpu.esp = %x\n", cpu.esp);
    raise_sw_intr((uint8_t)Num.val);
    print_asm_1("int", "", 2, &Num);
  //  printf("eip = %x\n", cpu.eip);
    return 0;
}

make_instr_func(IRET){
    opr_src.data_size = 32;
    opr_src.type = OPR_MEM;
    opr_src.sreg = SREG_DS;
    opr_src.addr = cpu.esp;

    operand_read(&opr_src);
    cpu.eip = opr_src.val;
    cpu.esp += 4;

    opr_src.data_size = 16;
    opr_src.addr = cpu.esp;
    operand_read(&opr_src);
    cpu.cs.val = opr_src.val;
    cpu.esp += 4;

    opr_src.data_size = 32;
    opr_src.addr = cpu.esp;
    operand_read(&opr_src);
    cpu.eflags.val = opr_src.val;
    cpu.esp += 4;

    return 0;



} //0xcf