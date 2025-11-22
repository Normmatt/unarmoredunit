#ifndef M_GAME_H
#define M_GAME_H

#include "types.h"

struct MGameWorkSub
{
    /* 00 */ u8 unk00[2];
    /* 02 */ u16 unk02;
    /* 04 */ u16 unk04;
    /* 06 */ u8 unk06;
    /* 07 */ u8 unk07[4];
    /* 0B */ u16 unk0B;
    /* 0D */ u16 unk0D;
    /* 0F */ s16 unk0F;
    /* 11 */ u16 unk11;
    /* 13 */ s16 unk13;
    /* 15 */ s16 unk15;
    /* 17 */ s16 unk17[8];
};

struct MGameWork
{
    /* 00 */ void *unk0;
    /* 02 */ u8 unk4[0x45 - 0x2];

    /* 45 */ struct MGameWorkSub unk45[2];

    /* Struct? */
    /* 93 */ u16 unk93;
    /* 93 */ u16 unk95;
    /* 93 */ u16 unk97;
    /* 99 */ u8 unk99;

    /* 9A */ u8 unk9A;
    /* 9B */ u8 unk9B[0xA7 - 0x9B];
    /* A7 */ u16 unkA7;
    /* A9 */ u16 unkA9;
    /* AB */ u16 unkAB;
    /* AD */ u16 unkAD[2];
    /* B1 */ u16 unkB1;
    /* B3 */ u8 unkB3;
    /* B4 */ u8 unkB4[8][2];
    /* C4 */ u8 unkC4;
    /* C5 */ u8 unkC5;
    /* C6 */ u8 unkC6;
    /* C7 */ u8 unkC7;
    /* C8 */ u16 unkC8;
    /* C9 */ u8 unkCA[0xD8 - 0xCA];
    /* D8 */ u8 unkD8;
    /* D9 */ u8 unkD9;
    /* DA */ u16 unkDA;
    /* DC */ u16 unkDC;
    /* DE */ u8 unkDE[0x13B - 0xDE];
    /* 13B */ u16 unk13B[3][8];
    /* 16B */ u8 unk16B;
    /* 16C */ u8 unk16C;
    /* 16D */ u8 unk16D;
    /* 16E */ u8 unk16E;
    /* 16F */ u8 unk16F[2][3];
    /* 175 */ u8 unk175;
    /* 176 */ u8 unk176;
}; //Total 0x177 bytes

extern u16 mother_child;

void m_game_reinit();
void m_game_init(void *buf);
void item_used_se();
void item_used_create();
void m_game_main_lange_sub();

#endif
