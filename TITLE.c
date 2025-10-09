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
/*	if((pad[0].unk4 & 0x800) && (work->unk7))
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

		//Should be just this but causes reg alloc diff
		work->unk9 = (work->unk9 + 1) % 8;

		//work->unk9 = (work->unk9 + 1) % 8;
		//work->unk9 = ((work->unk9 % 8) + 1) % 8;

		//work->unk9 = (work->unk9 + 1) & 0x7;
		//work->unk9 = ((work->unk9) + 1) & 7;
		//work->unk9 = (work->unk9 + 1) & (7);
		//work->unk9 = ((work->unk9) + (1)) & (0x7);

		//work->unk9 = (work->unk9 + 1U) & 0x7U;
		//work->unk9 = ((work->unk9) + 1U) & 7U;
		//work->unk9 = (work->unk9 + 1U) & (7U);
		//work->unk9 = ((work->unk9) + (1U)) & (0x7U);

		//work->unk9 = work->unk9 + 1;
		//work->unk9 &= 7;

		//++work->unk9;
		//work->unk9 &= 7;

		//work->unk9++;
		//work->unk9 &= 7;

		//work->unk9 = ++work->unk9 & 7;
		//work->unk9 = work->unk9++ & 7;

		//work->unk9 = work->unk9 + 1 - ((work->unk9 + 1) & ‾7);

		//work->unk9 = ((s16)work->unk9 + 1) & 7u;

		//work->unk9 = ((int16_t)(work->unk9 + 1)) & 7;
		//work->unk9 = (int16_t)((work->unk9 + 1) & 7);

		//work->unk9 = (work->unk9 + 1 >= 8) ? 0 : (work->unk9 + 1);

		if((work->unkB[work->unk9 - 1 & 7] & 0x200))
		{
			if((work->unkB[work->unk9 - 2 & 7] & 0x800))
			{
				if((work->unkB[work->unk9 - 3 & 7] & 0x400))
				{
					if((work->unkB[work->unk9 - 4 & 7] & 0x400))
					{
						if((work->unkB[work->unk9 - 5 & 7] & 0x400))
						{
							if((work->unkB[work->unk9 - 6 & 7] & 0x100))
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
	nbg_scroll(0, 0, ++work->unk6);*/

	sereq; //Force include
	memfree; //Force include
	task_delete_fade; //Force include
	nbg_scroll; //Force include
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("TEST	[0x0956].W,0x0800");
	ASM_INLINE("JZ	_840A6");
	ASM_INLINE("CMP	[SI+0x07].W,0x0000");
	ASM_INLINE("JZ	_840A6");
	ASM_INLINE("MOV	AL,0x12");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AX,[SI+0x1B].W");
	ASM_INLINE("SUB	AX,0xFFFC");
	ASM_INLINE("MOV	BX,0x0005");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	[SI+0x1B].W,DX");
	ASM_INLINE("MOV	AX,[SI+0x1B].W");
	ASM_INLINE("CMP	AX,0x0004");
	ASM_INLINE("JZ	_840A1");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JZ	_8409A");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JZ	_84093");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_8408C");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_840A6");
	ASM_INLINE("CALLF	unk_83DB2_, SEG unk_83DB2_");
	ASM_INLINE("JMP	_840A6");
ASM_INLINE("_8408C:");
	ASM_INLINE("CALLF	unk_83DC1_, SEG unk_83DC1_");
	ASM_INLINE("JMP	_840A6");
ASM_INLINE("_84093:");
	ASM_INLINE("CALLF	unk_83DD0_, SEG unk_83DD0_");
	ASM_INLINE("JMP	_840A6");
ASM_INLINE("_8409A:");
	ASM_INLINE("CALLF	unk_83DDF_, SEG unk_83DDF_");
	ASM_INLINE("JMP	_840A6");
ASM_INLINE("_840A1:");
	ASM_INLINE("CALLF	unk_83DEE_, SEG unk_83DEE_");
ASM_INLINE("_840A6:");
	ASM_INLINE("TEST	[0x0956].W,0x0200");
	ASM_INLINE("JZ	_84106");
	ASM_INLINE("CMP	[SI+0x07].W,0x0000");
	ASM_INLINE("JZ	_84106");
	ASM_INLINE("MOV	AL,0x12");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AX,[SI+0x1B].W");
	ASM_INLINE("ADD	AX,0x0006");
	ASM_INLINE("MOV	BX,0x0005");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	[SI+0x1B].W,DX");
	ASM_INLINE("MOV	AX,[SI+0x1B].W");
	ASM_INLINE("CMP	AX,0x0004");
	ASM_INLINE("JZ	_84101");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JZ	_840FA");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JZ	_840F3");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_840EC");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_84106");
	ASM_INLINE("CALLF	unk_83DB2_, SEG unk_83DB2_");
	ASM_INLINE("JMP	_84106");
