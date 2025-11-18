#ifndef STORY_H
#define STORY_H

#include "types.h"

struct StoryWorkSub
{
    /* 0A */ u16 unk0;
    /* 0C */ u16 unk2;
    /* 0E */ u16 unk4;
    /* 10 */ u16 unk6;
    /* 12 */ u16 unk8;
    /* 14 */ u16 unkA;
    /* 16 */ u16 unkC;
    /* 18 */ u8 far *unkE;
    /* 1C */ u16 unk12;
    /* 1E */ s16 unk14;
    /* 20 */ s16 unk16;
}; //Total 0x18 bytes

struct StoryWork
{
    /* 00 */ void *unk0;
    /* 02 */ s8 unk2;
    /* 03 */ s8 unk3;
    /* 04 */ s8 unk4;
    /* 05 */ s8 unk5;
    /* 06 */ u8 unk6;
    /* 07 */ u8 unk7;
    /* 08 */ u8 unk8;
    /* 09 */ u8 unk9;
    /* 0A */ struct StoryWorkSub unkA;
}; //Total 0x22 bytes

extern u8 far G_STORY_char_adr[];

void story_init();

#endif
