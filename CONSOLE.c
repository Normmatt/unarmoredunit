#include <machine.h>
#include "types.h"
#include "CONSOLE.h"
#include "IP_MES.h"
#include "SWANMAIN.h"
#include "MEMORY.h"
#include "SYSTEM.h"
#include "SWAN_L_C.h"
#include "PAD.h"

u8 console_data[] = {
	0x02, 0x00, 0xA8, 0xC0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00,
	0x02, 0x00,
};

static const char far console_text[] = "SW8000EX Console Ver 1.00b¥r¥nCopyright 1999 By minisoft/¥r¥n/Switches95/Fillsail/CHARA.¥r¥n¥r¥n  ReturnSystem Push !!¥r¥n   [L]+[R] and [A] Button¥r¥n¥r¥n";
static const char far console_login[] = "login:";
static const char far console_password[] = "password:";


static void unk_83C7B(struct ConsoleWork *buf);

static void near unk_839BF()
{
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0004");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	BX,[0x00F8].W");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	AX,BX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("MOV	DX,[0x0062].W");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("OR	BX,DX");
	ASM_INLINE("OR	AX,CX");
	ASM_INLINE("MOV	[BP-0x04].W,BX");
	ASM_INLINE("MOV	[BP-0x02].W,AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_83A17");
ASM_INLINE("_839E7:");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("JMP	_83A11");
ASM_INLINE("_839EB:");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("INC	DX");
	ASM_INLINE("MOV	CL,0x05");
	ASM_INLINE("SHL	DX,CL");
	ASM_INLINE("ADD	DX,DI");
	ASM_INLINE("SHL	DX,1");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("ADD	BX,DX");
	ASM_INLINE("MOV	SI,ES:[BX].W");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("MOV	CL,0x05");
	ASM_INLINE("SHL	DX,CL");
	ASM_INLINE("ADD	DX,DI");
	ASM_INLINE("SHL	DX,1");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("ADD	BX,DX");
	ASM_INLINE("MOV	ES:[BX].W,SI");
	ASM_INLINE("INC	DI");
ASM_INLINE("_83A11:");
	ASM_INLINE("CMP	DI,0x001C");
	ASM_INLINE("JL	_839EB");
	ASM_INLINE("INC	AX");
ASM_INLINE("_83A17:");
	ASM_INLINE("CMP	AX,0x0012");
	ASM_INLINE("JL	_839E7");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_83A24(struct ConsoleWork *buf)
{
	if(++buf->unk2 >= 0x1C)
	{
		buf->unk2 = 0;
		if(++buf->unk3 >= 0x12)
		{
			unk_839BF();
			buf->unk3--;
		}
	}
}

static void near unk_83A45(struct ConsoleWork *buf)
{
	buf->unk2 = 0;
}

static void near unk_83A4C(struct ConsoleWork *buf)
{
	if(++buf->unk3 >= 0x12)
	{
		unk_839BF();
		buf->unk3--;
	}
}

