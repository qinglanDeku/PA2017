#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	//printf("laddr = %x\n", laddr);
	paddr_t pagedirNo = (laddr >> 22) & 0x00003ff;
	paddr_t pagetabNo = (laddr >> 12) & 0x00003ff;
	paddr_t pageoffset = laddr & 0x00000fff;
	paddr_t pagebase = cpu.cr3.page_directory_base;
	//printf("the laddr = %x\n" , laddr);
	//printf("the pagebase = %x\n", pagebase);
	
	PDE page_dir;
	memcpy(&page_dir, hw_mem + pagebase*4*1024+ pagedirNo * 4, sizeof(PDE));
	//printf("page_dir = %x\n", page_dir.val);
	assert(page_dir.present == 1);
	//printf("page_dir = %x\n", page_dir.val);

	PTE page_tab;
	memcpy(&page_tab, hw_mem  + pagetabNo * 4+ page_dir.page_frame*4*1024, sizeof(PTE));
	//printf("page_tab = %x\n", page_tab.val);
	assert(page_tab.present == 1);

	return page_tab.page_frame*4*1024 + pageoffset;

#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
