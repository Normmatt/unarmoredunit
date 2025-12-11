#include <machine.h>
#include "types.h"
#include "menu.h"
#include "MEMORY.h"
#include "SWAN_L_C.h"
#include "SWANMAIN.h"
#include "SYSTEM.h"
#include "IP_MES.h"
#include "SERIAL.h"
#include "SOUND_CODE.h"
#include "unisel.h"
#include "m_game.h"
#include "PAD.h"

static void unk_89FB9();
static void near unk_8A696(struct MenuWork* work);
static void near unk_8AC60(struct MenuWork* work);
static void near unk_8AE35(struct MenuWork* work);
static void near unk_8B134(struct MenuWork* work);
static void unk_8B17B();
static void near unk_8B2E1(struct MenuWork* work, u16 mode);
static void near unk_8B3B1(struct MenuWork* work);

static void near unk_89B05(struct MenuWork* work)
{
	s16 i;
	s16 j;
	u16 val;

	if (work->unk2)
	{
		work->unk16 += (work->unk16 < 32) * 2;
	}
	else
	{
		work->unk16 -= (work->unk16 > 0) * 2;
	}

	if (work->unk2)
	{
		work->unk18 += (work->unk18 < 32) * 2;
	}
	else
	{
		work->unk18 -= (work->unk18 > 0) * 2;
	}

	if (work->unk8 > 0)
	{
		work->unk1A += (work->unk1A < 24) * 2;
	}
	else
	{
		work->unk1A -= (work->unk1A > -16) * 2;
	}

	if (work->unk8 < 4)
	{
		work->unk1C -= (work->unk1C > 104) * 2;
	}
	else
	{
		work->unk1C += (work->unk1C < 144) * 2;
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			val = get_bmp_cell_no(2 + j, 0x26 + i, G_MENU_char_adr);
			put_sprite(i * 2 + j, 0xc0 + work->unk16 + j * 8, i * 8 + work->unk1A, 0x2000 | val, 4);
		}
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			val = get_bmp_cell_no(0x18 + j, 0x26 + i, G_MENU_char_adr);
			put_sprite(4 + j + i * 2, 0xc0 + work->unk18 + j * 8, i * 8 + work->unk1C, 0x2000 | val, 4);
		}
	}
}

static void near unk_89CAD(struct MenuWork* work, s16 b, s16 c, s16 d, u16 e)
{
	s16 val = (d / 10);
	if (val)
	{
		font_putXYT(3 + val * 2, 0x38, 2, 4, b >> 3, c >> 3, e, 1, G_MENU_char_adr);
	}
	else
	{
		font_putXYT(1, 0x38, 2, 4, b >> 3, c >> 3, e, 1, G_MENU_char_adr);
	}
	val = (d % 10);
	font_putXYT(3 + val * 2, 0x38, 2, 4, (b >> 3) + 2, c >> 3, e, 1, G_MENU_char_adr);
}

void menu_init(void *buf)
{
	s32 i;
	s32 j;
	struct MenuWork *work;

	task_delete();
	work = (struct MenuWork*)memalloc(sizeof (struct MenuWork));

	if(work)
	{
		task_append((task_pointer)unk_89FB9, (u16)work);
		work->unk0 = buf;
		work->unk2 = 0;
		work->unk4 = 0;
		work->unk6 = 0;
		work->unk8 = 0;
		work->unkA = 0;
		work->unkC = 0;
		work->unk16 = 0;
		work->unk18 = 0;
		work->unk1A = 0xFFF0;
		work->unk1C = 0x0090;
		work->unk12 = 0;
		work->unk14 = 0;
		mother_child = 0;

		nbg_ddf(0, 0);
		nbg_ddf(1, 0);
		spr_ddf(0);
		spr_cls();
		font_load(1, G_MENU_char_adr);

		for(i = 0; i < 32; i++)
		{
			for(j = 0; j < 32; j++)
			{
				font_putXY(0, 0, 1, 1, j, i, 0, G_MENU_char_adr);
			}
		}

		font_putXY(0, 0, 0x1c, 0x12, 0, 0, 0, G_MENU_char_adr);
		font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);

		{
			u8 menu_data[] = {
				0x00, 0x01, 0xA8, 0xC0,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x10, 0x00,
			};

			ip_clear(menu_data);
		}
		unk_89B05(work);
		fade_tone(0);
		fade_out(100);
		fade_run();
		fade_in(10);
		nbg_scroll(0, 0, 0);
		nbg_scroll(1, 0, 0);
		nbg_ddf(0, 1);
		nbg_ddf(1, 1);
		spr_ddf(1);
		bgmreq(2);
	}
}