ASM_INLINE("_840EC:");
	ASM_INLINE("CALLF	unk_83DC1_, SEG unk_83DC1_");
	ASM_INLINE("JMP	_84106");
ASM_INLINE("_840F3:");
	ASM_INLINE("CALLF	unk_83DD0_, SEG unk_83DD0_");
	ASM_INLINE("JMP	_84106");
ASM_INLINE("_840FA:");
	ASM_INLINE("CALLF	unk_83DDF_, SEG unk_83DDF_");
	ASM_INLINE("JMP	_84106");
ASM_INLINE("_84101:");
	ASM_INLINE("CALLF	unk_83DEE_, SEG unk_83DEE_");
ASM_INLINE("_84106:");
	ASM_INLINE("TEST	[0x0956].W,0x0004");
	ASM_INLINE("JZ	_84157");
	ASM_INLINE("CMP	[SI+0x07].W,0x0000");
	ASM_INLINE("JZ	_84157");
	ASM_INLINE("MOV	AL,0x10");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AX,[SI+0x1B].W");
	ASM_INLINE("CMP	AX,0x0004");
	ASM_INLINE("JZ	_84152");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JZ	_8414B");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JZ	_84144");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_8413D");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_84157");
	ASM_INLINE("CALLF	unk_83DFD_, SEG unk_83DFD_");
	ASM_INLINE("JMP	_84157");
ASM_INLINE("_8413D:");
	ASM_INLINE("CALLF	unk_83E0C_, SEG unk_83E0C_");
	ASM_INLINE("JMP	_84157");
ASM_INLINE("_84144:");
	ASM_INLINE("CALLF	unk_83E1B_, SEG unk_83E1B_");
	ASM_INLINE("JMP	_84157");
ASM_INLINE("_8414B:");
	ASM_INLINE("CALLF	unk_83E2A_, SEG unk_83E2A_");
	ASM_INLINE("JMP	_84157");
ASM_INLINE("_84152:");
	ASM_INLINE("CALLF	unk_83E3E_, SEG unk_83E3E_");
ASM_INLINE("_84157:");
	ASM_INLINE("CMP	[0x0956].W,0x0000");
	ASM_INLINE("JNZ	_84161");
	ASM_INLINE("JMP	_8421B");
ASM_INLINE("_84161:");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("MOV	AX,[0x0956].W");
	ASM_INLINE("MOV	[BX].W,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[BX+0x09].W");
	ASM_INLINE("INC	AX");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("MOV	[SI+0x09].W,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0200");
	ASM_INLINE("JNZ	_84197");
	ASM_INLINE("JMP	_8421B");
ASM_INLINE("_84197:");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SUB	AX,0x0002");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0800");
	ASM_INLINE("JZ	_8421B");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SUB	AX,0x0003");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0400");
	ASM_INLINE("JZ	_8421B");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SUB	AX,0x0004");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0400");
	ASM_INLINE("JZ	_8421B");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SUB	AX,0x0005");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0400");
	ASM_INLINE("JZ	_8421B");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x000B");
	ASM_INLINE("MOV	AX,[SI+0x09].W");
	ASM_INLINE("SUB	AX,0x0006");
	ASM_INLINE("AND	AX,0x0007");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("TEST	[BX].W,0x0100");
	ASM_INLINE("JZ	_8421B");
	ASM_INLINE("MOV	[SI+0x07].W,0x0001");
	ASM_INLINE("MOV	AL,0x10");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
ASM_INLINE("_8421B:");
	ASM_INLINE("TEST	[0x0956].W,0x0002");
	ASM_INLINE("JZ	_8423E");
	ASM_INLINE("MOV	AL,0x0A");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	task_delete_fade_, SEG task_delete_fade_");
ASM_INLINE("_8423E:");
	ASM_INLINE("INC	[SI+0x04].W");
	ASM_INLINE("CMP	[SI+0x04].W,0x0003");
	ASM_INLINE("JLE	_84261");
	ASM_INLINE("MOV	[SI+0x04].W,0x0000");
	ASM_INLINE("MOV	AX,[SI+0x02].W");
	ASM_INLINE("INC	AX");
	ASM_INLINE("MOV	BX,0x0006");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	[SI+0x02].W,DX");
	ASM_INLINE("MOV	AX,[SI+0x02].W");
	ASM_INLINE("CALLF	unk_83CEA_, SEG unk_83CEA_");
ASM_INLINE("_84261:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("INC	[SI+0x06].B");
	ASM_INLINE("MOV	CL,[SI+0x06].B");
	ASM_INLINE("XOR	CH,CH");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}







 