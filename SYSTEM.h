#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

struct TaskContext
{
    /* 0886 */ s16 unk0;
    /* 0888 */ task_pointer unk2[16];
    /* 08C8 */ task_pointer2 unk42[16];
    /* 0908 */ u16 unk82[16];
    /* 0928 */ u16 unkA2[16];
    /* 0948 */ u16 unkC2;
    /* 094A */ u16 unkC4;
    /* 094C */ u16 unkC6;
};

extern short cel_tbl[2];
extern short map_tbl[2];
extern short spr_tbl[2];
extern long nbg_disp;
extern short spr_disp;
extern long nbg_xoff;
extern long nbg_yoff;
extern short lcd_option;
extern short colpal[64];
extern unsigned char vram[276];
extern unsigned char com_user[1012];
extern unsigned char effect_tbl[382];
extern unsigned char bitmap_nbg[6];
extern unsigned char _ctype[257];
extern struct TaskContext tsk1cont;
extern s16 fade[2];

void nbg_ddf();
void spr_ddf();
void nbg_scroll();
void cls();
void spr_cls();
void SetPaletteRate();
void SetPalette();
void fade_run();
void fade_tone();
void fade_in(s16 unk);
void fade_out(s16 unk);
void lcd_option_1();
void lcd_option_2();
void lcd_option_3();
void init_system();

#endif