static void unk_89FB9(struct MenuWork* work)
{
/*	u8 val1;
	u16 val2;

	if (work->unk12)
	{
		nbg_scroll(0, 0, 0xFF - (rand() & 1));

		if (work->unk12 == 0x24)
		{
			SetPalette(0, 6, 4, 2, 0);
		}

		if (work->unk12 == 0x21)
		{
			SetPalette(0, 7, 5, 3, 0);
		}

		work->unk12--;

		if (work->unk12 == 0)
		{
			nbg_scroll(0, 0, 0);
		}
	}
	else
	{
		if (rand() % 99 == 0)
		{
			work->unk12 = 0x24;
		}
	}

	switch(work->unk2)
	{
		case 0:
		{
			if ((work->unk8 & 1))
			{
				work->unk8 += work->unkA;
				font_putXYT(4, 0x24 + work->unk8 * 2, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
				font_putXYT(4, 0x24 + work->unk8 * 2 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
			}
			else if ((pad[0].unk4 & 4))
			{
				SAVE_DATA_START[0x07] = (work->unk8 >> 1) + work->unk6;
				SAVE_DATA_START[0x08] = 0;
				switch( (work->unk8 >> 1) + work->unk6)
				{
					case 0:
					{
						sereq(10);
						nbg_scroll(0, 0, 0);
						SetPalette(0, 7, 5, 3, 0);
						memfree(work);
						task_delete();
						task_append((task_pointer)unisel_init, 0);
						task_delete_fade(10);
						break;
					}
					case 1:
					{
						sereq(10);
						nbg_scroll(0, 0, 0);
						SetPalette(0, 7, 5, 3, 0);
						memfree(work);
						task_delete();
						task_append((task_pointer)unisel_init, 0);
						task_delete_fade(10);
						break;
					}
					case 2:
					{
						val1 = com_user;
						if ((val1 != 2) && (val1 != 1))
						{
							sereq(0xc);
						}
						else
						{
							sereq(10);
							unk_8B134(work);
						}
						break;
					}
					case 3:
					{
						sereq(10);
						work->unk2 = 1;
						work->unkC = 0;
						font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
						font_putXYT(4, 0x30, 0x14, 4, 4, 3, 0x800, 1, G_MENU_char_adr);
						font_putXYT(4, 0x3c, 0x14, 4, 4, 7, 0x800, 1, G_MENU_char_adr);

						if (SAVE_DATA_START[0x04])
						{
							font_putXYT(0xc, 0x44, 2, 4, 0xc, 7, 0x800, 1, G_MENU_char_adr);
						}
						else
						{
							font_putXYT(0xc, 0x44, 2, 4, 0x12, 7, 0x800, 1, G_MENU_char_adr);
						}

						font_putXYT(4, 0x40, 0x14, 4, 4, 0xb, 0xe00, 1, G_MENU_char_adr);

						if (SAVE_DATA_START[0x05])
						{
							font_putXYT(0xc, 0x44, 2, 4, 0xc, 0xb, 0xe00, 1, G_MENU_char_adr);
						}
						else
						{
							font_putXYT(0xc, 0x44, 2, 4, 0x12, 0xb, 0xe00, 1, G_MENU_char_adr);
						}

						break;
					}
					case 4:
					{
						sereq(10);
						work->unk2 = 4;
						work->unkC = 0;
						work->unkE = 0;
						work->unk10 = 0;
						font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
						font_putXYT(4, 0x34, 0x14, 4, 4, 3, 0x800, 1, G_MENU_char_adr);
						font_putXYT(4, 0x3c, 8, 4, 4, 7, 0x800, 1, G_MENU_char_adr);
						unk_89CAD(work, 0x98, 0x38, work->unkE, 0x800);
						font_putXYT(4, 0x40, 8, 4, 4, 0xb, 0xe00, 1, G_MENU_char_adr);
						unk_89CAD(work, 0x98, 0x58, work->unk10, 0xe00);
						break;
					}
				}
			}
			else if ((pad[0].unk4 & 8))
			{
				sereq(0xb);
			}
			else if ((pad[0].unk4 & 0x100))
			{
				sereq(0xc);
				font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0xe00, 1, G_MENU_char_adr);
				if (work->unk6 > 0)
				{
					work->unk6--;
				}
				else if (0 < work->unk8)
				{
					work->unk6--;
				}

				if (work->unk6 < 0)
				{
					work->unk6 = 0;
					work->unk8--;
					work->unkA = 0xffff;
					font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
				}
				else
				{
					font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
				}
			}
			else if ((pad[0].unk4 & 0x400))
			{
				sereq(0xc);
				font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0xe00, 1, G_MENU_char_adr);
				if (work->unk6 < 2)
				{
					work->unk6++;
				}
				else if (work->unk8 < (SAVE_DATA_START[0x06] * 2 + 2))
				{
					work->unk6++;
				}
				
				if (work->unk6 > 2)
				{
					work->unk6 = 2;
					work->unk8++;
					work->unkA = 1;
					font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
				}
				else
				{
					font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
				}
			}
			break;
		}
		case 1:
		{
			unk_8A696(work);
			break;
		}
		case 2:
		{
			unk_8AC60(work);
			break;
		}
		case 3:
		{
			unk_8B3B1(work);
			break;
		}
		case 4:
		{
			unk_8AE35(work);
			break;
		}
	}
	unk_89B05(work);

	//This mixes up SI and BX and is the only diff
	work->unk4 = (work->unk4 + 1) & 1;*/

	rand; //Force include
	SetPalette; //Force include
	sereq; //Force include
	memfree; //Force include
	task_delete_fade; //Force include
	unisel_init; //Force include
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("CMP	[SI+0x12].W,0x0000");
	ASM_INLINE("JZ	_8A02C");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("CALLF	rand_, SEG rand_");
	ASM_INLINE("AND	AX,0x0001");
	ASM_INLINE("MOV	CX,0x00FF");
	ASM_INLINE("SUB	CX,AX");
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("CMP	[SI+0x12].W,0x0024");
	ASM_INLINE("JNZ	_89FFA");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0006");
	ASM_INLINE("MOV	CX,0x0004");
	ASM_INLINE("MOV	DX,0x0002");
	ASM_INLINE("CALLF	SetPalette_, SEG SetPalette_");
	ASM_INLINE("ADD	SP,0x0002");
ASM_INLINE("_89FFA:");
	ASM_INLINE("CMP	[SI+0x12].W,0x0021");
	ASM_INLINE("JNZ	_8A016");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0007");
	ASM_INLINE("MOV	CX,0x0005");
	ASM_INLINE("MOV	DX,0x0003");
	ASM_INLINE("CALLF	SetPalette_, SEG SetPalette_");
	ASM_INLINE("ADD	SP,0x0002");
ASM_INLINE("_8A016:");
	ASM_INLINE("DEC	[SI+0x12].W");
	ASM_INLINE("CMP	[SI+0x12].W,0x0000");
	ASM_INLINE("JNZ	_8A040");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("JMP	_8A040");
ASM_INLINE("_8A02C:");
	ASM_INLINE("CALLF	rand_, SEG rand_");
	ASM_INLINE("MOV	BX,0x0063");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("TEST	DX,DX");
	ASM_INLINE("JNZ	_8A040");
	ASM_INLINE("MOV	[SI+0x12].W,0x0024");
ASM_INLINE("_8A040:");
	ASM_INLINE("MOV	AX,[SI+0x02].W");
	ASM_INLINE("CMP	AX,0x0004");
	ASM_INLINE("JNZ	_8A04B");
	ASM_INLINE("JMP	_8A67C");
ASM_INLINE("_8A04B:");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JNZ	_8A053");
	ASM_INLINE("JMP	_8A675");
ASM_INLINE("_8A053:");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JNZ	_8A05B");
	ASM_INLINE("JMP	_8A66E");
ASM_INLINE("_8A05B:");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JNZ	_8A063");
	ASM_INLINE("JMP	_8A667");
ASM_INLINE("_8A063:");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_8A06A");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A06A:");
	ASM_INLINE("TEST	[SI+0x08].W,0x0001");
	ASM_INLINE("JZ	_8A0EE");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[SI+0x0A].W");
	ASM_INLINE("ADD	[BX+0x08].W,AX");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x000C");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,[SI+0x06].W");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A0EE:");
	ASM_INLINE("TEST	[0x0956].W,0x0004");
	ASM_INLINE("JNZ	_8A0F9");
	ASM_INLINE("JMP	_8A46A");
