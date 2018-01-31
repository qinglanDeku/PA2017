#include "cpu/cpu.h"
	
void set_PF(uint32_t result){
		int count_bit_1=0;
		for(int i=0;i<8;i++){
		if(result%2==1)
			count_bit_1++;
		result = result>>1;
	}
	if(count_bit_1%2==0)	cpu.eflags.PF = 1;
	else cpu.eflags.PF = 0;
}

void set_ZF(uint32_t result){
	cpu.eflags.ZF=(result==0);
}

void set_SF(uint32_t result){
		cpu.eflags.SF = sign(result);
}

void set_OF_add(uint32_t result, uint32_t src, uint32_t dest){
	if(sign(src) == sign(dest)){
		if(sign(src) != sign(result))
				cpu.eflags.OF=1;
		else 
				cpu.eflags.OF=0;
	}
	else	cpu.eflags.OF=0;
			
}

void set_CF_add(uint32_t result, uint32_t src){
		cpu.eflags.CF= (result<src);
}

void set_CF_adc(uint32_t result, uint32_t src, uint32_t dest){
	if(src != 0 && dest !=0)
			cpu.eflags.CF = ((result <= src) || (result <= dest));
	else
			cpu.eflags.CF = (result<src || result < dest );
}

void set_CF_sub(uint32_t src, uint32_t dest){
	cpu.eflags.CF = (dest < src);
}

void set_OF_sub(uint32_t result, uint32_t src, uint32_t dest){
	if(sign(src) == sign(dest))
			cpu.eflags.OF = 0;
	else if(src == 0)
			cpu.eflags.OF = 0;
	else{
		if (sign(dest) == 1)
			cpu.eflags.OF = ((int32_t)result >= (int32_t)dest);
		else 
			cpu.eflags.OF = ((int32_t)result <= (int32_t)dest);
		}	
}

void set_OF_sbb(uint32_t result, uint32_t src, uint32_t dest){
	if(sign(src) == sign(dest)){
		cpu.eflags.OF = 0;
	}
	else if(src == 0){ 
		if(cpu.eflags.CF ==0)	cpu.eflags.OF =0;
		else cpu.eflags.OF = ( (int32_t)result >=(int32_t)dest);
	}
	else{
			if (sign(dest) == 1)
			cpu.eflags.OF = ((int32_t)result > (int32_t)dest);
		else 
			cpu.eflags.OF = ((int32_t)result < (int32_t)dest);
		}	
}

void set_CF_sbb(uint32_t src, uint32_t dest){
	if(cpu.eflags.CF == 0)
		cpu.eflags.CF = (dest < src);
	else{
		if(dest < dest -1)
				cpu.eflags.CF = 1;
		else 
				cpu.eflags.CF = (dest-1 < src);
	}
}

uint32_t alu_add(uint32_t src, uint32_t dest) {
	uint32_t res = src+dest;

	set_CF_add(res,src);
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	set_OF_add(res,src,dest);

	return res;
}

uint32_t alu_adc(uint32_t src, uint32_t dest) {
	uint32_t res=src+dest+cpu.eflags.CF;

	set_PF(res);
	set_ZF(res);
	set_SF(res);
	set_CF_adc(res,src,dest);
	set_OF_add(res,src,dest);

	return res;
}