static void near unk_83A60(struct ConsoleWork *buf, u8 character)
{
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0008");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	DI,AX");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("ADD	CX,ES:[0x000E].W");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("MOV	AX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("MOV	DX,AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	AX,DX");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("OR	DX,CX");
	ASM_INLINE("OR	AX,SI");
	ASM_INLINE("MOV	[BP-0x04].W,DX");
	ASM_INLINE("MOV	[BP-0x02].W,AX");
	ASM_INLINE("MOV	CX,[0x00F8].W");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	AX,CX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("MOV	SI,[0x0062].W");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("OR	CX,SI");
	ASM_INLINE("OR	AX,DX");
	ASM_INLINE("MOV	[BP-0x08].W,CX");
	ASM_INLINE("MOV	[BP-0x06].W,AX");
	ASM_INLINE("CMP	BL,0x20");
	ASM_INLINE("JNB	_83ACF");
	ASM_INLINE("CMP	BL,0x0D");
	ASM_INLINE("JZ	_83AC8");
	ASM_INLINE("CMP	BL,0x0A");
	ASM_INLINE("JNZ	_83B10");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("CALL	unk_83A4C_");
	ASM_INLINE("JMP	_83B10");
ASM_INLINE("_83AC8:");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("CALL	unk_83A45_");
	ASM_INLINE("JMP	_83B10");
ASM_INLINE("_83ACF:");
	ASM_INLINE("CMP	BL,0x7F");
	ASM_INLINE("JNZ	_83ADF");
	ASM_INLINE("CMP	[DI+0x02].B,0x00");
	ASM_INLINE("JBE	_83B10");
	ASM_INLINE("DEC	[DI+0x02].B");
	ASM_INLINE("JMP	_83B10");
ASM_INLINE("_83ADF:");
	ASM_INLINE("LES	SI,[BP-0x04]");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SUB	BX,0x0040");
	ASM_INLINE("ADD	SI,BX");
	ASM_INLINE("MOV	DX,0x0800");
	ASM_INLINE("ADD	DX,ES:[SI].W");
	ASM_INLINE("MOV	BL,[DI+0x03].B");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("MOV	CL,0x05");
	ASM_INLINE("SHL	BX,CL");
	ASM_INLINE("MOV	AL,[DI+0x02].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("ADD	AX,BX");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("LES	BX,[BP-0x08]");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("MOV	ES:[BX].W,DX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("CALL	unk_83A24_");
ASM_INLINE("_83B10:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_83B18(struct ConsoleWork *buf, const char far *string)
{
	while(*string)
	{
		unk_83A60(buf, *string++);

	}
	unk_83A45(buf);
	unk_83A4C(buf);
}

static void near unk_83B50()
{
	ip_r; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0016");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("LEA	DI,[BP-0x16].B");
	ASM_INLINE("MOV	SI,0x02F2");
	ASM_INLINE("MOV	CX,0x0016");
	ASM_INLINE("PUSH	DS");
	ASM_INLINE("POP	ES");
	ASM_INLINE("CLD");
	ASM_INLINE("REP MOVSB");
	ASM_INLINE("LEA	AX,[BP-0x16].B");
	ASM_INLINE("CALLF	ip_r_, SEG ip_r_");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_83B81");
	ASM_INLINE("MOV	AL,[BP-0x12].B");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_83B81");
	ASM_INLINE("MOV	AL,[BP-0x11].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("JMP	_83B84");
ASM_INLINE("_83B81:");
	ASM_INLINE("MOV	AX,0xFFFF");
ASM_INLINE("_83B84:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_83B8B(struct ConsoleWork *buf)
{
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("CALL	unk_83B50_");
	ASM_INLINE("MOV	CX,AX");
	ASM_INLINE("CMP	CX,-1");
	ASM_INLINE("JZ	_83BE9");
	ASM_INLINE("CMP	CX,0x0020");
	ASM_INLINE("JGE	_83BB5");
	ASM_INLINE("CMP	CX,0x000D");
	ASM_INLINE("JZ	_83BAC");
	ASM_INLINE("CMP	CX,0x000A");
	ASM_INLINE("JNZ	_83BB0");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_83BEC");
ASM_INLINE("_83BAC:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_83BEC");
ASM_INLINE("_83BB0:");
	ASM_INLINE("MOV	AX,0xFFFF");
	ASM_INLINE("JMP	_83BEC");
ASM_INLINE("_83BB5:");
	ASM_INLINE("CMP	CX,0x007F");
	ASM_INLINE("JNZ	_83BC8");
	ASM_INLINE("CMP	[SI+0x02].B,0x00");
	ASM_INLINE("JBE	_83BC3");
	ASM_INLINE("DEC	[SI+0x02].B");
ASM_INLINE("_83BC3:");
	ASM_INLINE("MOV	AX,0xFFFF");
	ASM_INLINE("JMP	_83BEC");
ASM_INLINE("_83BC8:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	BL,CL");
	ASM_INLINE("CALL	unk_83A60_");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,0x0006");
	ASM_INLINE("MOV	AL,[SI+0x0086].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("MOV	[BX].B,CL");
	ASM_INLINE("CMP	[SI+0x0086].B,0x7F");
	ASM_INLINE("JNB	_83BE9");
	ASM_INLINE("INC	[SI+0x0086].B");
ASM_INLINE("_83BE9:");
	ASM_INLINE("MOV	AX,0xFFFF");
ASM_INLINE("_83BEC:");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	CX");
}

void console_init()
{
	struct ConsoleWork *work;
	task_delete();
	work = (struct ConsoleWork*)memalloc(sizeof (struct ConsoleWork));
	if(work)
	{
		task_append((task_pointer)unk_83C7B, (u16)work);

		work->unk0 = 0x64;
		work->unk2 = 0;
		work->unk3 = 0;
		work->unk4 = 0;
		work->unk5 = 0;
		work->unk6 = 0;
		work->unk86 = 0;
		work->unk87 = 0;

		nbg_ddf(0, 0);
		nbg_ddf(1, 0);
		spr_ddf(0);
		font_load(1,DFONT_char_adr);
		nbg_ddf(0, 0);
		nbg_ddf(1, 1);
		spr_ddf(0);
	}
}

static void unk_83C7B(struct ConsoleWork *buf)
{
	/*u16 val = buf->unk0;
	if(val != 0x76)
	{
		if(val != 1)
		{
			if(val == 0)
			{
				unk_83B18(buf, console_text);
				unk_83B18(buf, console_login);
				buf->unk0 = 1;
			}
			else
			{
				unk_83B8B(buf);
				if(!val || ((pad.unk0 & 0x200) || (pad.unk0 & 0x800) || !(pad.unk4 & 0x4)))
				{
					task_delete();
					memfree(buf);
				}
			}
		}
		else
		{
			unk_839BF();
			buf->unk0++;
		}
		
	}
	else
	{
		buf->unk0 = 0;
	}*/

	task_delete; //Force include 
	memfree; //Force include
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("MOV	AX,[SI].W");
	ASM_INLINE("CMP	AX,0x0076");
	ASM_INLINE("JZ	_83CE2");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_83CAC");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_83CDB");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	CX,0x0008");
	ASM_INLINE("MOV	DX,0xA21A");
	ASM_INLINE("CALL	unk_83B18_");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	CX,0x0006");
	ASM_INLINE("MOV	DX,0xA223");
	ASM_INLINE("CALL	unk_83B18_");
	ASM_INLINE("MOV	[SI].W,0x0001");
	ASM_INLINE("JMP	_83CE6");
ASM_INLINE("_83CAC:");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALL	unk_83B8B_");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_83CB5");
ASM_INLINE("_83CB5:");
	ASM_INLINE("TEST	[0x0952].W,0x0200");
	ASM_INLINE("JZ	_83CE6");
	ASM_INLINE("TEST	[0x0952].W,0x0800");
	ASM_INLINE("JZ	_83CE6");
	ASM_INLINE("TEST	[0x0956].W,0x0004");
	ASM_INLINE("JZ	_83CE6");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("CALLF	memfree_, SEG memfree_");
	ASM_INLINE("JMP	_83CE6");
ASM_INLINE("_83CDB:");
	ASM_INLINE("CALL	unk_839BF_");
	ASM_INLINE("INC	[SI].W");
	ASM_INLINE("JMP	_83CE6");
ASM_INLINE("_83CE2:");
	ASM_INLINE("MOV	[SI].W,0x0000");
ASM_INLINE("_83CE6:");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
}

 