ASM_INLINE("_8A0F9:");
	ASM_INLINE("MOV	AX,[SI+0x08].W");
	ASM_INLINE("SAR	AX,1");
	ASM_INLINE("ADD	AX,[SI+0x06].W");
	ASM_INLINE("MOV	[0x1E07].B,AL");
	ASM_INLINE("MOV	[0x1E08].B,0x00");
	ASM_INLINE("MOV	AX,[SI+0x08].W");
	ASM_INLINE("SAR	AX,1");
	ASM_INLINE("ADD	AX,[SI+0x06].W");
	ASM_INLINE("CMP	AX,0x0004");
	ASM_INLINE("JNZ	_8A119");
	ASM_INLINE("JMP	_8A375");
ASM_INLINE("_8A119:");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JNZ	_8A121");
	ASM_INLINE("JMP	_8A1F1");
ASM_INLINE("_8A121:");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JNZ	_8A129");
	ASM_INLINE("JMP	_8A1CD");
ASM_INLINE("_8A129:");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_8A181");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_8A135");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A135:");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0007");
	ASM_INLINE("MOV	CX,0x0005");
	ASM_INLINE("MOV	DX,0x0003");
	ASM_INLINE("CALLF	SetPalette_, SEG SetPalette_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unisel_init_");
	ASM_INLINE("MOV	BX,SEG unisel_init_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	task_delete_fade_, SEG task_delete_fade_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A181:");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0007");
	ASM_INLINE("MOV	CX,0x0005");
	ASM_INLINE("MOV	DX,0x0003");
	ASM_INLINE("CALLF	SetPalette_, SEG SetPalette_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unisel_init_");
	ASM_INLINE("MOV	BX,SEG unisel_init_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	task_delete_fade_, SEG task_delete_fade_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A1CD:");
	ASM_INLINE("MOV	AL,[0x020C].B");
	ASM_INLINE("CMP	AL,0x02");
	ASM_INLINE("JZ	_8A1E2");
	ASM_INLINE("CMP	AL,0x01");
	ASM_INLINE("JZ	_8A1E2");
	ASM_INLINE("MOV	AL,0x0C");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A1E2:");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_8B134_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A1F1:");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	[SI+0x02].W,0x0001");
	ASM_INLINE("MOV	[SI+0x0C].W,0x0000");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0012");
	ASM_INLINE("MOV	CX,0x001C");
	ASM_INLINE("MOV	DX,0x0012");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x0030");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x003C");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("CMP	[0x1E04].B,0x00");
	ASM_INLINE("JZ	_8A2B8");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x0044");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A2E4");
