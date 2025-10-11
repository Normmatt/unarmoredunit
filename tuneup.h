#ifndef TUNEUP_H
#define TUNEUP_H

#include "types.h"

struct TuneupWork
{
    /* 00 */ u16 unk0;
    /* 02 */ u16 unk2;
    /* 04 */ u16 unk4;
    /* 06 */ u16 unk6;
    /* 08 */ u16 unk8;
    /* 0A */ s8 unkA[8];
    /* 12 */ s8 *unk12;
}; //Total 0x14 bytes

void tuneup_init();

#endif
