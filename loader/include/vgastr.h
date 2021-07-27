#ifndef _VGASTR_H
#define _VGASTR_H

void init_curs();
void set_curs(u32_t x, u32_t y);
void update_current_curs(cursor_t *cp, u32_t c_flg);
void close_curs();
void clear_screen(u16_t srrv);

char *numberk(char_t *str, uint_t n, sint_t base);

void strwrite(char_t *str, cursor_t *cursptr);

void vsprintfk(char_t *buf, const char_t *fmt, va_list_t args);
void kprint(const char_t *fmt, ...);


#endif