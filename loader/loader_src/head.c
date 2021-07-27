#include "ctl.h"

void head_entry()
{
    init_curs();
    close_curs();
    clear_screen(VGADP_DFVL);
    kprint("HelloOS, I'm head_entry %x\n", &head_entry);

    write_loaderfile();
    write_realmodefuncfile();
    return;
}
static sint_t m2mcpy(void *src, void *dst, sint_t len)
{
    if(dst == NULL || src == NULL || len < 1)
    {
        return 0;
    }
    
    u8_t * s = (u8_t*)src, *d = (u8_t*)dst;
    
    if (s < d)
    {
        for(sint_t i = (len - 1); i >= 0; i--)
        {
            d[i] = s[i];
        }
        return len;
    }

    if (s > d)
    {
        for (sint_t i = 0 ; i < len; i++)
        {
            d[i] = s[i];
        }
        return len;
    }
    
    if(s==d)
    {
        return len;
    }
    return 0;

}

void error(char_t *err_str)
{
    kprint("Head die error:%s\n", err_str);
    while(1);
    return;
}

void write_realmodefuncfile()
{
    fhdr_t *realmodefunc_fhdr = find_file("realmodefunc.bin");
    if(realmodefunc_fhdr == NULL)
    {
        error("can no find realmodefunc.bin");
    }

    m2mcpy((void*)((u32_t)(realmodefunc_fhdr->fhdr_intsfsoff + IMG_FILE_PHYADR)),
            (void*)(REALMODEFUNC_FILE_PHYADR),(sint_t)(realmodefunc_fhdr->fhdr_frealsz));
}

void write_loaderfile()
{
    fhdr_t *loader_fhdr = find_file("loader.bin");
    if(loader_fhdr == NULL)
    {
        error("can no find loader.bin");
    }

    m2mcpy((void*)((u32_t)(loader_fhdr->fhdr_intsfsoff + IMG_FILE_PHYADR)),
            (void*)(LOADER_PHYADR),(sint_t)(loader_fhdr->fhdr_frealsz));
    
    return;
}

static int strcmpl(const char_t *a, const char_t *b)
{
    while (*b && *a && (*b == *a))
    {
        b++;
        a++;
    }

    return *b - *a;
}

fhdr_t *find_file(char_t *fname)
{
    imghdr_t *imghdr = (imghdr_t*)(IMGHEADER_ADR);
    if (imghdr->imghdr_endgic != IMGHDR_ENDGIC ||
        imghdr->imghdr_version != IMGHDR_VERSION ||
        imghdr->imghdr_fhdr_num < 2 ||
        imghdr->imghdr_file_num < 2)
    {
        kprint("Raw: %x\n", *((u64_t*)(IMGHEADER_ADR)));
        kprint("imghdr->imghdr_endgic: %x\n", imghdr->imghdr_endgic);
        kprint("imghdr->imghdr_fhdr_num: %d\n", imghdr->imghdr_fhdr_num);
        kprint("imghdr->imghdr_file_num: %d\n", imghdr->imghdr_file_num);
        error("can not find image header struct.");
    }

    s64_t fhdr_idx = -1;
    fhdr_t *fhdr_start = (fhdr_t*)((u32_t)(imghdr->imghdr_fhdr_start) + IMG_FILE_PHYADR);

    for (u64_t i = 0; i < imghdr->imghdr_fhdr_num; i++)
    {
        if (strcmpl(fname, fhdr_start[i].fhdr_name) == 0)
        {
            fhdr_idx = (s64_t)i;
            goto out;
        }
    }
out:
    if (fhdr_idx == -1)
    {
        error("can not find file.");
    }
    return &fhdr_start[fhdr_idx];

}
