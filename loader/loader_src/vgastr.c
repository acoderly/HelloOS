#include "ctl.h"

__attribute__((section(".data"))) cursor_t cursor;

void init_curs()
{
    cursor.vmem_start = VGASTR_RAM_BASE;
    cursor.vmem_end = VGASTR_RAM_END;
    cursor.cvmemadr = 0;
    cursor.x = 0;
    cursor.y = 0;
    return;
}

void close_curs()
{
    out_u8(VGACTRL_REG_ADR, VGACURS_REG_INX);
    out_u8(VGACTRL_REG_DAT, VGACURS_CLOSE);
    return;
}

void set_curs(u32_t x, u32_t y)
{
    cursor.x = x;
    cursor.y = y;
    return;
}

void clear_screen(u16_t srrv)
{
    cursor.x = 0;
    cursor.y = 0;

    u16_t *vga_ram_base = (u16_t*)VGASTR_RAM_BASE;
    
    for (uint_t i = 0; i < 2001; i++)
    {
        vga_ram_base[i] = srrv;
    }

    close_curs();
    return;
}

void update_current_curs(cursor_t *cp, u32_t c_flg)
{

	if (c_flg == VGACHAR_LR_CFLG)
	{
		cp->y++;
		cp->x = 0;
		if (cp->y > 24)
		{
			cp->y = 0;
			clear_screen(VGADP_DFVL);
		}

		return;
	}
	if (c_flg == VGACHAR_DF_CFLG)
	{
		cp->x += 2;
		if (cp->x > 159)
		{
			cp->x = 0;
			cp->y++;
			if (cp->y > 24)
			{
				cp->y = 0;
				clear_screen(VGADP_DFVL);
			}
			return;
		}
	}
	return;
}


char *numberk(char_t *str, uint_t n, sint_t base)
{
    register char_t *p;
    char_t strbuf[36];
    p = &strbuf[36];
    *--p = 0;

    if (n == 0)
    {
        *--p = '0';
    }
    else
    {
        do
        {
            *--p = "0123456789abcdef"[n%base];
        } while (n/=base);
    }

    while (*p != 0)
    {
        *str++ = *p++;
    }
    return str;
}

void strwrite(char_t *str, cursor_t *cursptr)
{
    uint_t straddr = cursptr->x + cursptr->y * 80 * 2;
    char_t *p_strdst = (char_t*)(cursptr->vmem_start + straddr);
    u32_t tfindx = FALSE;
    while(*str)
    {
        if (*str == 10)
        {
            tfindx = TRUE;
            str++;
            if (*str == 0)
            {
                break;
            }
        }

        update_current_curs(cursptr, VGACHAR_DF_CFLG);

        *p_strdst = *str++;
        p_strdst+=2;
    }

    if(tfindx == TRUE)
    {
        update_current_curs(cursptr, VGACHAR_LR_CFLG);
    }

    return;
}

static char_t *strcpy(char_t *dst, char_t *src)
{
    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
    return dst;
}

void vsprintfk(char_t *buf, const char_t *fmt, va_list_t args)
{
    char_t *p = buf;
    va_list_t next_arg = args;
    while (*fmt)
    {
        if (*fmt != '%')
        {
            *p++ = *fmt++;
            continue;
        }
        fmt++;
        switch (*fmt)
        {
        case 'x':
            p = numberk(p, *((long *)next_arg), 16);
            next_arg += sizeof(long);
            fmt++;

            break;
        case 'd':
            p = numberk(p, *((long *)next_arg), 10);
            next_arg += sizeof(long);
            fmt++;
            break;
        case 's':
            p = strcpy(p, (char_t *)(*((long *)next_arg)));
            next_arg += sizeof(long);
            fmt++;
            break;
        default:
            break;
        }
    }
    *p = 0;
    return;
}

void kprint(const char_t *fmt, ...)
{
    char_t buf[512];
 
    va_list_t arg = (va_list_t)((char_t *)(&fmt) + sizeof(long));

    vsprintfk(buf, fmt, arg);
    strwrite(buf, &cursor);
    return;
}