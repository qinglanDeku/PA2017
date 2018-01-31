#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE)  // number of page tables to cover the vmem

PTE vptable[SCR_SIZE / PAGE_SIZE] align_to_page;

PDE* get_updir();

void create_video_mapping() {
	
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */

	//panic("please implement me");
	PDE *pdir = get_updir();
	PTE *ptable = (PTE *)va_to_pa(vptable);
	uint32_t pframe_idx;
	/* make all PDE invalid */

	/* fill PDEs and PTEs */
	pframe_idx = VMEM_ADDR;
	
	pdir[0].val = make_pde(ptable);
	//pdir[pdir_idx + SCR_SIZE / PT_SIZE].val = make_pde(ptable);
	for (int pageNo  = 0; pageNo< (SCR_SIZE + PAGE_SIZE - 1)/ PAGE_SIZE; pageNo++) {
			vptable[VMEM_ADDR / PAGE_SIZE + pageNo].val = make_pte(pframe_idx);
			pframe_idx += PAGE_SIZE;
	}

		
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