ASM_INLINE("_8A2B8:");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x0044");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
ASM_INLINE("_8A2E4:");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x0040");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("CMP	[0x1E05].B,0x00");
	ASM_INLINE("JZ	_8A346");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x0044");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A346:");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x0044");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A375:");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	[SI+0x02].W,0x0004");
	ASM_INLINE("MOV	[SI+0x0C].W,0x0000");
	ASM_INLINE("MOV	[SI+0x0E].W,0x0000");
	ASM_INLINE("MOV	[SI+0x10].W,0x0000");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0012");
	ASM_INLINE("MOV	CX,0x001C");
	ASM_INLINE("MOV	DX,0x0012");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x0034");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x003C");
	ASM_INLINE("MOV	CX,0x0008");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	BX,0x0098");
	ASM_INLINE("MOV	CX,0x0038");
	ASM_INLINE("MOV	DX,[SI+0x0E].W");
	ASM_INLINE("CALL	unk_89CAD_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x000B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,0x0040");
	ASM_INLINE("MOV	CX,0x0008");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	BX,0x0098");
	ASM_INLINE("MOV	CX,0x0058");
	ASM_INLINE("MOV	DX,[SI+0x10].W");
	ASM_INLINE("CALL	unk_89CAD_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A46A:");
	ASM_INLINE("TEST	[0x0956].W,0x0008");
	ASM_INLINE("JZ	_8A47C");
	ASM_INLINE("MOV	AL,0x0B");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A47C:");
	ASM_INLINE("TEST	[0x0956].W,0x0100");
	ASM_INLINE("JNZ	_8A487");
	ASM_INLINE("JMP	_8A56E");
