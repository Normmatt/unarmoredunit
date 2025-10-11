#ifndef UNISEL_H
#define UNISEL_H

#include "types.h"

struct UniselWork
{
    /* 00 */ void *unk0;
    /* 02 */ u16 unk2;
    /* 04 */ u16 unk4;
    /* 06 */ u16 unk6;
    /* 08 */ u16 unk8;
    /* 0A */ u16 unkA;
}; //Total 0x0C bytes

extern u8 far G_UNISE2_char_adr[];

void unisel_init();

#endif
