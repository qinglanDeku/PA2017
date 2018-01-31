#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include"memory/cache.h"

uint8_t hw_mem[MEM_SIZE_B];

extern CacheLine L1_DCache[];
//extern CacheLine_info Info_Cache[];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	//printf("paddr = %x\n",paddr);
	memcpy(&ret, hw_mem + paddr, len);
	//printf("boom6!\n");
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	int NO = is_mmio(paddr);
	if(NO == -1){
#ifdef CACHE_ENABLED

		ret = cache_read( paddr, len, L1_DCache);
#else
	//printf("boom5!\n");
	//printf("paddr = %x\n", paddr);
		ret = hw_mem_read(paddr, len);
	//printf("ret = %x\n", ret);
#endif
		return ret;
	}
	else{
		ret = mmio_read(paddr, len, NO);

		return ret;
	}
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data){
	int NO = is_mmio(paddr);
	if( NO == -1){
#ifdef CACHE_ENABLED
		cache_write(paddr, len, data, L1_DCache);
#else
		hw_mem_write(paddr, len, data);
#endif
	}
	else{
		mmio_write(paddr, len, data, NO);
	}
}


uint32_t laddr_read(laddr_t laddr, size_t len) {
	//printf("boom4!\n");
	//printf("laddr = %x\n", laddr);
	//getchar();
	assert(len == 1 || len == 2 || len == 4 );
	if(cpu.cr0.pg == 1 && cpu.cr0.pe == 1){
		//assert(0);	
		if(1){				//laddr/(1024*4) == (laddr + len) / (1024 * 4)
		//laddr = len;
		//uint32_t p = laddr;
		
		//printf("laddr = %d\n", addr);
		//assert(laddr/1024/4 == (laddr + len) / 1024 / 4);
		paddr_t paddr = page_translate(laddr);
		//printf("laddr = %x\n", laddr);
		return paddr_read(paddr,len);
		}
		else{
			//printf("here\n");
			//printf("boom2!");
			uint8_t prelen = 1024 * 4 - laddr%(1024 * 4);
			uint8_t taillen = len - prelen;
			paddr_t paddr1 = page_translate(laddr);
			paddr_t paddr2 = page_translate(laddr + prelen);

			return paddr_read(paddr1, prelen) + (paddr_read(paddr2, taillen) << (8 * prelen));
		}
	}
	//printf("boom1!!\n");
	return paddr_read(laddr, len);
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4 );
	if(cpu.cr0.pg == 1 && cpu.cr0.pe == 1){
		if(1){			//no page missing
		//printf("laddr = %d\n", laddr);
		paddr_t paddr = page_translate(laddr);
		paddr_write(paddr, len, data);
		}
		else{
		//printf("boom2!");
			uint8_t prelen = 1024 * 4 - laddr%(1024 * 4);
			uint8_t taillen = len - prelen;
			uint32_t data1 = (data << (8 *taillen)) >> (8 * taillen);
			uint32_t data2 = (data >>(8 * prelen)) << (8 * prelen);
			paddr_t paddr1 = page_translate(laddr);
			paddr_t paddr2 = page_translate(laddr + prelen);

			paddr_write(paddr1, prelen, data1);
			paddr_write(paddr2, taillen, data2);
		}
		return;
	}
	paddr_write(laddr, len, data);
}


uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
		assert(0);
		return laddr_read(vaddr, len);
#else

		if(cpu.cr0.pe == 1){
			
			vaddr = segment_translate(vaddr, sreg);
			//printf("boom2!\n");
			//printf("vaddr=%x\n", vaddr);
			return laddr_read(vaddr, len);
		}
		else return laddr_read(vaddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
		assert(0);
		laddr_write(vaddr, len, data);
#else
		if(cpu.cr0.pe == 1){
			//printf("\n pe == 1!!! \n");
			//printf("here!");
			vaddr = segment_translate(vaddr, sreg);
			laddr_write(vaddr, len, data);
			}
		else	laddr_write(vaddr, len, data);
#endif
}

void init_mem() {
	// clear the memory on initiation
	init_cache();
	memset(hw_mem, 0, MEM_SIZE_B);

#ifdef TLB_ENABLED
	
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	//printf("boom!1\n");
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t * get_mem_addr() {
	return hw_mem;
}
