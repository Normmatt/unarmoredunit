#ifndef STAGESEL_H
#define STAGESEL_H

#include "types.h"

struct StageSelWork
{
    /* 00 */ s16 unk0;
    /* 02 */ s16 unk2;
}; //Total 0x4 bytes

extern u8 far G_STGSEL_char_adr[];
extern u8 far G_AU1_char_adr[];
extern u8 far G_AU2_char_adr[];
extern u8 far G_AU3_char_adr[];

void stage_select_init();

#endif
