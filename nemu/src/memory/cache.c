#include"memory/cache.h"
#include "cpu/cpu.h"
#include"nemu.h"
#include "device/mm_io.h"
#include "memory/memory.h"
#include <memory.h>
#include <stdio.h>

CacheLine L1_DCache[Cache_line_num];

void init_cache(){
		 for( int i = 0; i < Cache_line_num; i++)
				L1_DCache[i].valid = 0;
}


uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache){
		//printf("Here!");
		uint32_t ret =  0;
		//uint32_t ret2 = 0;
		uint8_t ret_s[4];
		bool info = false;	// *******using to break circle
		//memcpy(&ret2, hw_mem + paddr, len);
		/*uint32_t group_num = (paddr & 0x00001fc0)>>6;
		uint32_t Tag = paddr >> 13;
		uint32_t in_addr = paddr & 0x0000003f;		//addr in block(or line)
		uint32_t line = group_num * 8 ;// 8-way set associative
		uint32_t begin_addr = paddr & 0xffffffc0;	// block begin addr*/
		//printf("group = %x, tag = %x, in_addr = %x, paddr = %x\n",group_num, Tag, in_addr, paddr);
		for(int k = 0; k< len; k++){
			info = false;
			uint32_t group_num = ((paddr+ k) & 0x00001fc0)>>6;
			uint32_t Tag = (paddr + k) >> 13;
			uint32_t in_addr = (paddr + k )& 0x0000003f;		//addr in block(or line)
			uint32_t line = group_num * 8 ;// 8-way set associative
			uint32_t begin_addr = (paddr + k )& 0xffffffc0;	// block begin addr
			for(int i = line; i<line + 8;i++){
				if(cache[i].Tag == Tag){
					if(cache[i].valid == 1)
					{	/*memcpy(&ret2, hw_mem + paddr, len);
						if(in_addr + len >= 64){
							uint32_t begin = begin_addr + 64;
							memcpy(cache[i+1].data, hw_mem + begin, 64);
							Info_Cache[i+1].valid = 1;
							Info_Cache[i+1].Tag = begin >> 13;
						}
						memcpy(&ret, cache[i].data + in_addr, len);
						if(ret2 != ret){
							printf("cache = %x, hw = %x, len = %x, in_addr = %d\n NO.1.1\n", ret, ret2, len, in_addr);
							getchar();
						}*/
						ret_s[k] = cache[i].data[in_addr];
						info  = true;
					}
				else{			//change the line of cache
					
					/*for(int j = 0; j < 64 ; j++)
						cache[i].data[j] =  hw_mem[begin_addr + j];*/
					memcpy(cache[i].data, hw_mem + begin_addr, 64);
					cache[i].valid = 1;
					ret_s[k] = cache[i].data[in_addr];
					info = true;
					/*memcpy(&ret, cache[i].data + in_addr, len);
					memcpy(&ret2, hw_mem + paddr, len);
					if(ret2 != ret){
						printf("cache = %x, hw = %x, len = %x, in_addr = %d\n NO.1.2\n", ret, ret2, len, in_addr);
						getchar();
						}*/
				}
				//printf("here!");
				
			//	return ret;
			}		
		}
		//printf("%p, %p\n",cache[line].data, cache[line].data + 1);
		
		if(info == true)	continue;
		//************if not matched the tag
		uint8_t count_v = 0;		// count valid line;
		uint16_t empty_line = 9;
		for(int i = line ; i< line + 8; i++){
			if(cache[i].valid == 0)
				{	empty_line = i;
					break;
				}
			else count_v++;
		}

		if(count_v < 8){		// there are at least one empty line
			cache[empty_line].valid = 1;
			cache[empty_line].Tag = Tag;
			/*for(int j = 0; j < 64; j++)
				cache[empty_line].data[j] = hw_mem[begin_addr + j];*/
			memcpy(cache[empty_line].data, hw_mem + begin_addr, 64);
			ret_s[k] = cache[empty_line].data[in_addr];
			/*memcpy(&ret, cache[empty_line].data + in_addr, len);
			memcpy(&ret2, hw_mem + paddr, len);
			if(ret2 != ret){
			printf("cache = %x, hw = %x\nNO.2\n", ret, ret2);
			getchar();
			}
			return ret;*/
		}
		else{				//there is no empty line
			cache[line+3].Tag = Tag;
			cache[line+3].valid = 1;
			/*for(int j = 0; j<64; j++)
				cache[line+3].data[j] = hw_mem[begin_addr +j];*/
			memcpy(cache[line+3].data, hw_mem + begin_addr, 64);
			ret_s[k] = cache[line+3].data[in_addr];
			/*memcpy(&ret, cache[line+3].data + in_addr, len);
			memcpy(&ret2 ,hw_mem + paddr, len);
		if(ret != ret2){
		printf("cache = %x, hw = %x\nNO.3\n", ret, ret2);
		getchar();
			}
			return ret;*/
			}
		}
		for(int i = 0; i<len; i++)
			ret += ((uint32_t)ret_s[i] << (i*8));
		/*if(ret2 != ret){
							printf("cache = %x, hw = %x, len = %x\n NO.1.1\n", ret, ret2, len);
							getchar();
						}*/
		return ret;		

}

void cache_write(paddr_t paddr, size_t len, uint32_t data , CacheLine* cache){
//	printf("There");
	/*paddr_t group_num = (paddr & 0x00001fc0)>>6;
	paddr_t Tag = paddr >> 13;
	paddr_t in_addr = paddr & 0x0000003f;		//addr in block(or line)
	uint32_t line = group_num * 8 ;// 8-way set associative
	paddr_t begin_addr = paddr & 0xffffffc0;	// block begin addr*/
	uint8_t data_s[4];
	data_s[0] = data & 0x000000ff;
	data_s[1] = (data & 0x0000ff00) >> 8;
	data_s[2] = (data & 0x00ff0000) >> 16;
	data_s[3] = (data & 0xff000000) >> 24;

for(int k = 0; k< len; k++){
	paddr_t group_num = ((paddr + k) & 0x00001fc0)>>6;
	paddr_t Tag = (paddr + k )>> 13;
	paddr_t in_addr = (paddr + k) & 0x0000003f;		//addr in block(or line)
	uint32_t line = group_num * 8 ;// 8-way set associative
	//paddr_t begin_addr = paddr & 0xffffffc0;	// block begin addr
	for(int i = line; i<line + 8;i++){
		if(cache[i].Tag == Tag){
			if(cache[i].valid == 1){
				/*if(in_addr + len >= 64){
						uint32_t begin = begin_addr + 64;
						memcpy(cache[i+1].data, hw_mem + begin, 64);
						Info_Cache[i+1].valid = 1;
						Info_Cache[i+1].Tag = begin >> 13;
				}
				memcpy(cache[i].data + in_addr, &data, len);
				return;*/
				cache[i].data[in_addr] = data_s[k];
			}
			/*else{			//change the line of cache
				
				for(int j = 0; j < 64 ; j++)
					cache[i].data[j] =  hw_mem[begin_addr + j];
				cache[i].valid = 1;
				ret = cache[i].data[in_addr];
				return ret;
			}*/
		}
	}
}
	memcpy(hw_mem + paddr, &data, len);

}


