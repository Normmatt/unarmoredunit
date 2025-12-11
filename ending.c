
#include <machine.h>
#include "types.h"
#include "func_tbl.h"
#include "ending.h"
#include "SWAN_L_C.h"
#include "SWANMAIN.h"
#include "SPRINTF.h"
#include "SYSTEM.h"
#include "SOUND_CODE.h"
#include "MEMORY.h"
#include "PAD.h"
#include "story.h"

extern const u8 far G_ENDING_char_adr[];

static void unk_91673(struct EndingWork* work);

static void near unk_90FC7(struct EndingWork* work)
{
	font_put2XY(0x15 + work->unk8, 0x7f, 1, 1, 0, 0, 0, G_ENDING_char_adr);
	work->unk8 = work->unk8 + 1U & 3;
}

//static void near unk_91004(u16 a, u16 b, void far *data)
static void near unk_91004()
{
/*	s16 i;
	u16 val;
	u16 far *ptr = ((u16 far*)data) + *((u16 far*)((u8 far *)data+0x0E));

	for (i = 0; i < 0x1c; i++) {
		put_cell_no(i << 3, a << 3, 1, ptr[(b * 0x1c + i)] | 0x800);
	}*/

	put_cell_no; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0008");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	DI,AX");
	ASM_INLINE("MOV	SI,BX");
	ASM_INLINE("MOV	[BP-0x04].W,CX");
	ASM_INLINE("MOV	[BP-0x02].W,DX");
	ASM_INLINE("MOV	AX,[BP-0x04].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	AX,BX");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("MOV	CX,[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("ADD	CX,ES:[BX+0x0E].W");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("OR	DX,CX");
	ASM_INLINE("OR	AX,BX");
	ASM_INLINE("MOV	[BP-0x08].W,DX");
	ASM_INLINE("MOV	[BP-0x06].W,AX");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("JMP	_9107A");
ASM_INLINE("_91042:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,DX");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	DX,0x001C");
	ASM_INLINE("MUL	DX");
	ASM_INLINE("POP	DX");
	ASM_INLINE("ADD	AX,DX");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("LES	BX,[BP-0x08]");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("MOV	DX,ES:[BX].W");
	ASM_INLINE("OR	DX,0x0800");
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("POP	DX");
	ASM_INLINE("INC	DX");
ASM_INLINE("_9107A:");
	ASM_INLINE("CMP	DX,0x001C");
	ASM_INLINE("JL	_91042");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

void ending_init(void *buf)
{
/*	s16 i;
	s16 j;
	s16 k;
	u16 val;
	u16 val2;
	u16 val3;
	struct EndingWork *work;

	task_delete();
	work = (struct EndingWork*)memalloc(sizeof (struct EndingWork));

	if(work)
	{
		task_append((task_pointer)unk_91673, work);
		work->unk0 = buf;
		work->unk2 = 0;
		work->unk4 = 0;
		work->unk6 = 0;
		work->unk8 = 0;
		nbg_ddf(0, 0);
		nbg_ddf(1, 0);
		spr_ddf(0);
		spr_cls();
		font_load(1, G_ENDING_char_adr);
		for (i = 0; i < 32; i++)
		{
			font_putXYT(0, 0, 0x1c, 1, 0, i, 0x800, 1, G_ENDING_char_adr);
		}

		val = get_bmp_cell_no(0x13, 0x80, G_ENDING_char_adr);
		for (i = 0; i < 256; i += 8)
		{
			for (j = 0; j < 256; j += 8)
			{
				put_cell_no(j, i, 0, val);
			}
		}
		
		k = 8;
		i = 8;
		val2 = get_bmp_cell_no(0x12, 0x7f, G_ENDING_char_adr);
		put_cell_no(i, k, 0, val2 | 0x200);
		i += 8;

		val2 = get_bmp_cell_no(0x13, 0x7f, G_ENDING_char_adr);
		for (; i < 0xd0; i += 8)
		{
			put_cell_no(i, k, 0, val2 | 0x200);
		}

		val2 = get_bmp_cell_no(0x14, 0x7f, G_ENDING_char_adr);
		put_cell_no(i, k, 0, val2 | 0x200);
		k += 8;

		for (; k < 0x80; k += 8)
		{
			i = 8;
			val2 = get_bmp_cell_no(0x12, 0x80, G_ENDING_char_adr);
			put_cell_no(i, k, 0, val2 | 0x200);
			i += 8;

			i = 0xd0;
			val2 = get_bmp_cell_no(0x14, 0x80, G_ENDING_char_adr);
			put_cell_no(i, k, 0, val2 | 0x200);
		}

		val2 = get_bmp_cell_no(0x12, 0x81, G_ENDING_char_adr);
		put_cell_no(8, i, 0, val2 | 0x200);

		val2 = get_bmp_cell_no(0x13, 0x81, G_ENDING_char_adr);
		for (j = 0x10; j < 0xd0; j += 8)
		{
			put_cell_no(j, i, 0, val2 | 0x200);
		}

		//unformatted and most likely not correct
		val2 = get_bmp_cell_no(0x14,0x81,G_ENDING_char_adr);
		put_cell_no(j,i,0,val2 | 0x200);
		val2 = get_bmp_cell_no(0x12,0x7f,G_ENDING_char_adr);
		put_cell_no(0x10,0x10,0,val2 | 0x600);
		val2 = get_bmp_cell_no(0x13,0x7f,G_ENDING_char_adr);
		for (i = 0x18; i < 200; i += 8)
		{
			put_cell_no(i,0x10,0,val2 | 0x600);
		}
		val2 = get_bmp_cell_no(0x14,0x7f,G_ENDING_char_adr);
		put_cell_no(i,0x10,0,val2 | 0x600);
		for (i = 0x18; i < 0x78; i += 8)
		{
			val2 = get_bmp_cell_no(0x12,0x80,G_ENDING_char_adr);
			put_cell_no(0x10,i,0,val2 | 0x600);
			val2 = get_bmp_cell_no(0x14,0x80,G_ENDING_char_adr);
			put_cell_no(200,i,0,val2 | 0x600);
		}
		val2 = get_bmp_cell_no(0x12,0x81,G_ENDING_char_adr);
		put_cell_no(0x10,i,0,val2 | 0x600);
		val2 = get_bmp_cell_no(0x13,0x81,G_ENDING_char_adr);
		for (j = 0x18; j < 200; j += 8)
		{
			put_cell_no(j,i,0,val2 | 0x600);
		}
		val2 = get_bmp_cell_no(0x14,0x81,G_ENDING_char_adr);
		put_cell_no(j,i,0,val2 | 0x600);
		val2 = get_bmp_cell_no(0x15,0x7f,G_ENDING_char_adr);
		i = 0;
		put_sprite(0,0,0,val2 | 0x2000,0);
		val3 = 1;
		for (j = 8; j < 0xd8; j += 8)
		{
			put_sprite(val3,j,i,val2 | 0x2000,0);
			val3 = val3 + 1;
		}
		put_sprite(val3,j,i,val2 | 0x2000,0);
		val3 = val3 + 1;
		while (i += 8, i < 0x88)
		{
			put_sprite(val3,0,i,val2 | 0x2000,0);
			put_sprite(val3 + 1,0xd8,i,val2 | 0x2000,0);
			val3 = val3 + 2;
		}
		put_sprite(val3, 0, i, val2 | 0x2000, 0);
		for (j = 8; val3 += 1, j < 0xd8; j += 8)
		{
			put_sprite(val3, j, i, val2 | 0x2000, 0);
		}
		put_sprite(val3, j, i, val2 | 0x2000,0);
		put_cell_no(0, 0, 0, val2);
		nbg_scroll(0, 0, 0);
		nbg_scroll(1, 0, 0);
		fade_tone(0);
		fade_out(100);
		fade_run();
		fade_in(10);
		nbg_ddf(0, 1);
		nbg_ddf(1, 1);
		spr_ddf(1);
		bgmreq(8);
	}*/

	task_delete; //Force include
	memalloc; //Force include
	task_append; //Force include
	nbg_ddf; //Force include
	spr_ddf; //Force include
	spr_cls; //Force include
	font_load; //Force include
	font_putXYT; //Force include
	font_load; //Force include
	get_bmp_cell_no; //Force include
	put_sprite; //Force include
	nbg_scroll; //Force include
	fade_tone; //Force include
	fade_out; //Force include
	fade_run; //Force include
	fade_in; //Force include
	bgmreq; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0002");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	memalloc_, SEG memalloc_");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("TEST	SI,SI");
	ASM_INLINE("JNZ	_910A9");
	ASM_INLINE("JMP	_91575");
ASM_INLINE("_910A9:");
	ASM_INLINE("MOV	AX,unk_91673_");
	ASM_INLINE("MOV	BX,SEG unk_91673_");
	ASM_INLINE("MOV	CX,SI");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	[SI].W,DX");
	ASM_INLINE("MOV	[SI+0x02].W,0x0000");
	ASM_INLINE("MOV	[SI+0x04].W,0x0000");
	ASM_INLINE("MOV	[SI+0x06].W,0x0000");
	ASM_INLINE("MOV	[SI+0x08].W,0x0000");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("CALLF	spr_ddf_, SEG spr_ddf_");
	ASM_INLINE("CALLF	spr_cls_, SEG spr_cls_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	font_load_, SEG font_load_");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_91124");
ASM_INLINE("_910FD:");
	ASM_INLINE("MOV	BX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	AX,SEG G_ENDING_char_adr_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,0x0800");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("MOV	CX,0x001C");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALLF	font_putXYT_, SEG font_putXYT_");
	ASM_INLINE("ADD	SP,0x000C");
	ASM_INLINE("INC	SI");
ASM_INLINE("_91124:");
	ASM_INLINE("CMP	SI,0x0020");
	ASM_INLINE("JL	_910FD");
	ASM_INLINE("MOV	AX,0x0013");
	ASM_INLINE("MOV	BX,0x0080");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_9115B");
ASM_INLINE("_91140:");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("JMP	_91152");
ASM_INLINE("_91144:");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
ASM_INLINE("_91152:");
	ASM_INLINE("CMP	DI,0x0100");
	ASM_INLINE("JL	_91144");
	ASM_INLINE("ADD	SI,0x0008");
ASM_INLINE("_9115B:");
	ASM_INLINE("CMP	SI,0x0100");
	ASM_INLINE("JL	_91140");
	ASM_INLINE("MOV	SI,0x0008");
	ASM_INLINE("MOV	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0013");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("JMP	_911B5");
ASM_INLINE("_911A1:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("POP	DX");
ASM_INLINE("_911B5:");
	ASM_INLINE("CMP	DI,0x00D0");
	ASM_INLINE("JL	_911A1");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	SI,0x0008");
	ASM_INLINE("JMP	_91232");
ASM_INLINE("_911E2:");
	ASM_INLINE("MOV	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x0080");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	DI,0x00D0");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x0080");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	SI,0x0008");
ASM_INLINE("_91232:");
	ASM_INLINE("CMP	SI,0x0080");
	ASM_INLINE("JL	_911E2");
	ASM_INLINE("MOV	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0013");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("JMP	_91289");
ASM_INLINE("_91275:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("POP	DX");
ASM_INLINE("_91289:");
	ASM_INLINE("CMP	DI,0x00D0");
	ASM_INLINE("JL	_91275");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0200");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("MOV	SI,0x0010");
	ASM_INLINE("MOV	DI,0x0010");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0013");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("JMP	_91305");
ASM_INLINE("_912F1:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("POP	DX");
ASM_INLINE("_91305:");
	ASM_INLINE("CMP	DI,0x00C8");
	ASM_INLINE("JL	_912F1");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	SI,0x0008");
	ASM_INLINE("JMP	_91382");
ASM_INLINE("_91332:");
	ASM_INLINE("MOV	DI,0x0010");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x0080");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	DI,0x00C8");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x0080");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	SI,0x0008");
ASM_INLINE("_91382:");
	ASM_INLINE("CMP	SI,0x0078");
	ASM_INLINE("JL	_91332");
	ASM_INLINE("MOV	DI,0x0010");
	ASM_INLINE("MOV	AX,0x0012");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("MOV	AX,0x0013");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("JMP	_913D8");
ASM_INLINE("_913C4:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("POP	DX");
ASM_INLINE("_913D8:");
	ASM_INLINE("CMP	DI,0x00C8");
	ASM_INLINE("JL	_913C4");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x0081");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	DX,0x0600");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("MOV	[BP-0x02].W,0x0000");
	ASM_INLINE("MOV	AX,0x0015");
	ASM_INLINE("MOV	BX,0x007F");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_no_, SEG get_bmp_cell_no_");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("JMP	_91456");
ASM_INLINE("_9143A:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	DI,0x0008");
ASM_INLINE("_91456:");
	ASM_INLINE("CMP	DI,0x00D8");
	ASM_INLINE("JL	_9143A");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	CX,0x0008");
	ASM_INLINE("JMP	_914B0");
ASM_INLINE("_9147A:");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("MOV	BX,0x00D8");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	CX,0x0008");
ASM_INLINE("_914B0:");
	ASM_INLINE("CMP	CX,0x0088");
	ASM_INLINE("JL	_9147A");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	DI,0x0008");
	ASM_INLINE("JMP	_914F2");
ASM_INLINE("_914D6:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("ADD	DI,0x0008");
ASM_INLINE("_914F2:");
	ASM_INLINE("CMP	DI,0x00D8");
	ASM_INLINE("JL	_914D6");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("INC	[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	DX,0x2000");
	ASM_INLINE("OR	DX,SI");
	ASM_INLINE("CALLF	put_sprite_, SEG put_sprite_");
	ASM_INLINE("ADD	SP,0x0002");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("MOV	DX,SI");
	ASM_INLINE("CALLF	put_cell_no_, SEG put_cell_no_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("CALLF	fade_tone_, SEG fade_tone_");
	ASM_INLINE("MOV	AX,0x0064");
	ASM_INLINE("CALLF	fade_out_, SEG fade_out_");
	ASM_INLINE("CALLF	fade_run_, SEG fade_run_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	fade_in_, SEG fade_in_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("CALLF	spr_ddf_, SEG spr_ddf_");
	ASM_INLINE("MOV	AL,0x08");
	ASM_INLINE("CALLF	bgmreq_, SEG bgmreq_");
ASM_INLINE("_91575:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_9157D()
{
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	CX,AX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x001D");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("ADD	SI,0x1E3C");
	ASM_INLINE("ADD	SI,0x0005");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_915AD");
ASM_INLINE("_9159B:");
	ASM_INLINE("TEST	CX,CX");
	ASM_INLINE("JZ	_915A6");
	ASM_INLINE("CMP	[BX].B,0x17");
	ASM_INLINE("JNZ	_915AB");
	ASM_INLINE("JMP	_915D5");
ASM_INLINE("_915A6:");
	ASM_INLINE("CMP	[BX].B,0x18");
	ASM_INLINE("JZ	_915D5");
ASM_INLINE("_915AB:");
	ASM_INLINE("INC	AX");
	ASM_INLINE("INC	BX");
ASM_INLINE("_915AD:");
	ASM_INLINE("CMP	AX,0x0008");
	ASM_INLINE("JL	_9159B");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_915D0");
ASM_INLINE("_915B6:");
	ASM_INLINE("TEST	CX,CX");
	ASM_INLINE("JZ	_915C4");
	ASM_INLINE("CMP	[SI].B,0xFF");
	ASM_INLINE("JNZ	_915CE");
	ASM_INLINE("MOV	[SI].B,0x17");
	ASM_INLINE("JMP	_915D5");
ASM_INLINE("_915C4:");
	ASM_INLINE("CMP	[SI].B,0xFF");
	ASM_INLINE("JNZ	_915CE");
	ASM_INLINE("MOV	[SI].B,0x18");
	ASM_INLINE("JMP	_915D5");
ASM_INLINE("_915CE:");
	ASM_INLINE("INC	AX");
	ASM_INLINE("INC	SI");
ASM_INLINE("_915D0:");
	ASM_INLINE("CMP	AX,0x0008");
	ASM_INLINE("JL	_915B6");
ASM_INLINE("_915D5:");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}

static void near unk_915D9()
{
	meminit; //Force include
	pad_init; //Force include
	tsk_init; //Force include
	remain; //Force include
	task_delete_fade; //Force include
	story_init; //Force include
	stageadd; //Force include
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AL,[0x1E0A].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("MOV	BX,0x001D");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("ADD	BX,0x1E3C");
	ASM_INLINE("CMP	[BX+0x01].B,0x00");
	ASM_INLINE("JZ	_91652");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("CALL	unk_9157D_");
	ASM_INLINE("MOV	AX,SEG stageadd_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	BL,ES:[0x001A].B");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("TEST	[BX+0x1E0B].B,0x80");
	ASM_INLINE("JZ	_91620");
	ASM_INLINE("CALLF	meminit_, SEG meminit_");
	ASM_INLINE("CALLF	pad_init_, SEG pad_init_");
	ASM_INLINE("CALLF	tsk_init_, SEG tsk_init_");
	ASM_INLINE("CALLF	remain_, SEG remain_");
	ASM_INLINE("JMP	_91670");
ASM_INLINE("_91620:");
	ASM_INLINE("MOV	AX,SEG stageadd_");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	BL,ES:[0x001A].B");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("OR	[BX+0x1E0B].B,0x80");
	ASM_INLINE("MOV	[0x1E09].B,0x10");
	ASM_INLINE("MOV	[0x1E08].B,0x01");
	ASM_INLINE("MOV	AX,story_init_");
	ASM_INLINE("MOV	BX,SEG story_init_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("CALLF	task_delete_fade_, SEG task_delete_fade_");
	ASM_INLINE("JMP	_91670");
ASM_INLINE("_91652:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("CALL	unk_9157D_");
	ASM_INLINE("MOV	[0x1E06].B,0x01");
	ASM_INLINE("CALLF	meminit_, SEG meminit_");
	ASM_INLINE("CALLF	pad_init_, SEG pad_init_");
	ASM_INLINE("CALLF	tsk_init_, SEG tsk_init_");
	ASM_INLINE("CALLF	remain_, SEG remain_");
ASM_INLINE("_91670:");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}

static void unk_91673(struct EndingWork* work)
{
	memfree; //Force include
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_90FC7_");
	ASM_INLINE("MOV	AX,[SI+0x06].W");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_91700");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_9168C");
	ASM_INLINE("JMP	_9171A");
ASM_INLINE("_9168C:");
	ASM_INLINE("TEST	[0x0952].W,0x0002");
	ASM_INLINE("JNZ	_9169C");
	ASM_INLINE("TEST	[0x0952].W,0x0004");
	ASM_INLINE("JZ	_916A1");
ASM_INLINE("_9169C:");
	ASM_INLINE("MOV	[SI+0x04].W,0x0002");
ASM_INLINE("_916A1:");
	ASM_INLINE("CMP	[SI+0x04].W,0x0002");
	ASM_INLINE("JGE	_916AC");
	ASM_INLINE("INC	[SI+0x04].W");
	ASM_INLINE("JMP	_9171A");
ASM_INLINE("_916AC:");
	ASM_INLINE("MOV	[SI+0x04].W,0x0000");
	ASM_INLINE("CMP	[SI+0x02].W,0x0360");
	ASM_INLINE("JGE	_916FB");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("INC	[SI+0x02].W");
	ASM_INLINE("MOV	CX,[SI+0x02].W");
	ASM_INLINE("CALLF	nbg_scroll_, SEG nbg_scroll_");
	ASM_INLINE("TEST	[SI+0x02].W,0x0007");
	ASM_INLINE("JNZ	_9171A");
	ASM_INLINE("MOV	AX,0x0090");
	ASM_INLINE("ADD	AX,[SI+0x02].W");
	ASM_INLINE("MOV	BX,0x0008");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	BX,0x0020");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	AX,DX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,[SI+0x02].W");
	ASM_INLINE("MOV	BX,0x0008");
	ASM_INLINE("CWD");
	ASM_INLINE("IDIV	BX");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("MOV	CX,G_ENDING_char_adr_");
	ASM_INLINE("MOV	DX,SEG G_ENDING_char_adr_");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALL	unk_91004_");
	ASM_INLINE("JMP	_9171A");
ASM_INLINE("_916FB:");
	ASM_INLINE("INC	[SI+0x06].W");
	ASM_INLINE("JMP	_9171A");
ASM_INLINE("_91700:");
	ASM_INLINE("CMP	[SI+0x04].W,0x0048");
	ASM_INLINE("JGE	_9170B");
	ASM_INLINE("INC	[SI+0x04].W");
	ASM_INLINE("JMP	_9171A");
ASM_INLINE("_9170B:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("CALL	unk_915D9_");
ASM_INLINE("_9171A:");
	ASM_INLINE("TEST	[0x0956].W,0x0010");
	ASM_INLINE("JZ	_91731");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("CALL	unk_915D9_");
ASM_INLINE("_91731:");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}
 