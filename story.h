#ifndef STORY_H
#define STORY_H

#include "types.h"

struct StoryWork
{
    /* 00 */ void *unk0;
    /* 02 */ s8 unk2;
    /* 03 */ u8 unk3;
    /* 04 */ u8 unk4;
    /* 05 */ u8 unk5;
    /* 06 */ u8 unk6;
    /* 07 */ u8 unk7;
    /* 08 */ u8 unk8;
    /* 09 */ u8 unk9;
    /* 0A */ u8 unkA;
    /* 0B */ u8 unkB;
    /* 0C */ u8 unkC;
    /* 0D */ u8 unkD;
    /* 0E */ u8 unkE;
    /* 0F */ u8 unkF;
    /* 10 */ u8 unk10;
    /* 11 */ u8 unk11;
    /* 12 */ u8 unk12;
    /* 13 */ u8 unk13;
    /* 14 */ u8 unk14;
    /* 15 */ u8 unk15;
    /* 16 */ u8 unk16;
    /* 17 */ u8 unk17;
    /* 18 */ u16 unk18;
    /* 1A */ u16 unk1A;
    /* 1C */ u16 unk1C;
    /* 1E */ u16 unk1E;
    /* 20 */ u16 unk20;
}; //Total 0x22 bytes

extern u8 far G_STORY_char_adr[];

void story_init();

#endif
