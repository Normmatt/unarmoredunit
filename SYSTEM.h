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

extern short cel_tbl[];
extern short map_tbl[];
extern short spr_tbl[];
extern u16 nbg_disp[];
extern u16 spr_disp;
extern u16 nbg_xoff[];
extern u16 nbg_yoff[];
extern u8 lcd_option;
extern u16 colpal[16][4];
extern u8 vram[];
extern u8 com_user[];
extern u8 effect_tbl[];
extern u8 bitmap_nbg[];
extern u8 _ctype[];
extern struct TaskContext tsk1cont;
extern s16 fade[];

u16 nbg_ddf(u16 a, u16 b);
u16 spr_ddf(u16 a);
void nbg_scroll(u16 a, u16 b, u16 c);
void cls(u16 a);
void spr_cls();
void SetPaletteRate(u16 a);
void SetPalette(u16 a, u16 b, u16 c, u16 d, u16 e);
void fade_run();
void fade_tone();
void fade_in(s16 unk);
void fade_out(s16 unk);
void lcd_option_1(u16 a);
void lcd_option_2(u16 a);
void lcd_option_3(u16 a);
void init_system();

#endif
