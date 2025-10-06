#ifndef M_GAME_H
#define M_GAME_H

#include "types.h"

struct MGameWork
{
    /* 00 */ void *unk0;
    /* 02 */ u8 unk4[0x4B - 0x2];
    /* 4B */ u8 unk4B;
    /* 4C */ u8 unk4C[0x50 - 0x4C];
    /* 50 */ u16 unk50;
    /* 52 */ u16 unk52;
    /* 54 */ u8 unk54[0x5C - 0x54];
    /* 5C */ u16 unk5C[(0x72 - 0x5C) / 2];
    /* 72 */ u8 unk72;
    /* 73 */ u8 unk73[0x7B - 0x73];
    /* 7B */ u16 unk7B;
    /* 73 */ u8 unk7D[0xA7 - 0x7D];
    /* A7 */ u8 unkA7;
    /* A8 */ u8 unkA8;
    /* A9 */ s8 unkA9;
    /* B3 */ u8 unkAA[0xB3 - 0xAA];
    /* B3 */ u8 unkB3;
    /* B4 */ u8 unkB4[0x177 - 0xB4];
}; //Total 0x177 bytes

extern u16 mother_child;

void m_game_reinit();
void m_game_init(void *buf);
void item_used_se();
void item_used_create();
void m_game_main_lange_sub();

#endif
