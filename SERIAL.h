#ifndef SERIAL_H
#define SERIAL_H

#include "types.h"

typedef struct sSerialInfo {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u8* unkA;
} sSerialInfo_t;

extern sSerialInfo_t rcv_work;
extern u8 receive_buf[630];
extern u16 mother_child;

void serial_init();
void serial_receive();
void serial_in();
void serial_out_sub();
void serial_out();
u16 serial_ver_info();
u16 serial_exist();
s16 serial_in_frag();

/*static void near unk_2F8B();
static s16 near unk_2FB2();
static void near unk_2FD3();
static void near unk_2FFF();
static void near unk_3097();*/

#endif
