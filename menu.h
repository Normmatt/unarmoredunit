#ifndef MENU_H
#define MENU_H

#include "types.h"

struct MenuWork
{
    /* 00 */ void *unk0;
    /* 02 */ u16 unk2;
    /* 04 */ s16 unk4;
    /* 06 */ s16 unk6;
    /* 08 */ s16 unk8;
    /* 0A */ s16 unkA;
    /* 0C */ s16 unkC;
    /* 0E */ s16 unkE;
    /* 10 */ s16 unk10;
    /* 12 */ u16 unk12;
    /* 14 */ u16 unk14;
    /* 16 */ s16 unk16;
    /* 18 */ s16 unk18;
    /* 1A */ s16 unk1A;
    /* 1C */ s16 unk1C;
}; //Total 0x1E bytes

extern u8 far G_MENU_char_adr[];

void menu_init();

#endif
