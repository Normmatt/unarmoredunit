#ifndef STORY_H
#define STORY_H

#include "types.h"

struct StoryWork
{
    /* 00 */ void *unk0;
    /* 02 */ s8 unk2;
    /* 03 */ s8 unk3;
    /* 04 */ s8 unk4;
    /* 05 */ u8 unk5;
    /* 06 */ u8 unk6;
    /* 07 */ u8 unk7;
    /* 08 */ u8 unk8;
    /* 09 */ u8 unk9;
    /* 0A */ u16 unkA;
    /* 0C */ u16 unkC;
    /* 0E */ u16 unkE;
    /* 10 */ u8 unk10;
    /* 11 */ u8 unk11;
    /* 12 */ u8 unk12;
    /* 13 */ u8 unk13;
    /* 14 */ u8 unk14;
    /* 15 */ u8 unk15;
    /* 16 */ u8 unk16;
    /* 17 */ u8 unk17;
    /* 18 */ u8 far *unk18;
    /* 1C */ u16 unk1C;
    /* 1E */ s16 unk1E;
    /* 20 */ s16 unk20;
}; //Total 0x22 bytes

extern u8 far G_STORY_char_adr[];

void story_init();

#endif
