#include "ctl.h"

void init_machbootinfo()
{
    machbootinfo_t *mbotinfo_ptr = MACHBOOTINFO_ADR;
    machbootinfo_t_init(mbotinfo_ptr);

    get_cpu_info(mbotinfo_ptr);
    get_mem_info(mbotinfo_ptr);

    return;
}

static void memset(void*src, u8_t value, uint_t src_len)
{
    u8_t* tmp = (u8_t*)src;
    for(uint_t i = 0; i < src_len; i++)
    {
        tmp[i] = value;
    }
    return;
}

void machbootinfo_t_init(machbootinfo_t* mbotinfo_ptr)
{
    memset(mbotinfo_ptr, 0, sizeof(machbootinfo_t));
    mbotinfo_ptr->machinfo_migc = 0;
    return;
}

void adrzone_is_ok(u64_t sadr, u64_t slen, u64_t kadr, u64_t klen)
{
    return;
}

int chkadr_is_ok(machbootinfo_t *mbotinfo_ptr, u64_t chkadr_start, u64_t chkadr_sz)
{
    return 0;
}
