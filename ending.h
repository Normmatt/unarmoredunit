#ifndef ENDING_H
#define ENDING_H

#include "types.h"

struct EndingWork
{
    /* 00 */ void *unk0;
    /* 02 */ u16 unk2;
    /* 04 */ u16 unk4;
    /* 06 */ u16 unk6;
    /* 08 */ u16 unk8;
}; //Total 0xA bytes

void ending_init();

#endif
