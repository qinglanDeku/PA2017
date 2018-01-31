#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"
#include "memory/mmu/segment.h"
#include "memory/mmu/page.h"
#include "memory/mmu/tlb.h"
#define Cache_line_num 1024


typedef struct {
		 uint8_t valid;
		 uint16_t Tag;		//14bit
		 uint8_t data[64];
}CacheLine;

/*typedef struct{
	uint8_t valid;
	uint16_t Tag;		//14bit
}CacheLine_info;*/

void init_cache();

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);

void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache);


#endif