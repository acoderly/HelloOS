#include "ctl.h"

void loader_entry()
{
    init_curs();
    close_curs();
    set_curs(0, 1);
    kprint("HelloOS, I am loader entry\n");
    init_machbootinfo();
    return;
}

void DEBUG()
{
    kprint("HelloOS, I am realmode_call_entry xxxsxxx\n");
}