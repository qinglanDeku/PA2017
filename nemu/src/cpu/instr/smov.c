#include"cpu/instr.h"

make_instr_func(mov_cr2r_v){
    int len = 1;
    opr_dest.data_size = 32;
    opr_dest.type = OPR_REG;
    uint8_t crNo = 0;
    len += modrm_opcode_rm(eip + 1, &crNo, &opr_dest);
    if(crNo == 0)
        opr_dest.val = cpu.cr0.val;
    else if(crNo == 3)
        opr_dest.val = cpu.cr3.val;
    else;

    operand_write(&opr_dest);
    /*opr_dest.data_size = 32;
    len += modrm_rm(eip+1, &opr_dest);
    opr_dest.type = OPR_REG;
    operand_read(&opr_dest);
    cpu.cr0.val = opr_src.val;
    opr_dest.val = opr_src.val;
    operand_write(&opr_dest);*/
    return len;
}               //0xf020

make_instr_func(mov_r2cr_v){
    int len = 1;
    //opr_dest.data_size = 32;
    opr_src.data_size =32;
    uint8_t crNo = 0;
    len +=modrm_opcode_rm(eip + 1, &crNo, &opr_src);
    operand_read(&opr_src);
    if(crNo == 0)
        cpu.cr0.val = opr_src.val;
    else if(crNo == 3)
        cpu.cr3.val = opr_src.val;
    else;

    return len;
}           //0x0f22