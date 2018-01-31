#include"cpu/instr.h"

make_instr_func(das){
		 if((cpu.gpr[0]._8[0]&0x0F)>9|| cpu.eflags.AF == 1){
				 cpu.gpr[0]._8[0]  -=6;
				 cpu.eflags.AF = 1;
		 }
		 else cpu.eflags.AF = 0;

		 if(cpu.gpr[0]._8[0]>0x9F|| cpu.eflags.CF == 1)
		 {
				 cpu.gpr[0]._8[0] -=0x60;
				 cpu.eflags.CF = 1;
		 } 
		 else cpu.eflags.CF = 0;
		print_asm_0("das", "", 1);
		 return 1;
} 