uint32_t alu_sub(uint32_t src, uint32_t dest) {
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
	int	versrc = ~src + 1;
	int res = versrc + dest;
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	set_OF_sub(res, src, dest);
	set_CF_sub(src, dest);	
	
	
	return res;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest) {
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
	uint32_t res = ~src + dest + 1 - cpu.eflags.CF ;
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	set_OF_sbb(res,src,dest);
	set_CF_sbb(src,dest);
	return res;
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
		uint64_t res = 0;
		switch(data_size){
			case 8:
					src &= 0x000000ffu;
					dest &= 0x000000ffu;
					res = (uint16_t)(src * dest);
					res &= 0x0000ffffu;
					cpu.eflags.SF = ((res&0x00008000u) != 0);
					cpu.eflags.ZF = (res == 0);
					cpu.eflags.CF = ((res&0x0000ff00u) != 0);
					cpu.eflags.OF = cpu.eflags.CF;
					break;

			case 16:
					src &= 0x0000ffffu;
					dest &= 0x0000ffffu;
					res = src * dest;
					cpu.eflags.SF = ((res&0x80000000u) != 0);
					cpu.eflags.ZF = (res ==0);
					cpu.eflags.CF = ((res&0xffff0000u) != 0);
					cpu.eflags.OF = cpu.eflags.CF;
					break;

			case 32:
					res =(uint64_t)src*(uint64_t)dest;
					cpu.eflags.SF = ((res&0x8000000000000000u) != 0);
					cpu.eflags.ZF = (res == 0);
					cpu.eflags.CF = ((res&0xffffffff00000000u) !=0);
					cpu.eflags.OF = cpu.eflags.CF;
					break;
			default: assert(0);
		}
		set_PF(res);
		return res;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	int64_t res = 0;
		switch(data_size){
			case 8:
					src = (int8_t)src;
					dest = (int8_t)dest;
					res = (int16_t)(src * dest);
					break;

			case 16:
					src = (int16_t)src;
					dest = (int16_t)dest;
					res = src * dest;
					break;

			case 32:
					res = (int64_t)src*(int64_t)dest;
					break;
			default: assert(0);
		}
		return res;	
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
		uint32_t res=0;
		cpu.eflags.CF =0;
		cpu.eflags.OF =0;
		if(src == 0)
				assert(0);
		switch(data_size){
			case 8: {  
					 uint16_t dest_2 =(dest&0x000000000000ffffu);
				   	   uint8_t src_2 =(src&0x00000000000000ffu);
					   if(dest_2/(uint16_t)src_2 > 255)	assert(0);
					   res = (uint8_t)(dest_2/src_2);
					   cpu.eflags.SF = ((res&0x00000080u) != 0);
					   cpu.eflags.ZF = (res == 0);
					   break;
					}
			case 16:{   
					uint32_t dest_2 =(dest&0x00000000ffffffffu);
						uint16_t src_2 = (src&0x000000000000ffffu);
						if(dest_2/(uint32_t)src_2 > 65535)	assert(0);
						res = (uint16_t)(dest_2/src_2);
						cpu.eflags.SF = ((res&0x00008000u) !=0);
						cpu.eflags.ZF = (res == 0);
						break;
					}
			case 32:{
					uint32_t src_2 = (src&0x00000000ffffffffu);
						if(dest/(uint64_t)src_2 > 4294967295) assert(0);
						res = (uint32_t)(dest/src_2);
						cpu.eflags.SF = ((res&0x80000000) != 0);
						cpu.eflags.ZF = (res == 0);
						break;
					}
			default: assert(0);
	
		}
		set_PF(res);
		return res;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {

		int32_t res=0;
		cpu.eflags.CF =0;
		cpu.eflags.OF =0;
		if(src == 0)
				assert(0);
		switch(data_size){
			case 8: {  
					   int16_t dest_2 =dest;
				   	   int8_t src_2 =src;
					   if(dest_2/(int16_t)src_2 > 127||dest_2/(int16_t)src_2 < -128)	assert(0);
					   res = (int8_t)(dest_2/src_2);
					   cpu.eflags.SF = ((res&0x00000080u) != 0);
					   cpu.eflags.ZF = (res == 0);
					   break;
					}
			case 16:{   
						int32_t dest_2 = dest;
						int16_t src_2 = src;
						if(dest_2/(int32_t)src_2 > 32767||dest_2/(int32_t)src_2 < -32768)	assert(0);
						res = (int16_t)(dest_2/src_2);
						cpu.eflags.SF = ((res&0x00008000u) !=0);
						cpu.eflags.ZF = (res == 0);
						break;
					}
			case 32:{
						int32_t src_2 = src;
						if(dest/(int64_t)src_2 > 2147483647||dest/(int64_t)src_2 < -2147483648) assert(0);
						res = (int32_t)(dest/src_2);
						cpu.eflags.SF = ((res&0x80000000) != 0);
						cpu.eflags.ZF = (res == 0);
						break;
					}
			default: assert(0);
	
		}
		set_PF(res);
		return res;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	return dest%src;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	return dest%src; 
}

uint32_t alu_and(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t res = dest & src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	return res;
}

uint32_t alu_xor(uint32_t src, uint32_t dest) {
//	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
//	assert(0);
	uint32_t res = dest ^ src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	return res;
}

uint32_t alu_or(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t res = dest | src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res);
	set_SF(res);
	return res;
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t res = 0;
	if(src<=0)
			return dest;
	switch(data_size){
		case 8 :{
				uint32_t dest_2 =  dest&0x000000ffu;
				if(src > 1){	
					dest_2 = dest_2<<(src-1);				// get CF
					cpu.eflags.CF = ((dest_2 & 0x00000080u) != 0);
					dest_2 = dest_2<<1;
					cpu.eflags.SF = ((dest_2 & 0x00000080u) != 0);
					cpu.eflags.ZF = ((dest_2 & 0x000000ffu) == 0);
				}
				else if(src == 1){
					cpu.eflags.CF = ((dest_2 & 0x00000080u) != 0);
					dest_2 <<= 1;
					cpu.eflags.SF = ((dest_2 & 0x00000080u) != 0);
					cpu.eflags.ZF = ((dest_2 & 0x000000ffu) == 0);
				}
			   	else assert(0);
				dest_2 = dest_2 & 0x000000ffu;
				dest &= 0xffffff00u;
				res = (dest | dest_2);
				set_PF(res);
				break;
		}
		case 16 :{
				uint32_t dest_2 = (dest&0x0000ffffu );
				if(src > 1){	
					dest_2 = dest_2<<(src-1);				// get CF
					cpu.eflags.CF = ((dest_2 & 0x00008000u) != 0);
					dest_2 = dest_2<<1;
					cpu.eflags.SF = ((dest_2 & 0x00008000u) != 0);
					cpu.eflags.ZF = ((dest_2 & 0x0000ffffu) == 0);
				}
				else if(src == 1){
					cpu.eflags.CF = ((dest_2 & 0x00008000u) != 0);
					dest_2 <<= 1;
					cpu.eflags.SF = ((dest_2 & 0x00008000u) != 0);
					cpu.eflags.ZF = ((dest_2 & 0x0000ffffu) == 0);
				}
				else assert(0);
				dest_2 = dest_2 & 0x0000ffffu;
				dest &= 0xffff0000u;
				res = (dest | dest_2);
				set_PF(res);
				break;
				 }
		case 32 :{
				uint32_t dest_2 = dest;
				if(src > 1){
					dest_2 = dest_2<<(src-1);				// get CF
					cpu.eflags.CF = ((dest_2 & 0x80000000u) != 0);
					dest_2 = dest_2<<1;
					
				}
				else if(src ==1){
						cpu.eflags.CF = ((dest_2 & 0x80000000u) !=0);
						dest_2 <<=1;
				}
				else assert(0);
				res = dest_2;
				set_PF(res);
				set_SF(res);
				set_ZF(res);
				break;
		}
		default :assert(0);	
	}
	//set_SF(res);
	//set_ZF(res);
	//set_PF(res);
	return res;
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	uint32_t dest_2;
	cpu.eflags.SF = 0;
	if(src <= 0)	return dest;
	switch(data_size){
		case 8:{
					dest_2 = dest&0x000000ffu;
			   		if(src == 1){
						cpu.eflags.CF = ((dest_2&0x00000001u) != 0);
						dest_2 >>= 1;
						cpu.eflags.ZF = (dest_2 ==0 );
						dest &= 0xffffff00u;
						res = dest|dest_2;
					}
					else {
						dest_2 >>= (src-1);
						cpu.eflags.CF = ((dest_2&0x00000001u) !=0);
						dest_2 >>= 1;
						cpu.eflags.ZF = (dest_2 ==0);
						dest &= 0xffffff00u;
						res = dest|dest_2;
					}
					break;
			   }
		case 16:{
					dest_2 = dest&0x0000ffffu;
					if(src == 1){
						cpu.eflags.CF = ( (dest_2&0x00000001u) != 0);
						dest_2 >>= 1;
						cpu.eflags.ZF = (dest_2 == 0);
						dest &= 0xffff0000;
						res = dest|dest_2;
					}
					else{
						dest_2 >>= (src-1);
						cpu.eflags.CF = ( (dest_2&0x00000001u) != 0);
						dest_2 >>= 1;
						cpu.eflags.ZF = (dest_2 ==0);
						dest &= 0xffff0000;
						res = dest|dest_2;
					}
					break;
				}
		case 32:{
					if(src ==1){
						cpu.eflags.CF = ((dest&0x00000001) != 0);
						dest >>= 1;
						cpu.eflags.ZF = (dest == 0);
						res = dest;
					}
					else {
						dest >>= (src-1);
						cpu.eflags.CF = ((dest&0x00000001) !=0);
						dest >>= 1;
						cpu.eflags.ZF = (dest == 0);
						res = dest;
					}
					break;
				}
		default: assert(0);
	}
		set_PF(res);
		return res;
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res=0;
	uint32_t dest_2;
	uint32_t signal;
	if(src <= 0)
			return dest;
	switch(data_size){
			case 8:{	dest_2 = dest&0x000000ffu;
						signal = ((dest_2&0x00000080u) != 0);
						cpu.eflags.SF = signal;
				   		if(src == 1){
							cpu.eflags.CF = ((dest_2&0x00000001u) != 0);
							dest_2 >>= 1;
							if(signal == 1)
									dest_2 |= 0x00000080u;
						    cpu.eflags.ZF = 	(dest_2 == 0);
							dest &= 0xffffff00u;
							res = dest|dest_2;
						}
						else{
							int8_t temp = dest&0xff;
							temp >>= (src-1);
							cpu.eflags.CF = ((temp&0x01) !=0);
							temp >>= 1;
							cpu.eflags.ZF = (temp == 0);
							dest &= 0xfffffff00u;
							res = dest|(uint8_t)temp;
						}
						break;
				   }
			case 16:{
						dest_2 = dest&0x0000ffffu;
						signal = ((dest_2&0x00008000u) != 0);
						cpu.eflags.SF = signal;
						if(src == 1){
							cpu.eflags.CF = ((dest_2&0x00000001u) !=0 );
							dest_2 >>= 1;
							if(signal == 1)
									dest_2 |= 0x00008000u;
							cpu.eflags.ZF = (dest_2 == 0);
							dest &= 0xffff0000u;
							res = dest|dest_2;
						}
						else{
							int16_t temp =dest&0xffffu;
							temp >>= (src-1);
							cpu.eflags.CF = ((temp&0x0001) != 0);
							temp >>= 1;
							cpu.eflags.ZF = (temp == 0);
							dest &= 0xffff0000u;
							res = dest|(uint16_t)temp;
						}
						break;
					}
			case 32:{
						signal = ((dest&0x80000000u) != 0);
						cpu.eflags.SF = signal;
						if(src == 1){
							cpu.eflags.CF = ((dest&0x00000001u) !=0);
							dest >>=1;
							if(signal == 1)
								dest |= 0x80000000;
							cpu.eflags.ZF = (dest ==0);
							res = dest;
						}
						else{
							int32_t temp=dest;
							temp >>= (src-1);
							cpu.eflags.CF = ((temp&0x00000001) != 0);
							temp >>= 1;
							cpu.eflags.ZF = (temp == 0);
							res =(uint32_t)temp;
						}
						break;
					}
			default: assert(0);
	}
		set_PF(res);
		return res;
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	return alu_shl(src, dest, data_size) ;
}
