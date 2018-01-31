#include"cpu/instr.h"

make_instr_func(lidt){
     int len = 1;
    OPERAND limit, base;
    
    limit.data_size = 16;
    base.data_size = 32;
    len += modrm_rm(eip + 1, &limit);
    //printf("idtr.base = %x\n", base.val);
    operand_read(&limit);
    if(limit.type == OPR_IMM){
       // printf("here\n");
        base.type = limit.type;
        base.sreg = limit.sreg;
        base.addr =limit.addr + 2;
        operand_read(&base);
    }
    else {
      assert(limit.type == OPR_MEM);
     // printf("there\n");
      //printf("limit.addr = %x, limit.val = %x\n", limit.addr, limit.val);

      base.type = limit.type;
      base.sreg = limit.sreg;
      base.addr = limit.addr + 2;
      operand_read(&base);
    }

    cpu.idtr.limit = limit.val;
    cpu.idtr.base = (data_size == 16? (base.val & 0x00ffffff) : base.val);
    return len;
}