ASM_INLINE("_8A487:");
	ASM_INLINE("MOV	AL,0x0C");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,[SI+0x06].W");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("CMP	[SI+0x06].W,0x0000");
	ASM_INLINE("JLE	_8A4DA");
	ASM_INLINE("DEC	[SI+0x06].W");
	ASM_INLINE("JMP	_8A4E3");
ASM_INLINE("_8A4DA:");
	ASM_INLINE("CMP	[SI+0x08].W,0x0000");
	ASM_INLINE("JLE	_8A4E3");
	ASM_INLINE("DEC	[SI+0x06].W");
ASM_INLINE("_8A4E3:");
	ASM_INLINE("CMP	[SI+0x06].W,0x0000");
	ASM_INLINE("JGE	_8A52A");
	ASM_INLINE("MOV	[SI+0x06].W,0x0000");
	ASM_INLINE("DEC	[SI+0x08].W");
	ASM_INLINE("MOV	[SI+0x0A].W,0xFFFF");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x000C");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A52A:");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,[SI+0x06].W");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A56E:");
	ASM_INLINE("TEST	[0x0956].W,0x0400");
	ASM_INLINE("JNZ	_8A579");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A579:");
	ASM_INLINE("MOV	AL,0x0C");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,[SI+0x06].W");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("CMP	[SI+0x06].W,0x0002");
	ASM_INLINE("JGE	_8A5CC");
	ASM_INLINE("INC	[SI+0x06].W");
	ASM_INLINE("JMP	_8A5DE");
ASM_INLINE("_8A5CC:");
	ASM_INLINE("MOV	AL,[0x1E06].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0002");
	ASM_INLINE("CMP	AX,[SI+0x08].W");
	ASM_INLINE("JLE	_8A5DE");
	ASM_INLINE("INC	[SI+0x06].W");
ASM_INLINE("_8A5DE:");
	ASM_INLINE("CMP	[SI+0x06].W,0x0002");
	ASM_INLINE("JLE	_8A624");
	ASM_INLINE("MOV	[SI+0x06].W,0x0002");
	ASM_INLINE("INC	[SI+0x08].W");
	ASM_INLINE("MOV	[SI+0x0A].W,0x0001");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0E00");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x000C");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A624:");
	ASM_INLINE("MOV	BX,G_MENU_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_MENU_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	AX,0x0003");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0004");
	ASM_INLINE("MOV	BX,[SI+0x08].W");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0024");
	ASM_INLINE("MOV	CX,[SI+0x06].W");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("MOV	CX,0x0014");
	ASM_INLINE("MOV	DX,0x0004");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A667:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_8A696_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A66E:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_8AC60_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A675:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_8B3B1_");
	ASM_INLINE("JMP	_8A681");
ASM_INLINE("_8A67C:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_8AE35_");
ASM_INLINE("_8A681:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_89B05_");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[BX+0x04].W");
	ASM_INLINE("INC	AX");
	ASM_INLINE("AND	AX,0x0001");
	ASM_INLINE("MOV	[SI+0x04].W,AX");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}

