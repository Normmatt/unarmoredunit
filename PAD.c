#include <machine.h>
#include "types.h"
#include "PAD.h"
#include "SWAN_L_C.h"
#include "MEMORY.h"
#include "SWANMAIN.h"
#include "IP_MES.h"

struct padState pad[2];

static u8 pad_data[] = {
	0x00, 0x00, 0xA8, 0xC0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x02, 0x00
};

void pad_init()
{
	pad[0].unkC = 0;
	pad[0].unkA = 0;
	pad[0].unk8 = 0;
	pad[0].unk6 = 0;
	pad[0].unk4 = 0;
	pad[0].unk2 = 0;
	pad[0].unk0 = 0;
	pad[1].unkC = 0;
	pad[1].unkA = 0;
	pad[1].unk8 = 0;
	pad[1].unk6 = 0;
	pad[1].unk4 = 0;
	pad[1].unk2 = 0;
	pad[1].unk0 = 0;
}

void pad_task()
{
/*	
	//00FA
	u8 pad_data[] = {
		0x00, 0x00, 0xA8, 0xC0,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x02, 0x00
	};
	struct padState *p = &pad[0];
	s16 i;
	u16 val;

	p->unk0 = pad_in();

	if((pad[0].unk0 & 4) && (pad[0].unk0 & 8) && (pad[0].unk0 & 2))
	{
		meminit();
		pad_init();
		tsk_init();
		remain();
	}

	if(pad[0].unk0 != pad[0].unk2)
	{
		pad_data[4] = (pad[0].unk0 >> 8) & 0xFF;
		pad_data[5] = pad[0].unk0 & 0xFF;
		ip_w(pad_data);
	}

	if(!ip_r(pad_data))
	{
		pad[1].unk2 = pad_data[4] << 8 | pad_data[5];
	}

	pad[1].unk0 = pad[1].unk2;

	for(i = 0; i < 2; i++, p++)
	{
		val = ‾p->unk2 & p->unk0;
		p->unk6 = val;
		p->unk4 = val;
		if(p->unk4)
		{
			p->unk8 = p->unk0;
			p->unkA = 0;
			p->unkC = 3;
		}
		else
		{
			p->unk8 = 0;
			if(p->unkA > 9)
			{
				p->unkC++;
				if(p->unkC > 3)
				{
					p->unkC = 0;
					p->unk8 = p->unk0;
				}
			}
			else
			{
				p->unkA++;
			}
		}
		p->unk2 = p->unk0;
	}*/


	pad_in; //Force include
	meminit; //Force include
	tsk_init; //Force include
	remain; //Force include
	ip_w; //Force include
	ip_r; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0016");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("LEA	DI,[BP-0x16].B");
	ASM_INLINE("MOV	SI,0x00FA");
	ASM_INLINE("MOV	CX,0x0016");
	ASM_INLINE("PUSH	DS");
	ASM_INLINE("POP	ES");
	ASM_INLINE("CLD");
	ASM_INLINE("REP MOVSB");
	ASM_INLINE("MOV	SI,pad_");
	ASM_INLINE("CALLF	pad_in_, SEG pad_in_");
	ASM_INLINE("MOV	[SI].W,AX");
	ASM_INLINE("TEST	[pad_].W,0x0004");
	ASM_INLINE("JZ	_813F2");
	ASM_INLINE("TEST	[pad_].W,0x0008");
	ASM_INLINE("JZ	_813F2");
	ASM_INLINE("TEST	[pad_].W,0x0002");
	ASM_INLINE("JZ	_813F2");
	ASM_INLINE("CALLF	meminit_, SEG meminit_");
	ASM_INLINE("CALLF	pad_init_, SEG pad_init_");
	ASM_INLINE("CALLF	tsk_init_, SEG tsk_init_");
	ASM_INLINE("CALLF	remain_, SEG remain_");
ASM_INLINE("_813F2:");
	ASM_INLINE("MOV	AX,[pad_].W");
	ASM_INLINE("CMP	AX,[pad_+2].W");
	ASM_INLINE("JZ	_81419");
	ASM_INLINE("MOV	AX,[pad_].W");
	ASM_INLINE("MOV	CL,0x08");
	ASM_INLINE("SHR	AX,CL");
	ASM_INLINE("AND	AX,0x00FF");
	ASM_INLINE("MOV	[BP-0x12].B,AL");
	ASM_INLINE("MOV	AX,[pad_].W");
	ASM_INLINE("AND	AX,0x00FF");
	ASM_INLINE("MOV	[BP-0x11].B,AL");
	ASM_INLINE("LEA	AX,[BP-0x16].B");
	ASM_INLINE("CALLF	ip_w_, SEG ip_w_");
ASM_INLINE("_81419:");
	ASM_INLINE("LEA	AX,[BP-0x16].B");
	ASM_INLINE("CALLF	ip_r_, SEG ip_r_");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_81432");
	ASM_INLINE("MOV	AL,[BP-0x12].B");
	ASM_INLINE("MOV	AH,AL");
	ASM_INLINE("MOV	BL,[BP-0x11].B");
	ASM_INLINE("MOV	AL,BL");
	ASM_INLINE("MOV	[pad_+16].W,AX");
ASM_INLINE("_81432:");
	ASM_INLINE("MOV	AX,[pad_+16].W");
	ASM_INLINE("MOV	[pad_+14].W,AX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("JMP	_81492");
ASM_INLINE("_8143C:");
	ASM_INLINE("MOV	AX,[SI+0x02].W");
	ASM_INLINE("NOT	AX");
	ASM_INLINE("AND	AX,[SI].W");
	ASM_INLINE("MOV	[SI+0x06].W,AX");
	ASM_INLINE("MOV	[SI+0x04].W,AX");
	ASM_INLINE("CMP	[SI+0x04].W,0x0000");
	ASM_INLINE("JZ	_81462");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[SI].W");
	ASM_INLINE("MOV	[BX+0x08].W,AX");
	ASM_INLINE("MOV	[SI+0x0A].W,0x0000");
	ASM_INLINE("MOV	[SI+0x0C].W,0x0003");
	ASM_INLINE("JMP	_81487");
ASM_INLINE("_81462:");
	ASM_INLINE("MOV	[SI+0x08].W,0x0000");
	ASM_INLINE("CMP	[SI+0x0A].W,0x0009");
	ASM_INLINE("JBE	_81484");
	ASM_INLINE("INC	[SI+0x0C].W");
	ASM_INLINE("CMP	[SI+0x0C].W,0x0003");
	ASM_INLINE("JBE	_81487");
	ASM_INLINE("MOV	[SI+0x0C].W,0x0000");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[SI].W");
	ASM_INLINE("MOV	[BX+0x08].W,AX");
	ASM_INLINE("JMP	_81487");
ASM_INLINE("_81484:");
	ASM_INLINE("INC	[SI+0x0A].W");
ASM_INLINE("_81487:");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	AX,[SI].W");
	ASM_INLINE("MOV	[BX+0x02].W,AX");
	ASM_INLINE("INC	CX");
	ASM_INLINE("ADD	SI,0x000E");
ASM_INLINE("_81492:");
	ASM_INLINE("CMP	CX,0x0002");
	ASM_INLINE("JL	_8143C");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

u16 get_pad(u16 a, s16 b)
{
	do
	{
		pad_task();
	} while (!pad[a].unk8 && b);
	
	return pad[a].unk8;

}

