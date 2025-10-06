#ifndef LOGO_H
#define LOGO_H

struct LogoWork {
    s16 unk0;
    s16 unk2;
    s16 unk4;
}; //Total 0x6 bytes

void logo_init();
static void unk_842E6(struct LogoWork *a);

#endif
