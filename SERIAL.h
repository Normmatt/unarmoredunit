#ifndef SERIAL_H
#define SERIAL_H

#include "types.h"

typedef struct sSerialInfo {
    /* 00 */ u16 unk0;
    /* 02 */ u16 unk2;
    /* 04 */ u16 unk4;
    /* 06 */ u16 unk6;
    /* 08 */ u16 unk8;
    /* 0A */ u8* unkA;
} sSerialInfo_t; //Total 0xC bytes

extern sSerialInfo_t rcv_work;  /*0D80*/
extern u8 receive_buf[260];  /*0D8C*/

void serial_init();
void serial_receive();
void serial_in();
void serial_out_sub();
void serial_out();
u16 serial_ver_info();
u16 serial_exist();
s16 serial_in_frag();

/*static void near unk_82F8B();
static s16 near unk_82FB2();
static void near unk_82FD3();
static void near unk_82FFF();
static void near unk_83097();*/

#endif
