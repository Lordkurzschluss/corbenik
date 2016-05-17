#ifndef EXPORTED_H
#define EXPORTED_H

#include "headers.h"

#define stdout ((void*)0)
#define stderr ((void*)2)

extern int strlen(const char *string);
extern int isprint(char c);
extern void memcpy(void *dest, const void *src, size_t size);
extern void memmove(void *dest, const void *src, size_t size);
extern void memset(void *dest, const int filler, size_t size);
extern int memcmp(const void *buf1, const void *buf2, const size_t size);
extern void strncpy(void *dest, const void *src, const size_t size);
extern int strncmp(const void *buf1, const void *buf2, const size_t size);
extern int atoi(const char *str);
extern uint8_t* memfind (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen);

extern void putc(void* buf, const int c);
extern void puts(void* buf, const char *string);
extern void fprintf(void* channel, const char* format, ...);

extern firm_h* get_firm();
extern exefs_h* get_firm_proc9_exefs();

extern firm_h* get_agb();
extern exefs_h* get_agb_proc9_exefs();

extern firm_h* get_twl();
extern exefs_h* get_twl_proc9_exefs();

#endif