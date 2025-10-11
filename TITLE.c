#include <machine.h>
#include "types.h"
#include "TITLE.h"
#include "SWAN_L_C.h"
#include "SWANMAIN.h"
#include "SYSTEM.h"
#include "SPRINTF.h"
#include "MEMORY.h"
#include "SOUND_CODE.h"
#include "PAD.h"

static char str0[] = "               ";
static char str1[] = "VERSION 000105D";
static char str2[] = "FREE PLAY      ";
static char str3[] = "ALL SAVE CLEAR!";
static char str4[] = "UNDEFINED!!    ";
static char str5[] = "               ";
static char str6[] = "TYPE 0         ";
static char str7[] = "No Suppoted    ";
static char str8[] = "--CLEAR--      ";

static const u8 far title_unk[] = {0,1,2,3,2,1};

static void unk_84041(struct TitleWork *work);

static void unk_83CEA(u16 a)
{
	a = title_unk[a];
	font_putXY(0, 18 + a, 12, 1, 8, 14, 1, G_TITLE_char_adr);
}

static void unk_83D28(s16 a, s16 b, u8 *c)
{
	for (; *c != 0; c++)
	{
		font_putXY((*c & 0xf) + 0xc, (*c >> 4) + 0x10, 1, 1, a, b, 1, G_TITLE_char_adr);
		if (*c == ' ')
		{
			put_cell_no(a << 3, b << 3, 1, get_bmp_cell_no(a, b, G_TITLE_char_adr));
		}
		a += 1;
	}
}

static void unk_83DB2()
{
	unk_83D28(0, 0, (u8*)str0);
}

static void unk_83DC1()
{
	unk_83D28(0, 0, (u8*)str1);
}

static void unk_83DD0()
{
	unk_83D28(0, 0, (u8*)str2);
}

static void unk_83DDF()
{
	unk_83D28(0, 0, (u8*)str3);
}

static void unk_83DEE()
{
	unk_83D28(0, 0, (u8*)str4);
}

static void unk_83DFD()
{
	unk_83D28(0, 0, (u8*)str5);
}

static void unk_83E0C()
{
	unk_83D28(0, 0, (u8*)str6);
}

static void unk_83E1B()
{
	unk_83D28(0, 0, (u8*)str7);
}

static void unk_83E2A()
{
	unk_83D28(0, 0, (u8*)str8);
	flash_clear();
}

static void unk_83E3E()
{
}

void title_init(void *buf)
{
	s16 i;
	s16 j;
	u16 val;
	u16 val2;
	struct TitleWork *work;

	task_delete();
	work = (struct TitleWork *)memalloc(sizeof (struct TitleWork));
	if (work != NULL)
	{
		task_append((task_pointer)unk_84041, (u16)work);
		work->unk0 = buf;
		work->unk2 = 0;
		work->unk4 = 0;
		work->unk6 = 0;
		work->unk7 = 0;
		work->unk9 = 0;
		for (i = 0; i < 8; i++)
		{
			work->unkB[i] = 0;
		}
		work->unk1B = 0;
		nbg_ddf(0, 0);
		nbg_ddf(1, 0);
		spr_ddf(0);
		font_load(1, G_TITLE_char_adr);
		val = get_bmp_cell_no(0x1b, 0x21, G_TITLE_char_adr);
		val |= 0x800;
		for (i = 0; i < 256; i += 8)
		{
			for (j = 0; j < 256; j += 8)
			{
				put_cell_no(j, i, 0, val);
				put_cell_no(j, i, 1, val);
			}
		}

		for (i = 0; i < 0x10; i += 1)
		{
			font_putXY(0, 0, 5, 2, 0, i << 1, 0, G_TITLE_char_adr);
		}

		font_putXY(5, 0, 0x17, 0x12, 5, 0, 1, G_TITLE_char_adr);
		font_putXYT(0, 0x16, 5, 9, 0, 2, 0xe00, 1, G_TITLE_char_adr);

		val2 = 0;
		for (i = 0; i < 9; i += 1)
		{
			for (j = 0; j < 5; j += 1)
			{
				val = get_bmp_cell_no(5 + j, 0x16 + i, G_TITLE_char_adr);
				put_sprite(val2++, j << 3, (i << 3) + 0x10, 0x2000 | val, 4);
			}
		}
		unk_83CEA(0);
		fade_tone(0);
		fade_out(100);
		fade_run();
		fade_in(10);
		nbg_ddf(0, 1);
		nbg_ddf(1, 1);
		spr_ddf(1);
		bgmreq(1);
	}
}

static void unk_84041(struct TitleWork *work)
{
	if((pad[0].unk4 & 0x800) && (work->unk7))
	{
		sereq(0x12);
		//Might be fake match
		work->unk1B = (work->unk1B - -4) % 5;

		switch(work->unk1B)
		{
			case 0:
			{
				unk_83DB2();
				break;
			}
			case 1:
			{
				unk_83DC1();
				break;
			}
			case 2:
			{
				unk_83DD0();
				break;
			}
			case 3:
			{
				unk_83DDF();
				break;
			}
			case 4:
			{
				unk_83DEE();
				break;
			}
		}
	}
	if((pad[0].unk4 & 0x200) && (work->unk7))
	{
		sereq(0x12);
		work->unk1B = (work->unk1B + 6) % 5;

		switch(work->unk1B)
		{
			case 0:
			{
				unk_83DB2();
				break;
			}
			case 1:
			{
				unk_83DC1();
				break;
			}
			case 2:
			{
				unk_83DD0();
				break;
			}
			case 3:
			{
				unk_83DDF();
				break;
			}
			case 4:
			{
				unk_83DEE();
				break;
			}
		}
	}
	if((pad[0].unk4 & 4) && (work->unk7))
	{
		sereq(0x10);

		switch(work->unk1B)
		{
			case 0:
			{
				unk_83DFD();
				break;
			}
			case 1:
			{
				unk_83E0C();
				break;
			}
			case 2:
			{
				unk_83E1B();
				break;
			}
			case 3:
			{
				unk_83E2A();
				break;
			}
			case 4:
			{
				unk_83E3E();
				break;
			}
		}
	}
	if((pad[0].unk4))
	{
		work->unkB[work->unk9] = pad[0].unk4;

		work->unk9 = (work->unk9 + 1) % 8;
		work->unk9; //Required for matching

		if((work->unkB[(work->unk9 - 1) % 8] & 0x200))
		{
			if((work->unkB[(work->unk9 - 2) % 8] & 0x800))
			{
				if((work->unkB[(work->unk9 - 3) % 8] & 0x400))
				{
					if((work->unkB[(work->unk9 - 4) % 8] & 0x400))
					{
						if((work->unkB[(work->unk9 - 5) % 8] & 0x400))
						{
							if((work->unkB[(work->unk9 - 6) % 8] & 0x100))
							{
								work->unk7 = 1;
								sereq(0x10);
							}
						}
					}
				}
			}
		}
	}
	if((pad[0].unk4 & 2))
	{
		sereq(10);
		memfree(work);
		task_delete();
		task_delete_fade(10);
	}
	work->unk4++;

	if (3 < work->unk4)
	{
		work->unk4 = 0;
		work->unk2 = (work->unk2 + 1) % 6;
		unk_83CEA(work->unk2);
	} 
	nbg_scroll(0, 0, ++work->unk6);
}







 