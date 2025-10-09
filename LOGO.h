#ifndef LOGO_H
#define LOGO_H

#include "types.h"

struct LogoWork {
    /* 00 */ s16 unk0;
    /* 02 */ s16 unk2;
    /* 04 */ s16 unk4;
}; //Total 0x6 bytes

void logo_init();
static void unk_842E6(struct LogoWork *a);

#endif
