
#include <machine.h>
#include "types.h"
#include "stagesel.h"
#include "SWAN_L_C.h"
#include "SWANMAIN.h"
#include "MEMORY.h"
#include "PAD.h"
#include "SPRINTF.h"
#include "SYSTEM.h"
#include "flash.h"
#include "story.h"
#include "unisel.h"
#include "tuneup.h"
#include "SOUND_CODE.h"
#include "func_tbl.h"

static void unk_8D82A();

static void near unk_8CFD3(struct StageSelWork *work)
{
	switch(SAVE_DATA_START[0x07])
	{
		case 0:
		{
			font_put2XY(1, 0xb, 10, 1, 9, 7, 1, G_STGSEL_char_adr);
			break;
		}
		case 1:
		{
			font_put2XY(1, 0xc, 10, 1, 9, 7, 1, G_STGSEL_char_adr);
			//break;
		}
		case 2:
		case 3:
		{
			break;
		}
	}
}

static void near unk_8D03D(struct StageSelWork *work, u16 b)
{
	bmp_print; //Force include
	stagelist; //Force include
	type_name; //Force include
	chara_name; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0014");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("TEST	BX,BX");
	ASM_INLINE("JNZ	_8D050");
	ASM_INLINE("JMP	_8D14B");
ASM_INLINE("_8D050:");
	ASM_INLINE("LEA	DI,[BP-0x10].B");
	ASM_INLINE("MOV	AX,SEG stagelist_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x001D");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("ADD	BX,0x1E3C");
	ASM_INLINE("CMP	[BX+0x01].B,0x00");
	ASM_INLINE("JZ	_8D073");
	ASM_INLINE("MOV	BX,0x0010");
	ASM_INLINE("JMP	_8D075");
ASM_INLINE("_8D073:");
	ASM_INLINE("XOR	BX,BX");
ASM_INLINE("_8D075:");
	ASM_INLINE("ADD	BX,[SI].W");
	//ASM_INLINE("MOV	AL,ES:[BX+0x000A].B");
	ASM_OP5(0x26,0x8A,0x87,0x0A,0x00);
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x000F");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("SUB	BX,0x000F");
	ASM_INLINE("MOV	AX,SEG aulist_");
	ASM_INLINE("MOV	ES,AX");
	//ASM_INLINE("MOV	AL,ES:[BX+0x0004].B");
	ASM_OP5(0x26,0x8A,0x87,0x04,0x00);
	ASM_INLINE("CBW");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("MOV	AX,SEG type_name_");
	ASM_INLINE("MOV	ES,AX");
	//ASM_INLINE("MOV	CX,ES:[BX+0x0002].W");
	ASM_OP5(0x26,0x8B,0x8F,0x02,0x00);
	//ASM_INLINE("MOV	AX,ES:[BX+0x0004].W");
	ASM_OP5(0x26,0x8B,0x87,0x04,0x00);
	ASM_INLINE("MOV	[BP-0x14].W,CX");
	ASM_INLINE("MOV	[BP-0x12].W,AX");
ASM_INLINE("_8D0AE:");
	ASM_INLINE("INC	[BP-0x14].W");
	ASM_INLINE("LES	BX,[BP-0x14]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_8D0AE");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0078");
	ASM_INLINE("MOV	BX,0x0020");
	ASM_INLINE("LEA	CX,[BP-0x10].B");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALLF	bmp_print_, SEG bmp_print_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("LEA	DI,[BP-0x10].B");
	ASM_INLINE("MOV	AX,SEG stagelist_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x001D");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("ADD	BX,0x1E3C");
	ASM_INLINE("CMP	[BX+0x01].B,0x00");
	ASM_INLINE("JZ	_8D0F9");
	ASM_INLINE("MOV	BX,0x0010");
	ASM_INLINE("JMP	_8D0FB");
ASM_INLINE("_8D0F9:");
	ASM_INLINE("XOR	BX,BX");
ASM_INLINE("_8D0FB:");
	ASM_INLINE("ADD	BX,[SI].W");
	//ASM_INLINE("MOV	BL,ES:[BX+0x000A].B");
	ASM_OP5(0x26,0x8A,0x9F,0x0A,0x00);
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SUB	BX,0x0004");
	ASM_INLINE("MOV	AX,SEG chara_name_");
	ASM_INLINE("MOV	ES,AX");
	//ASM_INLINE("MOV	CX,ES:[BX+0x000A].W");
	ASM_OP5(0x26,0x8B,0x8F,0x0A,0x00);
	//ASM_INLINE("MOV	AX,ES:[BX+0x000C].W");
	ASM_OP5(0x26,0x8B,0x87,0x0C,0x00);
	ASM_INLINE("MOV	[BP-0x14].W,CX");
	ASM_INLINE("MOV	[BP-0x12].W,AX");
ASM_INLINE("_8D120:");
	ASM_INLINE("INC	[BP-0x14].W");
	ASM_INLINE("LES	BX,[BP-0x14]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_8D120");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0078");
	ASM_INLINE("MOV	BX,0x0030");
	ASM_INLINE("LEA	CX,[BP-0x10].B");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALLF	bmp_print_, SEG bmp_print_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("JMP	_8D20B");
ASM_INLINE("_8D14B:");
	ASM_INLINE("LEA	BX,[BP-0x10].B");
	ASM_INLINE("MOV	AX,SEG aulist_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	CX,0x001D");
	ASM_INLINE("MUL	CX");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("MOV	AL,[SI+0x1E3C].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	CX,0x000F");
	ASM_INLINE("MUL	CX");
	ASM_INLINE("MOV	SI,AX");
	//ASM_INLINE("MOV	AL,ES:[SI+0x0004].B");
	ASM_OP5(0x26,0x8A,0x84,0x04,0x00);
	ASM_INLINE("CBW");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("SHL	SI,1");
	ASM_INLINE("SHL	SI,1");
	ASM_INLINE("MOV	AX,SEG type_name_");
	ASM_INLINE("MOV	ES,AX");
	//ASM_INLINE("MOV	CX,ES:[SI+0x0002].W");
	ASM_OP5(0x26,0x8B,0x8C,0x02,0x00);
	//ASM_INLINE("MOV	AX,ES:[SI+0x0004].W");
	ASM_OP5(0x26,0x8B,0x84,0x04,0x00);
	ASM_INLINE("MOV	[BP-0x14].W,CX");
	ASM_INLINE("MOV	[BP-0x12].W,AX");
ASM_INLINE("_8D18D:");
	ASM_INLINE("INC	[BP-0x14].W");
	ASM_INLINE("LES	SI,[BP-0x14]");
	ASM_INLINE("DEC	SI");
	ASM_INLINE("MOV	AL,ES:[SI].B");
	ASM_INLINE("MOV	[BX].B,AL");
	ASM_INLINE("INC	BX");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_8D18D");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0030");
	ASM_INLINE("MOV	BX,0x0020");
	ASM_INLINE("LEA	CX,[BP-0x10].B");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALLF	bmp_print_, SEG bmp_print_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("LEA	SI,[BP-0x10].B");
	ASM_INLINE("MOV	AX,SEG chara_name_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x001D");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("MOV	BL,[BX+0x1E3C].B");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("MOV	CX,ES:[BX+0x000A].W");
	ASM_OP5(0x26,0x8B,0x8F,0x0A,0x00);
	//ASM_INLINE("MOV	AX,ES:[BX+0x000C].W");
	ASM_OP5(0x26,0x8B,0x87,0x0C,0x00);
	ASM_INLINE("MOV	[BP-0x14].W,CX");
	ASM_INLINE("MOV	[BP-0x12].W,AX");
