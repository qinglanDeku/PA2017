#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	
	int pro_offset = offset + cpu.segReg[sreg].base;
	//printf("here");
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	return pro_offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	
	uint32_t Addr = cpu.segReg[sreg].index*8+ cpu.gdtr.base;
	SegDesc segdesc;
	memcpy(&segdesc, hw_mem+Addr, sizeof(SegDesc));
	//printf("addr= %x\n",Addr );

	//printf("base = %x\n", cpu.gdtr.base);
	cpu.segReg[sreg].base = segdesc.base_15_0 + (segdesc.base_23_16 <<  16) + (segdesc.base_31_24 << 24);
	cpu.segReg[sreg].limit  = segdesc.limit_15_0 + (segdesc.limit_19_16 << 16);
	cpu.segReg[sreg].type = segdesc.type;
	cpu.segReg[sreg].privilege_level = segdesc.privilege_level;
	cpu.segReg[sreg].soft_use = segdesc.soft_use;

	assert(cpu.segReg[sreg].base == 0 );
	//printf("limit = %x\n", cpu.segReg[sreg].limit);
	//printf("granularity = %x\n",segdesc.granularity );
	//assert(cpu.segReg[sreg].limit == 0x0000001f );
	//assert(segdesc.granularity == 1);
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
}
