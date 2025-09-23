#ifndef CONSOLE_H
#define CONSOLE_H

struct ConsoleWork
{
    /* 00 */ u16 unk0;
    /* 02 */ u8 unk2;
    /* 03 */ u8 unk3;
    /* 04 */ u8 unk4;
    /* 05 */ u8 unk5;
    /* 06 */ u8 unk6;

    /* 07 */ u8 unk7[0x7F];

    /* 86 */ u8 unk86;
    /* 87 */ u8 unk87;
}; //Total 0x88 bytes

void console_init();

#endif
