#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	/*printf("Please implement raise_intr()");
	assert(0);*/
	//printf("intr_no = %x\n", intr_no);
	OPERAND eflags, CS, EIP;
    eflags.data_size = 32;
    eflags.sreg = SREG_DS;
	eflags.type = OPR_MEM;
    eflags.val = cpu.eflags.val;
	
    CS.data_size = 16;
    CS.sreg = SREG_DS;
	CS.type = OPR_MEM;
    CS.val = cpu.cs.val;

    EIP.data_size = 32;
    EIP.sreg = SREG_DS;
	EIP.type = OPR_MEM;
    EIP.val = cpu.eip;

    cpu.esp -= 4;
    eflags.addr = cpu.esp;
    operand_write(&eflags);
    
    cpu.esp -= 4;
    CS.addr = cpu.esp;
    operand_write(&CS);

    cpu.esp -= 4;
    EIP.addr = cpu.esp;
    operand_write(&EIP);

	uint32_t intaddr = cpu.idtr.base + intr_no * 8;
	//memcpy(&intaddr, hw_mem + cpu.idtr.base, sizeof(intaddr));
	//printf("intaddr = %x\n", intaddr);
	uint32_t offset, offset1, offset2;
	uint16_t selector;
	
	offset1 = laddr_read(intaddr,2);
	offset2 = laddr_read(intaddr + 6, 2);
	//memcpy(&offset1, hw_mem + intaddr, 2);
	
	offset = offset1 + (offset2 << 16);
	
	selector = laddr_read(intaddr + 2,2);
	//memcpy(&selector, hw_mem + intaddr + 2, 2);
	//printf("offset1 = %x, offfset2 = %x, offset = %x, selector = %x\n", offset1, offset2, offset, selector);
	/*uint32_t baseaddr = cpu.gdtr.base + ((selector & 0xfff8)>>3) * 8;
	SegDesc segdesc;
	printf("baseaddr = %x\n", cpu.gdtr.base);
	memcpy(&segdesc, hw_mem + baseaddr, sizeof(segdesc));
	printf("here\n");
	uint32_t base = segdesc.base_15_0 + (segdesc.base_23_16 <<  16) + (segdesc.base_31_24 << 24);*/
	if(intr_no > 80)	cpu.eflags.IF = 0;
	cpu.cs.val = selector;
	cpu.eip = offset;
//	printf("cpu.eip = %x\n", cpu.eip);

#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
