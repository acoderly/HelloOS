#ifndef _CPU_MEM_INFO_H
#define _CPU_MEM_INFO_H

#define HALT() __asm__ __volatile__("cli; hlt":::"memory")

void get_e820map_by_bios(e820map_t **e820map_ptr, u32_t *e820map_sz);
void get_e820map(machbootinfo_t* mbotinfo_ptr);
u64_t get_memsize(e820map_t *e820map_ptr, u32_t size);
void get_cpu_info(machbootinfo_t* mbotinfo_ptr);
void get_mem_info(machbootinfo_t* mbotinfo_ptr);
void init_boot_stage_pages(machbootinfo_t* mbotinfo_ptr);
int chk_cpuid();
int chk_cpu_longmode();

#endif