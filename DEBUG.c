
#include <machine.h>
#include <stdrom.h>
#include "types.h"
#include "DEBUG.h"
#include "SWANMAIN.h"
#include "SWAN_L_C.h"
#include "MEMORY.h"
#include "SYSTEM.h"
#include "SPRINTF.h"
#include "IP_MES.h"
#include "SOUND_CODE.h"

static u8 debug_data[] = {
    0x03, 0x00, 0xA8, 0xC0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
	0x10, 0x00
};

static void unk_83949();

static void near unk_83853()
{
	s16 i;
	s16 j;
	s16 tmp;
	u16 far *m = MK_FP(vram, map_tbl[1]);

	for(i = 0; i < 0x12; i++)
	{
		for(j = 0; j < 0x1C; j++)
		{
			m[(0x20 * i) + j] = m[(0x20 * (i+1)) + j];
		}
	}
}

void debug_init()
{
	s16 i;
	u16 val;
	struct DebugWork *work;
	char buf[256];

	task_delete();
	work = (struct DebugWork*)memalloc(sizeof (struct DebugWork));

	if(work)
	{
		task_append((task_pointer)unk_83949, (u16)work);
		font_load(1,DFONT_char_adr);
		nbg_ddf(1, 1);
		unk_83853();

		for(i = 0; i < 16; i++)
		{
			val = e2lib_i_read(0x30 + i);
			hsprintf(buf, 0x2d2, i, val);
			print(0, 0x11, 1, buf, DFONT_char_adr);
			unk_83853();
		}
	}

}

static void unk_83949(struct DebugWork* work)
{
/*	s16 i;
	char buf[22];

	for(i = 0; i < sizeof(buf); i++)
	{
		buf[i] = ((char*)0x2dc);
	}*/



	ip_r; //Force include
	sereq; //Force include
	memfree; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0016");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	DI,[BP-0x16].B");
	ASM_INLINE("MOV	SI,debug_data_");
	ASM_INLINE("MOV	CX,0x0016");
	ASM_INLINE("PUSH	DS");
	ASM_INLINE("POP	ES");
	ASM_INLINE("CLD");
	ASM_INLINE("REP MOVSB");
	ASM_INLINE("LEA	DX,[BP-0x16].B");
	ASM_INLINE("MOV	AX,DX");
	ASM_INLINE("CALLF	ip_r_, SEG ip_r_");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_83995");
	ASM_INLINE("MOV	AL,0x0D");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("ADD	DX,0x0004");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("CALL	unk_83853_");
ASM_INLINE("_83995:");
	ASM_INLINE("TEST	[0x0956].W,0x0002");
	ASM_INLINE("POP	AX");
	ASM_INLINE("JZ	_839B7");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("JMP	_839A7");
ASM_INLINE("_839A3:");
	ASM_INLINE("CALL	unk_83853_");
	ASM_INLINE("INC	CX");
ASM_INLINE("_839A7:");
	ASM_INLINE("CMP	CX,0x0012");
	ASM_INLINE("JL	_839A3");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
ASM_INLINE("_839B7:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}



 