static void near unk_8A696(struct MenuWork* work)
{
	if ((pad[0].unk4 & 4))
	{
		sereq(10);
		work->unk2 = 0;
		font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
		font_putXYT(4,work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
		font_putXYT(4,work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
	}
	else if ((pad[0].unk4 & 8))
	{
		sereq(0xb);
		work->unk2 = 0;
		font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
	}
	else if ((pad[0].unk4 & 0x100))
	{
		sereq(0xc);
		if (work->unkC > 0)
		{
			work->unkC--;
			font_putXYT(4, 0x3c, 0x14, 4, 4, 7, 0x800, 1, G_MENU_char_adr);

			if (SAVE_DATA_START[0x04])
			{
				font_putXYT(0xc, 0x44, 2, 4, 0xc, 7, 0x800, 1, G_MENU_char_adr);
			}
			else
			{
				font_putXYT(0xc, 0x44, 2, 4, 0x12, 7, 0x800, 1, G_MENU_char_adr);
			}

			font_putXYT(4, 0x40, 0x14, 4, 4, 0xb, 0xe00, 1, G_MENU_char_adr);

			if (SAVE_DATA_START[0x05])
			{
				font_putXYT(0xc, 0x44, 2, 4, 0xc, 0xb, 0xe00, 1, G_MENU_char_adr);
			}
			else
			{
				font_putXYT(0xc, 0x44, 2, 4, 0x12, 0xb, 0xe00, 1, G_MENU_char_adr);
			}
		}
	}
	else if ((pad[0].unk4 & 0x400))
	{
		sereq(0xc);
		if (work->unkC < 1)
		{
			work->unkC++;
			font_putXYT(4, 0x3c, 0x14, 4, 4, 7, 0xe00, 1, G_MENU_char_adr);

			if (SAVE_DATA_START[0x04])
			{
				font_putXYT(0xc, 0x44, 2, 4, 0xc, 7, 0xe00, 1, G_MENU_char_adr);
			}
			else
			{
				font_putXYT(0xc, 0x44, 2, 4, 0x12, 7, 0xe00, 1, G_MENU_char_adr);
			}

			font_putXYT(4, 0x40, 0x14, 4, 4, 0xb, 0x800, 1, G_MENU_char_adr);
			
			if (SAVE_DATA_START[0x05])
			{
				font_putXYT(0xc, 0x44, 2, 4, 0xc, 0xb, 0x800, 1, G_MENU_char_adr);
			}
			else
			{
				font_putXYT(0xc, 0x44, 2, 4, 0x12, 0xb, 0x800, 1, G_MENU_char_adr);
			}
		}
	}
	else if ((pad[0].unk4 & 0x800))
	{
		if (work->unkC)
		{
			if(SAVE_DATA_START[0x05] == 0)
			{
				SAVE_DATA_START[0x05] = 1;
				sereq(0xc);
				font_putXYT(4, 0x40, 0x14, 4, 4, 0xb, 0x800, 1, G_MENU_char_adr);
				font_putXYT(0xc, 0x44, 2, 4, 0xc, 0xb, 0x800, 1, G_MENU_char_adr);
			}
		}
		else if (SAVE_DATA_START[0x04] == 0)
		{
			SAVE_DATA_START[0x04] = 1;
			bgmreq(2);
			font_putXYT(4, 0x3c, 0x14, 4, 4, 7, 0x800, 1, G_MENU_char_adr);
			font_putXYT(0xc, 0x44, 2, 4, 0xc, 7, 0x800, 1, G_MENU_char_adr);
		}
	}
	else if ((pad[0].unk4 & 0x200))
	{
		if (work->unkC)
		{
			if(SAVE_DATA_START[0x05])
			{
				sereq(0xc);
				SAVE_DATA_START[0x05] = 0;
				font_putXYT(4, 0x40, 0x14, 4, 4, 0xb, 0x800, 1, G_MENU_char_adr);
				font_putXYT(0xc, 0x44, 2, 4, 0x12, 0xb, 0x800, 1, G_MENU_char_adr);
			}
		}
		else if (SAVE_DATA_START[0x04])
		{
			bgmreq(0);
			SAVE_DATA_START[0x04] = 0;
			font_putXYT(4, 0x3c, 0x14, 4, 4, 7, 0x800, 1, G_MENU_char_adr);
			font_putXYT(0xc, 0x44, 2, 4, 0x12, 7, 0x800, 1, G_MENU_char_adr);
		}
	}
}

static void near unk_8AC60(struct MenuWork* work)
{
	if ((pad[0].unk4 & 4))
	{
		sereq(10);
		unk_8B2E1(work, 4);
	}
	else if ((pad[0].unk4 & 8))
	{
		sereq(0xb);
		work->unk2 = 0;
		font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
		unk_8B2E1(work, 3);
	}
	else if ((pad[0].unk4 & 0x100))
	{
		sereq(0xc);
		if(work->unkC > 0)
		{
			work->unkC--;
			font_putXYT(3, 0x48, 0x16, 4, 3, 7, 0x800, 1, G_MENU_char_adr);
			font_putXYT(3, 0x4c, 0x16, 4, 3, 0xb, 0xe00, 1, G_MENU_char_adr);
			unk_8B2E1(work, 1);
		}
	}
	else if (pad[0].unk4 & 0x400)
	{
		sereq(0xc);
		if(work->unkC < 1)
		{
			work->unkC++;
			font_putXYT(3, 0x48, 0x16, 4, 3, 7, 0xe00, 1, G_MENU_char_adr);
			font_putXYT(3, 0x4c, 0x16, 4, 3, 0xb, 0x800, 1, G_MENU_char_adr);
			unk_8B2E1(work, 2);
		}
	}
}

static void near unk_8AE35(struct MenuWork* work)
{
	if ((pad[0].unk4 & 8))
	{
		sereq(0xb);
		bgmreq(2);
		work->unk2 = 0;
		font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
		font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
		unk_8B2E1(work, 3);
	}
	else if ((pad[0].unk4 & 4))
	{
		if (work->unkC)
		{
			sereq(work->unk10 + 10);
		}
		else
		{
			bgmreq(work->unkE);
		}
	}
	else if ((pad[0].unk4 & 0x100))
	{
		sereq(0xc);
		if (work->unkC > 0)
		{
			work->unkC--;
			font_putXYT(4, 0x3c, 8, 4, 4, 7, 0x800, 1, G_MENU_char_adr);
			unk_89CAD(work, 0x98, 0x38, work->unkE, 0x800);
			font_putXYT(4, 0x40, 8, 4, 4, 0xb, 0xe00, 1, G_MENU_char_adr);
			unk_89CAD(work, 0x98, 0x58, work->unk10, 0xe00);
		}
	}
	else if ((pad[0].unk4 & 0x400))
	{
		sereq(0xc);
		if (work->unkC < 1)
		{
			work->unkC++;
			font_putXYT(4, 0x3c, 8, 4, 4, 7, 0xe00, 1, G_MENU_char_adr);
			unk_89CAD(work, 0x98, 0x38, work->unkE, 0xe00);
			font_putXYT(4, 0x40, 8, 4, 4, 0xb, 0x800, 1, G_MENU_char_adr);
			unk_89CAD(work, 0x98, 0x58, work->unk10, 0x800);
		}
	}
	else if ((pad[0].unk4 & 0x200))
	{
		sereq(0xc);
		if (work->unkC)
		{
			work->unk10 += (work->unk10 < 0x14);
			unk_89CAD(work, 0x98, 0x58, work->unk10, 0x800);
		}
		else
		{
			work->unkE += (work->unkE < 9);
			unk_89CAD(work, 0x98, 0x38, work->unkE, 0x800);
		}
	}
	else if ((pad[0].unk4 & 0x800))
	{
		sereq(0xc);
		if (work->unkC)
		{
			work->unk10 -= (0 < work->unk10);
			unk_89CAD(work, 0x98, 0x58, work->unk10, 0x800);
		}
		else
		{
			work->unkE -= (0 < work->unkE);
			unk_89CAD(work, 0x98, 0x38, work->unkE, 0x800);
		}
	}
}

static void near unk_8B134(struct MenuWork* work)
{
	u8 menu_data2[] = {
		0x00, 0x01, 0xA8, 0xC0,
		0xFF, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00,
	};
	menu_data2[4] = 0;
	ip_w(menu_data2);

	work->unk14 = 0x6C;
	task_delete();
	task_append((task_pointer)unk_8B17B, work);
}

static void unk_8B17B(struct MenuWork* work)
{
	s16 val;
	u8 menu_data3[] = {
		0x00, 0x01, 0xA8, 0xC0,
		0xFF, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00,
	};

	val = ip_r(menu_data3);

	if(val == 0)
	{
		if(menu_data3[4] == 0)
		{
			switch(com_user)
			{
				case 1:
				{
					mother_child = 1;
					work->unk2 = 3;
					break;
				}
				case 2:
				{
					mother_child = 2;
					work->unk2 = 2;
					break;
				}
			}
			work->unkC = 0;
			sereq(10);
			task_delete();
			task_append(unk_89FB9, work);
			font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
			font_putXYT(3, 0x2c, 0x16, 4, 3, 3, 0x800, 1, G_MENU_char_adr);
			font_putXYT(3, 0x48, 0x16, 4, 3, 7, 0x800, 1, G_MENU_char_adr);
			font_putXYT(3, 0x4c, 0x16, 4, 3, 0xb, 0xe00, 1, G_MENU_char_adr);
		}
	}
	else if((work->unk14 != 0))
	{
		--work->unk14;
		if(work->unk14 == 0)
		{
			ip_clear(menu_data3);
			task_delete();
			task_append(unk_89FB9, work);
			sereq(0xc);
		}
	}
}

static void near unk_8B2E1(struct MenuWork* work, u16 mode)
{
	u8 menu_data4[] = {
		0x00, 0x01, 0xA8, 0xC0,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00,
	};

	SAVE_DATA_START[0x07] = 2;
	SAVE_DATA_START[0x08] = work->unkC;

	menu_data4[5] = work->unkC;
	menu_data4[6] = mode;

	switch(menu_data4[6])
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			ip_w(menu_data4);
			break;
		}
		case 2:
		{
			ip_w(menu_data4);
			break;
		}
		case 3:
		{
			mother_child = 0;
			ip_clear(menu_data4);
			ip_w(menu_data4);
			break;
		}
		case 4:
		{
			nbg_scroll(0, 0, 0);
			SetPalette(0, 7, 5, 3, 0);
			memfree(work);
			task_delete();
			task_append((task_pointer)unisel_init, 0);
			task_delete_fade(10);
			mother_child = 1;
			ip_w(menu_data4);
			break;
		}
	}
}

