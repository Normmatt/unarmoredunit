#ifndef TITLE_H
#define TITLE_H

#include "types.h"

struct TitleWork {
    /* 00 */ void *unk0;
    /* 02 */ s16 unk2;
    /* 04 */ s16 unk4;
    /* 06 */ u8 unk6;
    /* 07 */ u16 unk7;
    /* 09 */ u16 unk9;
    /* 0B */ u16 unkB[8];
    /* 1B */ s16 unk1B;
}; //Total 0x1D bytes

extern u8 far G_TITLE_char_adr[];

void title_init(void *buf);

#endif
