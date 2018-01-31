#include"cpu/instr.h"

make_instr_func(lgdt){
    int len = 1;
    OPERAND limit, base;
    limit.data_size = 16;
    base.data_size = 32;
    len += modrm_rm(eip + 1, &limit);
    operand_read(&limit);
    if(limit.type == OPR_IMM){
        //printf("here\n");
        base.type = limit.type;
        base.sreg = limit.sreg;
        base.addr =limit.addr + 2;
        operand_read(&base);
    }
    else {
      assert(limit.type == OPR_MEM);
      //printf("there\n");
      //printf("limit.addr = %x, limit.val = %x\n", limit.addr, limit.val);

      base.type = limit.type;
      base.sreg = limit.sreg;
      base.addr = limit.addr + 2;
      operand_read(&base);
    }//printf("limit.addr = %x ", limit.addr);
    //printf("LGDT\n");
    //printf("gdtrlimit = %x\n", limit.val);
    /*uint32_t data[6];
    for(int i = 0; i<6; i++)
        data[i] = hw_mem[opr_src.val+i];
    cpu.gdtr.base = (data[3] << 24)  + (data[2] << 16) + (data[1] << 8) + (data[0]);
    if(data_size == 16)
        cpu.gdtr.base = cpu.gdtr.base & 0x00ffffff;
    cpu.gdtr.limit = (data[5] << 8) + data[4];*/
    cpu.gdtr.limit = limit.val;
    cpu.gdtr.base = (data_size == 16? (base.val & 0x00ffffff) : base.val);
    return len;
}