static void near unk_8B3B1(struct MenuWork* work)
{
	u16 val;
	u8 menu_data5[] = {
		0x00, 0x01, 0xA8, 0xC0,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00,
	};

	val = ip_r(menu_data5);

	if((val == 0) && (menu_data5[4] == 0))
	{
		SAVE_DATA_START[0x07] = 2;
		SAVE_DATA_START[0x08] = menu_data5[5];
		switch(menu_data5[6])
		{
			case 0:
			{
				sereq(10);
				break;
			}
			case 1:
			{
				sereq(0xc);
				font_putXYT(3, 0x48, 0x16, 4, 3, 7, 0x800, 1, G_MENU_char_adr);
				font_putXYT(3, 0x4c, 0x16, 4, 3, 0xb, 0xe00, 1, G_MENU_char_adr);
				break;
			}
			case 2:
			{
				sereq(0xc);
				font_putXYT(3, 0x48, 0x16, 4, 3, 7, 0xe00, 1, G_MENU_char_adr);
				font_putXYT(3, 0x4c, 0x16, 4, 3, 0xb, 0x800, 1, G_MENU_char_adr);
				break;
			}
			case 3:
			{
				sereq(0xb);
				mother_child = 0;
				ip_clear(menu_data5);
				work->unk2 = 0;
				font_putXYT(0, 0x12, 0x1c, 0x12, 0, 0, 0x800, 1, G_MENU_char_adr);
				font_putXYT(4, work->unk8 * 2 + 0x24, 0x14, 0xc, 4, 3, 0xe00, 1, G_MENU_char_adr);
				font_putXYT(4, work->unk8 * 2 + 0x24 + work->unk6 * 4, 0x14, 4, 4, work->unk6 * 4 + 3, 0x800, 1, G_MENU_char_adr);
				break;
			}
			case 4:
			{
				sereq(10);
				nbg_scroll(0, 0, 0);
				SetPalette(0, 7, 5, 3, 0);
				memfree(work);
				task_delete();
				task_append((task_pointer)unisel_init,0);
				task_delete_fade(10);
				mother_child = 2;
				break;
			}
		}
	}
}
