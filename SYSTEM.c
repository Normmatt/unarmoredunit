
#include <machine.h>
#include <stdrom.h>
#include "types.h"
#include "SYSTEM.h"

u16 cel_tbl[2] = {0x2000, 0x2000};
u16 map_tbl[2] = {0x1000, 0x1800};
u16 spr_tbl[2] = {0x0200, 0x2000};
u16 nbg_disp[2] = {0, 0};
u16 spr_disp = 0;
u16 nbg_xoff[2] = {0, 0};
u16 nbg_yoff[2] = {0, 0};
u8 lcd_option = 0;
u16 colpal[16][4] = {
	{ 0x0007, 0x0005, 0x0003, 0x0000, },
	{ 0x0007, 0x0006, 0x0005, 0x0004, },
	{ 0x0005, 0x0004, 0x0003, 0x0002, },
	{ 0x0003, 0x0002, 0x0001, 0x0000, },
	{ 0x0007, 0x0004, 0x0000, 0x0000, },
	{ 0x0003, 0x0004, 0x0005, 0x0007, },
	{ 0x0003, 0x0002, 0x0001, 0x0000, },
	{ 0x0007, 0x0005, 0x0003, 0x0000, },
	{ 0x0007, 0x0005, 0x0003, 0x0000, },
	{ 0x0007, 0x0006, 0x0005, 0x0004, },
	{ 0x0005, 0x0004, 0x0003, 0x0002, },
	{ 0x0003, 0x0002, 0x0001, 0x0000, },
	{ 0x0007, 0x0004, 0x0000, 0x0000, },
	{ 0x0006, 0x0004, 0x0002, 0x0000, },
	{ 0x0007, 0x0005, 0x0003, 0x0000, },
	{ 0x0000, 0x0004, 0x0007, 0x0000, },
};
u16 vram = 0;

struct TaskContext tsk1cont;
s16 fade[2];

u16 nbg_ddf(u16 a, u16 b)
{
	if(b == 1 || b == 0)
	{
		nbg_disp[a] = b;
		outpw(0,(spr_disp<<2) | (nbg_disp[1] << 1) | nbg_disp[0]);
		return b;
	}
	else
	{
		return nbg_disp[a];
	}
}

u16 spr_ddf(u16 a)
{
	if(a == 1 || a == 0)
	{
		spr_disp = a;
		outpw(0,(spr_disp<<2) | (nbg_disp[1] << 1) | nbg_disp[0]);
		return a;
	}
	else
	{
		return spr_disp;
	}
}

void nbg_scroll(u16 a, u16 b, u16 c)
{
	nbg_xoff[a] = b;
	nbg_yoff[a] = c;

	switch(a)
	{
		case 0:
		{
			outp2(0x10,b);
			outp2(0x11,c);
			break;
		}
		case 1:
		{
			outp2(0x12,b);
			outp2(0x13,c);
			break;
		}
	}
}

void cls(u16 a)
{
	u16 far *m = MK_FP(vram, map_tbl[a]);
	s16 i;

	for(i = 0x400; i != 0; i--)
	{
		*m++ = 0x9FF;
	}

	m = MK_FP(vram, cel_tbl[a] + 0x1ff0);
	for(i = 8; i != 0; i--)
	{
		*m++ = 0;
	}
}

void spr_cls()
{
	s16 i;
    
    for (i = 0; i < 0x80; i++)
    {
        put_sprite(i, 0xe0, 0x90, 0, 0);
    }
}

void SetPaletteRate(u16 a)
{
	u16 *f = fade;
	u16 c1,c2,c3,c4,c5;

	c1 = (((colpal[a][0] * f[0]) / 100) & 0xF);
	c2 = (((colpal[a][1] * f[0]) / 100) & 0xF);
	c3 = (((colpal[a][2] * f[0]) / 100) & 0xF);
	c4 = (((colpal[a][3] * f[0]) / 100) & 0xF);

	c5 = c1 << 12 | c2 << 8 | c3 << 4 | c4 << 0;

	switch(a)
	{
		case 0:
		{
			outpw(0x20,c5);
			break;
		}
		case 1:
		{
			outpw(0x22,c5);
			break;
		}
		case 2:
		{
			outpw(0x24,c5);
			break;
		}
		case 3:
		{
			outpw(0x26,c5);
			break;
		}
		case 4:
		{
			outpw(0x28,c5);
			break;
		}
		case 5:
		{
			outpw(0x2A,c5);
			break;
		}
		case 6:
		{
			outpw(0x2C,c5);
			break;
		}
		case 7:
		{
			outpw(0x2E,c5);
			break;
		}
		case 8:
		{
			outpw(0x30,c5);
			break;
		}
		case 9:
		{
			outpw(0x32,c5);
			break;
		}
		case 10:
		{
			outpw(0x34,c5);
			break;
		}
		case 11:
		{
			outpw(0x36,c5);
			break;
		}
		case 12:
		{
			outpw(0x38,c5);
			break;
		}
		case 13:
		{
			outpw(0x3A,c5);
			break;
		}
		case 14:
		{
			outpw(0x3C,c5);
			break;
		}
		case 15:
		{
			outpw(0x3E,c5);
			break;
		}
	}
}

void SetPalette(u16 a, u16 b, u16 c, u16 d, u16 e)
{
	colpal[a][0] = b & 7;
	colpal[a][1] = c & 7;
	colpal[a][2] = d & 7;
	colpal[a][3] = e & 7;
	SetPaletteRate(a);
}

void fade_run()
{
	s16 *f = fade;
	s16 i;
	if(f[1])
	{
		f[0] += f[1];
		if(f[0] < 0)
		{
			f[0] = 0;
			f[1] = 0;
		}
		if(f[0] > 100)
		{
			f[0] = 100;
			f[1] = 0;
		}
		for(i = 0; i < 16; i++)
		{
			SetPaletteRate(i);
		}
	}
}

void fade_tone(s16 unk)
{
	fade[0] = unk;
}

void fade_in(s16 unk)
{
    if(unk <= 0)
    {
        unk = -unk;
    }
    fade[1] = unk;
}

void fade_out(s16 unk)
{
    if(unk <= 0)
    {
        unk = -unk;
    }
    fade[1] = -unk;
}

void lcd_option_1(u16 a)
{
	lcd_option = (lcd_option & 0x1F) | (a << 5);
}

void lcd_option_2(u16 a)
{
	lcd_option = (lcd_option & 0x2F) | (a << 4);
}

void lcd_option_3(u16 a)
{
	lcd_option = (lcd_option & 0x37) | (a << 3);
}

void init_system()
{
	outp2(0x07, 0x32);
    outp2(0x10, 0x00);
    outp2(0x11, 0x00);
    outp2(0x12, 0x00);
    outp2(0x13, 0x00);
    outp2(0x04, 0x01);
    outp2(0x05, 0x00);
    outp2(0x06, 0x80);
    outpw(0x00, 0x00);
    fade_tone(100);
    fade_in(100);
    fade_run();
    outp2(0x14, 0x01);
    lcd_option = 4;
    outp2(0x15,lcd_option);
    outp2(0x1C, 0x20);
    outp2(0x1D, 0x64);
    outp2(0x1E, 0xA8);
    outp2(0x1F, 0xFC);
    interrupt_init();
    serial_init();
    sound_init();
    serial_send_cause(0);
    key_create_cause(0);
    casette_int_cause(0);
    serial_receive_cause(1);
    display_data_cause(0);
    v_brank_cnt_cause(1);
    v_brank_int_cause(1);
    h_brank_cnt_cause(0);
    ip_init();
}

