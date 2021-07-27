#include "ctl.h"

static inline void kerror(char_t* err_str)
{
    kprint("Init loader die error:%s\n", err_str);
    while(1);
    return;
}

void get_e820map_by_bios(e820map_t **e820map_ptr, u32_t *e820map_sz)
{
    realmode_call_entry(RLINTNR(0), 0, 0);
    *e820map_sz = *((u32_t *)(E820MAP_NR));
    *e820map_ptr = (e820map_t*)(*((u32_t*)(E820MAP_ADR_ADR)));
    return;
}
void get_e820map(machbootinfo_t* mbotinfo_ptr)
{
    return;
}
u64_t get_memsize(e820map_t *e820map_arry, u32_t array_sz)
{
    u64_t len = 0;
    if (array_sz == 0 || e820map_arry == NULL)
    {
        return 0;
    }
    for (u32_t i = 0; i < array_sz; i++)
    {
        if (e820map_arry[i].segment_type == RAM_USABLE)
        {
            len += e820map_arry[i].segment_size;
        }
    }
    return len;
}

void get_cpu_info(machbootinfo_t* mbotinfo_ptr)
{
    if (0 == chk_cpuid())
    {
        kerror("Your CPU is not support CPUID sys is die!");
        HALT();
    }

    if (0 == chk_cpu_longmode())
    {
        kerror("Your CPU is not support CPUID sys is die!");
        HALT();
    }

    mbotinfo_ptr->machinfo_cpumode = 0x40;

    return;
}

void get_mem_info(machbootinfo_t* mbotinfo_ptr)
{
    e820map_t *ret_e820map=NULL;
    u32_t ret_e820map_sz = 0;
    kprint("Entry get_mem_info\n");
    get_e820map_by_bios(&ret_e820map, &ret_e820map_sz);
    if(ret_e820map_sz == 0)
    {
        kerror("can't get e820map");
    }
    kprint("get_mem_info: e820map_adr:%x, e820map_sz:%d", ret_e820map, ret_e820map_sz);
    return;
}

void init_boot_stage_pages(machbootinfo_t* mbotinfo_ptr)
{
    return;
}
int chk_cpuid()
{
    int rets = 0;
    __asm__ __volatile__(
        "pushfl \n\t"
        "popl %%eax \n\t"
        "movl %%eax,%%ebx \n\t"
        "xorl $0x0200000,%%eax \n\t"
        "pushl %%eax \n\t"
        "popfl \n\t"
        "pushfl \n\t"
        "popl %%eax \n\t"
        "xorl %%ebx,%%eax \n\t"
        "jz 1f \n\t"
        "movl $1,%0 \n\t"
        "jmp 2f \n\t"
        "1: movl $0,%0 \n\t"
        "2: \n\t"
        : "=c"(rets)
        :
        :);
    return rets;
}
int chk_cpu_longmode()
{
    int rets = 0;
    __asm__ __volatile__(
        "movl $0x80000000,%%eax \n\t"
        "cpuid \n\t"
        "cmpl $0x80000001,%%eax \n\t"
        "setnb %%al \n\t"
        "jb 1f \n\t"
        "movl $0x80000001,%%eax \n\t"
        "cpuid \n\t"
        "bt $29,%%edx  \n\t" // long mode  support 位
        "setcb %%al \n\t"
        "1: \n\t"
        "movzx %%al,%%eax \n\t"
        : "=a"(rets)
        :
        :);
    return rets;
}