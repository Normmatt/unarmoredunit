#ifndef SPRINTF_H
#define SPRINTF_H

#include "types.h"

extern void far *ssprintf;
extern const char far hex_num_tbl[];
extern const char far HEX_num_tbl[];
extern const unsigned long far dec_div_tbl[];
extern const unsigned long far hex_div_tbl[];
extern const unsigned long far bin_div_tbl[];

	
void print(u16 unk, u16 unk2, u16 unk3, u8 *unk4, u8 far font[]);
void bmp_print();
void bmp_print_next();
void hsprintf(char *fmt, ...);
void chr2str();
void bin2str();
void str2str();
void dec2str();
void hex2str();

#endif
