#include "cpu/instr.h"
#include "device/port_io.h"
make_instr_func(in_b){
    uint8_t src = pio_read(cpu.gpr[2]._16, 1);
    cpu.gpr[0]._8[0] = src ;
    print_asm_0("in", "b", 1);
    return 1;
}     //  0xec

make_instr_func(in_l){
    if(data_size == 32){
        uint32_t src = pio_read(cpu.gpr[2]._16,data_size/8);
        cpu.eax = src;
        }
    else{
        uint16_t src = pio_read(cpu.gpr[2]._16,data_size/8);
        cpu.gpr[0]._16 = src ;
    }
    print_asm_0("in", data_size == 32?"l" : "w", data_size/8);
    return 1;
}//0xed

make_instr_func(out_b){
    uint8_t src = cpu.gpr[0]._8[0];
    pio_write(cpu.gpr[2]._16, 1, src);
    print_asm_0("out", "b", 1);
    return 1;
}   //0xee