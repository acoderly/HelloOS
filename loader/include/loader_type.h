#ifndef _LOADER_TYPE_H
#define _LOADER_TYPE_H


#define IMGHDR_ENDGIC 0xaaffaaffaaffaaff
#define IMGHDR_VERSION 0xffaaffaaffaaffaa

#define REALMODEFUNC_FILE_PHYADR 0x1000
#define IMG_FILE_PHYADR 0x4000000
#define LOADER_PHYADR 0x200000
#define KERNEL_IMG_PHYADR 0x2000000
#define INIT_KSTACK_PHYADR (0x90000-0x10)
#define INIT_KSTACK_SIZE 0x1000
#define IMGHEADER_OFF (0x1000)
#define IMGHEADER_ADR (IMG_FILE_PHYADR + IMGHEADER_OFF)

#define RAM_USABLE 1
#define RAM_RESERVED 2
#define RAM_ACPIREC 3
#define RAM_ACPINVS 4
#define RAM_AREACON 5

typedef struct s_e820
{
    u64_t segment_start; // start of memory segment
    u64_t segment_size; // size of memory segment
    u32_t segment_type; // type of memory segment
}__attribute__((packed)) e820map_t;



#define FHDR_MAX_FILE_NAME 192
//文件头描述符
typedef struct s_fhdr
{
    u64_t fhdr_type;
    u64_t fhdr_subtype;
    u64_t fhdr_status;
    u64_t fhdr_id;
    u64_t fhdr_intsfsoff;
    u64_t fhdr_intsfend;
    u64_t fhdr_frealsz;
    u64_t fhdr_fsum;
    char  fhdr_name[FHDR_MAX_FILE_NAME];
}fhdr_t;

//映像文件头描述符
typedef struct s_imghdr
{
    u64_t imghdr_mgic;
    u64_t imghdr_sfsum;//no used
    u64_t imghdr_sfsoff;//no used
    u64_t imghdr_sfeoff;//no used
    u64_t imghdr_sfrlsz;//no used
    u64_t imghdr_loader_start;
    u64_t imghdr_loader_end;
    u64_t imghdr_loader_size;
    u64_t imghdr_loader_sum;
    u64_t imghdr_fhdr_start;
    u64_t imghdr_fhdr_end;
    u64_t imghdr_fhdr_size;
    u64_t imghdr_fhdr_sum;
    u64_t imghdr_filedata_start;
    u64_t imghdr_filedata_end;
    u64_t imghdr_filedata_size;
    u64_t imghdr_filedata_sum;
    u64_t imghdr_padding;//no used
    u64_t imghdr_fhdr_num;
    u64_t imghdr_file_num;
    u64_t imghdr_endgic;
    u64_t imghdr_version;
}imghdr_t;


typedef struct s_MACHBOOTINFO
{
    u64_t   machinfo_migc; //LMOSMBSP//0
    u64_t   machinfo_checksum;
    u64_t   machinfo_kinitstack; //kernel stack addrress
    u64_t   machinfo_kinitstacksz; //kernel stack size
    u64_t   machinfo_imgphyadr; //image physical address
    u64_t   machinfo_imgsize;
    u64_t   machinfo_kimgphyadr;//kernel image physical address
    u64_t   machinfo_ksize;
    u64_t   machinfo_kversion;
    u64_t   machinfo_krunmode;
    u64_t   machinfo_kalldendpadr;
    u64_t   machinfo_nextwphyadr;
    u64_t   machinfo_fvrmphyadr;
    u64_t   machinfo_fvrmsz;
    u64_t   machinfo_cpumode;
    u64_t   machinfo_memsz;
    u64_t   machinfo_e820padr;
    u64_t   machinfo_e820nr;
    u64_t   machinfo_e820sz;
    u64_t   machinfo_e820expadr;
    u64_t   machinfo_e820exnr;
    u64_t   machinfo_e820exsz;
    u64_t   machinfo_memzonephyadr;
    u64_t   machinfo_memzonenr;
    u64_t   machinfo_memzonesz;
    u64_t   machinfo_memzonesum;
    u64_t   machinfo_memmappadr;
    u64_t   machinfo_memmapnr;
    u64_t   machinfo_memmapsz;
    u64_t   machinfo_memmapchksum;
    u64_t   machinfo_pml4padr;
    u64_t   machinfo_subpageslen;
    u64_t   machinfo_kpmapphymemsz;
    // u64_t   machinfo_ebdaphyadr;
    // mrsdp_t machinfo_mrsdp;
    // graph_t machinfo_ghparm;
}__attribute__((packed)) machbootinfo_t;

#define MACHBOOTINFO_ADR ((machbootinfo_t*)0x100000)

#define RLINTNR(x) (x*2)
void REGCALL realmode_call_entry(u16_t callint, u16_t val1, u16_t val2);

#endif