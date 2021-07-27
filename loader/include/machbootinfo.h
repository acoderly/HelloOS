#ifndef _MACHBOOTPARMS_H
#define _MACHBOOTPARMS_H

void init_machbootinfo();
void machbootinfo_t_init(machbootinfo_t* mbinf_ptr);
void adrzone_is_ok(u64_t sadr, u64_t slen, u64_t kadr, u64_t klen);
int chkadr_is_ok(machbootinfo_t *mbinf_ptr, u64_t chkadr_start, u64_t chkadr_sz);

#endif