ASM_INLINE("_8D1E3:");
	ASM_INLINE("INC	[BP-0x14].W");
	ASM_INLINE("LES	BX,[BP-0x14]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[SI].B,AL");
	ASM_INLINE("INC	SI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_8D1E3");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0030");
	ASM_INLINE("MOV	BX,0x0030");
	ASM_INLINE("LEA	CX,[BP-0x10].B");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALLF	bmp_print_, SEG bmp_print_");
	ASM_INLINE("ADD	SP,0x0002");
ASM_INLINE("_8D20B:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_8D213(struct StageSelWork *work, u16 b)
{
	u8 far *ptr;
	s16 i;
	s16 val;
	if(b)
	{
		val = stagelist[((*(u8 *)(SAVE_DATA_START[0x0A] * 0x1d + (SAVE_DATA_START + 0x3c) + 1))?16:0)+work->unk0] - 1;
	}
	else
	{
		val = *(u8 *)(SAVE_DATA_START[0x0A] * 0x1d + (SAVE_DATA_START + 0x3c) + 0);
	}

	switch(val / 20)
	{
		case 0:
		{
			font_put2XY((val - 0) << 2, 0, 4, 4, 0x16 * b + 1, 3, 1, G_AU1_char_adr);
			break;
		}
		case 1:
		{
			font_put2XY((val - 20) << 2, 0, 4, 4, 0x16 * b + 1, 3, 1, G_AU2_char_adr);
			break;
		}
		case 2:
		{
			font_put2XY((val - 40) << 2, 0, 4, 4, 0x16 * b + 1, 3, 1, G_AU3_char_adr);
		}
		case 3:
		{
			break;
		}
	}
}

static void unk_8D314(struct StageSelWork *work, s16 b, s16 c)
{
	s16 i;
	s16 j;
	s16 k;

	i = (b + 1) / 10;
	j = (b + 1) % 10;
	k = b % 8;

	if (b < 8)
	{
		font_put2XY(5, 9 + c, 1, 1, 1, 9 + k, 1, G_STGSEL_char_adr);
		font_put2XY(1, 9 + c, 4, 1, 2, 9 + k, 1, G_STGSEL_char_adr);

		if (i)
		{
			font_put2XY(6 + i, 9 + c, 1, 1, 6, 9 + k, 1, G_STGSEL_char_adr);
		}
		else
		{
			font_put2XY(5, 9 + c, 1, 1, 6, 9 + k, 1, G_STGSEL_char_adr);
		}

		font_put2XY(6 + j, 9 + c, 1, 1, 7, 9 + k, 1, G_STGSEL_char_adr);
		font_put2XY(5, 9 + c, 1, 1, 8, 9 + k, 1, G_STGSEL_char_adr);
		font_put2XY(5, 9 + c, 1, 1, 8, 9 + k, 1, G_STGSEL_char_adr);

		for (i = 0; i < *(u8 *)(SAVE_DATA_START[0x0A] * 0x1d + (SAVE_DATA_START + 0x3C) + 0x0D + b); i++)
		{
			font_put2XY(0x10, 9 + c, 1, 1, 9 + i, 9 + k, 1, G_STGSEL_char_adr);
		}

		for (; i < 4; i++)
		{
			font_put2XY(0x11, 9 + c, 1, 1, 9 + i, 9 + k, 1, G_STGSEL_char_adr);
		}

		font_put2XY(5, 9 + c, 1, 1, 0xd, 9 + k, 1, G_STGSEL_char_adr);	
	}
	else
	{
		font_put2XY(5, 9 + c, 1, 1, 0xe, 9 + k, 1, G_STGSEL_char_adr);
		font_put2XY(1, 9 + c, 4, 1, 0xf, 9 + k, 1, G_STGSEL_char_adr);

		if (i)
		{
			font_put2XY(6 + i, 9 + c, 1, 1, 0x13, 9 + k, 1, G_STGSEL_char_adr);
		}
		else
		{
			font_put2XY(5, 9 + c, 1, 1, 0x13, 9 + k, 1, G_STGSEL_char_adr);
		}

		font_put2XY(6 + j, 9 + c, 1, 1, 0x14, 9 + k, 1, G_STGSEL_char_adr);
		font_put2XY(5, 9 + c, 1, 1, 0x15, 9 + k, 1, G_STGSEL_char_adr);

		for (i = 0; i < *(u8 *)(SAVE_DATA_START[0x0A] * 0x1d + (SAVE_DATA_START + 0x3C) + 0x0D + b); i++)
		{
			font_put2XY(0x10, 9 + c, 1, 1, 0x16 + i, 9 + k, 1, G_STGSEL_char_adr);
		}

		for (; i < 4; i++)
		{
			font_put2XY(0x11, 9 + c, 1, 1, 0x16 + i, 9 + k, 1, G_STGSEL_char_adr);
		}
		font_put2XY(5, 9 + c, 1, 1, 0x1a, 9 + k, 1, G_STGSEL_char_adr);
	}
}

static void unk_8D72D(struct StageSelWork *work)
{
	s16 i;

	for (i = 0; i < 16; i++)
	{
		unk_8D314(work, i, 1);
	}
}

void stage_select_init()
{
	struct StageSelWork *work;

	task_delete();
	work = (struct StageSelWork *)memalloc(sizeof (struct StageSelWork));
	if (work != NULL)
	{
		task_append((task_pointer)unk_8D82A, (u16)work);
		work->unk0 = stage_get(SAVE_DATA_START[0x0A]);
		work->unk2 = work->unk0;
		nbg_ddf(0, 0);
		nbg_ddf(1, 0);
		spr_ddf(0);
		bitmap(1);
		font_put2(1, G_STGSEL_char_adr);
		unk_8D72D(work);
		unk_8D314(work, work->unk0, 0);
		unk_8CFD3(work);
		unk_8D03D(work, 0);
		unk_8D03D(work, 1);
		unk_8D213(work, 0);
		unk_8D213(work, 1);
		fade_tone(0);
		fade_out(100);
		fade_run();
		fade_in(10);
		nbg_ddf(0,1);
		nbg_ddf(1,1);
		bgmreq(2);
	}
}

static void unk_8D82A(struct StageSelWork *work)
{
	s16 i;
	u16 val;
	struct MAUData far *ptr;
	if ((pad[0].unk4 & 4))
	{
		SAVE_DATA_START[0x09] = work->unk0;
		SAVE_DATA_START[0x08] = 0;
		sereq(10);

		val = *(u8 *)(SAVE_DATA_START[0x0A] * 0x1d + (SAVE_DATA_START + 0x3c) + 1);

		if (val)
		{
			i = 16;
		}
		else
		{
			i = 0;
		}
		i += work->unk0;
		ptr = &aulist[stagelist[i] - 1];
		SAVE_DATA_START[0x3C] = stagelist[i] - 1;
		SAVE_DATA_START[0x3E] = ptr->hp;
		SAVE_DATA_START[0x3F] = ptr->en;
		SAVE_DATA_START[0x40] = 0xFF;

		for(i = 0; i < 8; i++)
		{
			SAVE_DATA_START[i+0x41] = ptr->moves[i];
		}

		for(i = 0; i < 16; i++)
		{
			SAVE_DATA_START[i+0x49] = 0xFF;
		}

		memfree(work);
		task_delete();

		switch(SAVE_DATA_START[0x07])
		{
			case 0:
			{
				task_append((task_pointer)story_init, 0);
				break;
			}
			case 1:
			{
				task_append((task_pointer)tuneup_init, 0);
				break;
			}
			case 2:
			case 3:
			{
				break;
			}
		}
		task_delete_fade(10);
	}
	if ((pad[0].unk4 & 8))
	{
		sereq(10);
		memfree(work);
		task_delete();
		task_append((task_pointer)unisel_init, 0);
		task_delete_fade(10);
	}
	if ((pad[0].unk4 & 0x100))
	{
		sereq(0xc);
		if(work->unk0 > 0)
		{
			unk_8D314(work, work->unk0, 1);
			work->unk0--;
			unk_8D03D(work, 1);
			unk_8D213(work, 1);
			unk_8D314(work, work->unk0, 0);
		}
	}
	if ((pad[0].unk4 & 0x400))
	{
		sereq(0xc);
		if(work->unk0 < work->unk2)
		{
			unk_8D314(work, work->unk0, 1);
			work->unk0++;
			unk_8D03D(work, 1);
			unk_8D213(work, 1);
			unk_8D314(work, work->unk0, 0);
		}
	}
	if ((pad[0].unk4 & 0x800))
	{
		sereq(0xc);
		if(7 < work->unk0)
		{
			unk_8D314(work, work->unk0, 1);
			work->unk0 -= 8;
			unk_8D03D(work, 1);
			unk_8D213(work, 1);
			unk_8D314(work, work->unk0, 0);
		}
	}
	if ((pad[0].unk4 & 0x200))
	{
		sereq(0xc);
		if((work->unk0 + 7) < work->unk2)
		{
			unk_8D314(work, work->unk0, 1);
			work->unk0 += 8;
			unk_8D03D(work, 1);
			unk_8D213(work, 1);
			unk_8D314(work, work->unk0, 0);
		}
	}
}
