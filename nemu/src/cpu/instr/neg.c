#include"cpu/instr.h"

make_instr_func(negv){
    int len = 1;
    len += modrm_rm(eip + 1, &opr_src);
    operand_read(&opr_src);

    if(opr_src.val == 0)
        cpu.eflags.CF = 0;

    else 
        cpu.eflags.CF = 1;
        
    opr_src.val = -opr_src.val;
    operand_write(&opr_src);
    return len;
}