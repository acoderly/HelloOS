#ifndef _BASE_TYPE_H
#define _BASE_TYPE_H

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;

typedef char s8_t;
typedef short s16_t;
typedef int s32_t;
typedef long long s64_t;
typedef long sint_t;
typedef unsigned long uint_t;

typedef u64_t bool_t;

typedef char char_t;
typedef char_t* va_list_t;


#define NULL	0
#define TRUE    1
#define	FALSE	0
#define REGCALL __attribute__((regparm(3)))
#define ALIGN(x, aligned) (((x) + (aligned) - 1) & ~((aligned) -1))

#endif