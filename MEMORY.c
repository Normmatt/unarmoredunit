#include <machine.h>
#include "types.h"
#include "MEMORY.h"
#include "SWAN_L_C.h"
#include "SWANMAIN.h"
#include "SPRINTF.h"
#include "SYSTEM.h"
#include "PAD.h"

extern u8 far KEYBOARD_char_adr[];

memory_node_t memory_alloc_work[128]; /*096E*/
static memory_test_t memory_test; /*0D6E*/

/*00FC*/
static u8 memory_data[] = {
	0xA8, 0xC0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x00
};

static u16 unk0 = 0;  	/*0110*/
static void *unk1 = 0; /*0112*/
static u16 unk2 = 0; 	/*0114*/
static u16 unk3 = 0; 	/*0116*/
static u16 unk4 = 0; 	/*0118*/

static char str0[] = "%04X:";
static char str1[] = "FAST:";
static char str2[] = "err.:";
static char str3[] = "%04X:";
static char str4[] = "err.:";
static char str5[] = "END.:";
static char str6[] = "%04X:";
static char str7[] = "%04X:";
static char str8[] = "FREE";
static char str9[] = "USE.";
static char str10[] = "err.";
static char str11[] = ">--=[  Memory Init. ]==--<";

static const char far fstr1[] = "Memory test program";
static const char far fstr2[] = "                 level1.00";
static const char far fstr3[] = "memory-size:%dbytes";
static const char far fstr4[] = "SRAMaddress:%04Xh";
static const char far fstr5[] = "entry memory:%dbytes";
static const char far fstr6[] = "free  memory:%dbytes";
static const char far fstr7[] = "Initialize RIGHT+LEFT+A";
static const char far fstr8[] = "button push";

static void unk_81A34();
static void unk_82093();

void meminit()
{
	u8 *p = (u8*)memory_alloc_work;
	memory_node_t *m;
	s16 i;
	for (i = sizeof(memory_alloc_work); i; i--)
	{
		*p++ = 0;
	}

	m = &memory_alloc_work[0];
	m->unk0 = (memory_node_t *)MEMORY_FLAG_FF41;
	m->unk2 = &memory_alloc_work[1];
	m->unk4 = 0;
	m->unk6 = MEMORY_FLAG_FF55;

	m = &memory_alloc_work[1];
	m->unk0 = &memory_alloc_work[0];
	m->unk2 = &memory_alloc_work[127];
	m->unk4 = 1000;
	m->unk6 = MEMORY_FLAG_FF46;
	
	m = &memory_alloc_work[127];
	m->unk0 = &memory_alloc_work[1];
	m->unk2 = (memory_node_t *)MEMORY_FLAG_FF42;
	m->unk4 = 0;
	m->unk6 = MEMORY_FLAG_FF55;
}

void *memalloc(u16 size)
{
	memory_node_t *m = memory_alloc_work;
	memory_node_t *n;
	memory_node_t *o;
	
	while(m->unk2 != (memory_node_t *)MEMORY_FLAG_FF42)
	{
		if(m->unk6 == MEMORY_FLAG_FF46 && ((8 + size) <= m->unk4))
		{
			n = (memory_node_t*)((u16)(m+1) + size);
			o = m->unk2;
			n->unk0 = m;
			n->unk2 = o;
			n->unk4 = m->unk4 - (8 + size);
			n->unk6 = MEMORY_FLAG_FF46;

			m->unk2 = n;
			m->unk4 = size;
			m->unk6 = MEMORY_FLAG_FF55;
			o->unk0 = n;

			return m+1;
		}
		m = m->unk2;
	}
	return 0;
}

static void near unk_81589(memory_node_t *n)
{
	memory_node_t *a, *b;

	a = n->unk2;
	b = a->unk2;
	if(a->unk6 == MEMORY_FLAG_FF46)
	{
		n->unk2 = a->unk2;
		b->unk0 = a->unk0;
		n->unk4 += a->unk4 + sizeof(memory_node_t);

	}
}

static void near unk_815B0(memory_node_t *n)
{
	n = n->unk0;
	if(n->unk6 == MEMORY_FLAG_FF46)
	{
		unk_81589(n);
	}
}

void memfree(memory_node_t *n)
{
	n--;
	n->unk6 = MEMORY_FLAG_FF46;
	unk_81589(n);
	unk_815B0(n);
}

void memory_test_init(void *buf)
{
/*	u8 val;
	s16 i = 0;
	char buf1[256];
	char buf2[256];
	u8 far *ptr;
	char *dst;

	task_delete();
	task_append((task_pointer)unk_81A34, 0);
	font_load(1, DFONT_char_adr);
	cls(1);

	ptr = fstr1;
	dst = buf1;
	while (*dst++ = *ptr++);
	print(1, 1, 1, buf1, DFONT_char_adr);

	ptr = fstr2;
	dst = buf1;
	while (*dst++ = *ptr++);
	print(1, 2, 1, buf1, DFONT_char_adr);

	ptr = fstr3;
	dst = buf1;
	while (*dst++ = *ptr++);
	hsprintf(buf2, buf1, 0x400);
	print(1, 3, 1, buf2, DFONT_char_adr);
	
	ptr = fstr4;
	dst = buf1;
	while (*dst++ = *ptr++);
	hsprintf(buf2, buf1, 0x6E);
	print(1, 4, 1, buf2, DFONT_char_adr);

	nbg_ddf(1, 1);*/

	task_delete; //Force include
	task_append; //Force include
	font_load; //Force include
	cls; //Force include
	print; //Force include
	hsprintf; //Force include
	nbg_ddf; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0204");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unk_81A34_");
	ASM_INLINE("MOV	BX,SEG unk_81A34_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	DX,0xA000");
	ASM_INLINE("CALLF	font_load_, SEG font_load_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("CALLF	cls_, SEG cls_");
	ASM_INLINE("MOV	[BP-0x04].W,fstr1_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr1_");
	ASM_INLINE("LEA	SI,[BP-0x0104].B");
ASM_INLINE("_8161E:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("MOV	[SI].B,BL");
	ASM_INLINE("INC	SI");
	ASM_INLINE("TEST	BL,BL");
	ASM_INLINE("JNZ	_8161E");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0104].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	[BP-0x04].W,fstr2_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr2_");
	ASM_INLINE("LEA	SI,[BP-0x0104].B");
ASM_INLINE("_8165A:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("MOV	[SI].B,BL");
	ASM_INLINE("INC	SI");
	ASM_INLINE("TEST	BL,BL");
	ASM_INLINE("JNZ	_8165A");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0002");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0104].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	[BP-0x04].W,fstr3_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr3_");
	ASM_INLINE("LEA	SI,[BP-0x0104].B");
ASM_INLINE("_81696:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("MOV	[SI].B,BL");
	ASM_INLINE("INC	SI");
	ASM_INLINE("TEST	BL,BL");
	ASM_INLINE("JNZ	_81696");
	ASM_INLINE("MOV	BX,0x0400");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	BX,[BP-0x0104].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	BX,[BP-0x0204].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0003");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	[BP-0x04].W,fstr4_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr4_");
	ASM_INLINE("LEA	SI,[BP-0x0104].B");
ASM_INLINE("_816E8:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("MOV	[SI].B,BL");
	ASM_INLINE("INC	SI");
	ASM_INLINE("TEST	BL,BL");
	ASM_INLINE("JNZ	_816E8");
	ASM_INLINE("MOV	BX,0x096E");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	BX,[BP-0x0104].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	BX,[BP-0x0204].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0004");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("MOV	SI,0x0005");
	ASM_INLINE("MOV	BX,0x096E");
	ASM_INLINE("POP	AX");
ASM_INLINE("_8173E:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,BX");
	ASM_INLINE("SUB	CX,0x096E");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	CX,str0_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	DX,0x0000");
	ASM_INLINE("MOV	CX,0xA000");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("MOV	CX,[BX].W");
	ASM_INLINE("CMP	CX,0xFF42");
	ASM_INLINE("JZ	_81798");
	ASM_INLINE("CMP	CX,0xFF41");
	ASM_INLINE("JNZ	_817AD");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,str1_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("JMP	_817C7");
ASM_INLINE("_81798:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,str2_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("JMP	_817C7");
ASM_INLINE("_817AD:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,[BX].W");
	ASM_INLINE("SUB	CX,0x096E");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	CX,str3_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("POP	BX");
ASM_INLINE("_817C7:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	DX,0x0000");
	ASM_INLINE("MOV	CX,0xA000");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,0x0006");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("MOV	CX,[BX+0x02].W");
	ASM_INLINE("CMP	CX,0xFF42");
	ASM_INLINE("JZ	_81809");
	ASM_INLINE("CMP	CX,0xFF41");
	ASM_INLINE("JNZ	_8181E");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,str4_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("JMP	_81839");
ASM_INLINE("_81809:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,str5_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("JMP	_81839");
ASM_INLINE("_8181E:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,[BX+0x02].W");
	ASM_INLINE("SUB	CX,0x096E");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	CX,str6_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("POP	BX");
ASM_INLINE("_81839:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	DX,0x0000");
	ASM_INLINE("MOV	CX,0xA000");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,0x000B");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	[BX+0x04].W");
	ASM_INLINE("MOV	CX,str7_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	DX,0x0000");
	ASM_INLINE("MOV	CX,0xA000");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,0x0010");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,[BX+0x06].W");
	ASM_INLINE("CMP	CX,0xFF55");
	ASM_INLINE("JZ	_818AC");
	ASM_INLINE("CMP	CX,0xFF46");
	ASM_INLINE("JNZ	_818BF");
	ASM_INLINE("MOV	CX,str8_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("JMP	_818D0");
ASM_INLINE("_818AC:");
	ASM_INLINE("MOV	CX,str9_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("JMP	_818D0");
ASM_INLINE("_818BF:");
	ASM_INLINE("MOV	CX,str10_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("LEA	CX,[BP-0x0204].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0004");
ASM_INLINE("_818D0:");
	ASM_INLINE("MOV	DX,0x0000");
	ASM_INLINE("MOV	CX,0xA000");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,0x0015");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	BX");
	ASM_INLINE("MOV	CX,[BX+0x06].W");
	ASM_INLINE("CMP	CX,0xFF55");
	ASM_INLINE("POP	AX");
	ASM_INLINE("JZ	_81902");
	ASM_INLINE("CMP	CX,0xFF46");
	ASM_INLINE("JNZ	_81905");
	ASM_INLINE("ADD	AX,[BX+0x04].W");
	ASM_INLINE("JMP	_81905");
ASM_INLINE("_81902:");
	ASM_INLINE("ADD	DI,[BX+0x04].W");
ASM_INLINE("_81905:");
	ASM_INLINE("INC	SI");
	ASM_INLINE("CMP	[BX+0x02].W,0xFF42");
	ASM_INLINE("JZ	_81913");
	ASM_INLINE("MOV	BX,[BX+0x02].W");
	ASM_INLINE("JMP	_8173E");
ASM_INLINE("_81913:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	[BP-0x04].W,fstr5_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr5_");
	ASM_INLINE("LEA	DI,[BP-0x0104].B");
ASM_INLINE("_81923:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_81923");
	ASM_INLINE("POP	DI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("LEA	BX,[BP-0x0104].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	BX,[BP-0x0204].B");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	SI");
	ASM_INLINE("MOV	[BP-0x04].W,fstr6_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr6_");
	ASM_INLINE("LEA	DI,[BP-0x0104].B");
ASM_INLINE("_81973:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,BL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	BL,BL");
	ASM_INLINE("JNZ	_81973");
	ASM_INLINE("POP	AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0104].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0204].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0204].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	SI");
	ASM_INLINE("MOV	[BP-0x04].W,fstr7_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr7_");
	ASM_INLINE("LEA	DI,[BP-0x0104].B");
ASM_INLINE("_819C3:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_819C3");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0104].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	SI");
	ASM_INLINE("MOV	[BP-0x04].W,fstr8_");
	ASM_INLINE("MOV	[BP-0x02].W,SEG fstr8_");
	ASM_INLINE("LEA	DI,[BP-0x0104].B");
ASM_INLINE("_819FF:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	AL,ES:[BX].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_819FF");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0104].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_81A34()
{
	if((pad[0].unk0 & 0x0800) && (pad[0].unk0 & 0x0200) && (pad[0].unk4 & 0x0004))
	{
		print(1, 0, 1, str11, DFONT_char_adr);
    	meminit();
	}
	if((pad[0].unk0 & 0x8000) && (pad[0].unk0 & 0x2000) && (pad[0].unk4 & 0x0004))
	{
		task_delete();
		task_append((task_pointer)memory_dump_init, 0);
	}
	if(pad[0].unk0 & 0x1000)
	{
		unk0 = 0;
	}
	if(pad[0].unk0 & 0x4000)
	{
		unk0 = 1;
	}
	if(unk0)
	{
		switch(rand() & 3)
		{
			case 0:
			{
				pad[0].unk4 |= 0x0100;
				break;
			}
			case 1:
			{
				pad[0].unk4 |= 0x0200;
				break;
			}
			case 2:
			{
				pad[0].unk4 |= 0x0400;
				break;
			}
			case 3:
			{
				pad[0].unk4 |= 0x0800;
				break;
			}
		}
	}
	if(pad[0].unk4 & 0x0100)
	{
		if(unk1)
		{
			memfree(unk1);
			unk1 = NULL;
		}
		else
		{
			unk1 = memalloc(1);
		}
		task_delete();
		task_append((task_pointer)memory_test_init, 0);
	}
	if(pad[0].unk4 & 0x0200)
	{
		if(unk2)
		{
			memfree(unk2);
			unk2 = NULL;
		}
		else
		{
			unk2 = memalloc(2);
		}
		task_delete();
		task_append((task_pointer)memory_test_init, 0);
	}
	if(pad[0].unk4 & 0x0400)
	{
		if(unk3)
		{
			memfree(unk3);
			unk3 = NULL;
		}
		else
		{
			unk3 = memalloc(3);
		}
		task_delete();
		task_append((task_pointer)memory_test_init, 0);
	}
	if(pad[0].unk4 & 0x0800)
	{
		if(unk4)
		{
			memfree(unk4);
			unk4 = NULL;
		}
		else
		{
			unk4 = memalloc(4);
		}
		task_delete();
		task_append((task_pointer)memory_test_init, 0);
	}
	if(pad[0].unk4 & 0x0002)
	{
		task_delete();
	}
}

static void unk_81BF4(s16 unk, s16 unk2, u16 unk3)
{
	font_putXY(unk3, 8, 1, 1, unk >> 3, unk2 >> 3, 0, KEYBOARD_char_adr);
}

static void unk_81C27(u16 unk)
{
	font_putXY(0x10, 2 + unk, 3, 1, 3, 0, 0, KEYBOARD_char_adr);
}

static void unk_81C56(u16 unk)
{
	unk_81BF4(0x50, 0, (unk >> 12) & 0xf);
	unk_81BF4(0x58, 0, (unk >>  8) & 0xf);
	unk_81BF4(0x60, 0, (unk >>  4) & 0xf);
	unk_81BF4(0x68, 0, (unk >>  0) & 0xf);
}

static void unk_81CB3(u16 unk)
{
	unk_81BF4(0x88, 0, (unk >> 12) & 0xf);
	unk_81BF4(0x90, 0, (unk >>  8) & 0xf);
	unk_81BF4(0x98, 0, (unk >>  4) & 0xf);
	unk_81BF4(0xA0, 0, (unk >>  0) & 0xf);
}

static void unk_81D10(s16 unk)
{
	unk_81BF4(0xC0, 0, (unk >>  4) & 0xf);
	unk_81BF4(0xC8, 0, (unk >>  0) & 0xf);
}

static void unk_81D3F(u16 unk, u16 unk2, u8 *unk3, u16 unk4)
{
	/*u16 i;
	u16 j;
	u16 val;
	u16 val2;

	val = 0;
	val |= unk2;
	val2 = 0;

	switch(unk)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
		{
			for (i = 0; i < 8; i++)
			{
				unk_81BF4(0x00, i * 8 + 0x10, ((u16)unk3 >> 12) & 0xf);
				unk_81BF4(0x08, i * 8 + 0x10, ((u16)unk3 >>  8) & 0xf);
				unk_81BF4(0x10, i * 8 + 0x10, ((u16)unk3 >>  4) & 0xf);
				unk_81BF4(0x18, i * 8 + 0x10, ((u16)unk3 >>  0) & 0xf);
				for (j = 0; j < 8; j++)
				{
					unk_81BF4(j * 0x18 + 0x28, i * 8 + 0x10, ((*unk3 >> 4) & 0xf));
					unk_81BF4(j * 0x18 + 0x30, i * 8 + 0x10, ((*unk3 >> 0) & 0xf));
					unk3++;
				}
			}
			break;
		}
		case 3:
			break;
	}*/

	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0004");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("MOV	BX,BX");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("OR	DX,CX");
	ASM_INLINE("OR	BX,SI");
	ASM_INLINE("MOV	[BP-0x04].W,DX");
	ASM_INLINE("MOV	[BP-0x02].W,BX");
	ASM_INLINE("CMP	AX,0x0003");
	ASM_INLINE("JNZ	_81D63");
	ASM_INLINE("JMP	_81E5B");
ASM_INLINE("_81D63:");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JZ	_81D7A");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JNZ	_81D70");
	ASM_INLINE("JMP	_81E5B");
ASM_INLINE("_81D70:");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_81D77");
	ASM_INLINE("JMP	_81E5B");
ASM_INLINE("_81D77:");
	ASM_INLINE("JMP	_81E5B");
ASM_INLINE("_81D7A:");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_81E53");
ASM_INLINE("_81D7F:");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("MOV	DX,[BP-0x04].W");
	ASM_INLINE("MOV	CL,0x0C");
	ASM_INLINE("SHR	DX,CL");
	ASM_INLINE("AND	DX,0x000F");
	ASM_INLINE("MOV	CX,DX");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("MOV	AX,0x0008");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("MOV	DX,[BP-0x04].W");
	ASM_INLINE("MOV	CL,0x08");
	ASM_INLINE("SHR	DX,CL");
	ASM_INLINE("AND	DX,0x000F");
	ASM_INLINE("MOV	CX,DX");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("MOV	AX,0x0010");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("MOV	CX,[BP-0x04].W");
	ASM_INLINE("SHR	CX,1");
	ASM_INLINE("SHR	CX,1");
	ASM_INLINE("SHR	CX,1");
	ASM_INLINE("SHR	CX,1");
	ASM_INLINE("AND	CX,0x000F");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("MOV	AX,0x0018");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("MOV	CX,[BP-0x04].W");
	ASM_INLINE("AND	CX,0x000F");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("JMP	_81E4D");
ASM_INLINE("_81DFE:");
	ASM_INLINE("INC	[BP-0x04].W");
	ASM_INLINE("LES	BX,[BP-0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	CL,ES:[BX].B");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,0x0018");
	ASM_INLINE("MUL	DI");
	ASM_INLINE("ADD	AX,0x0028");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("AND	CL,0x0F");
	ASM_INLINE("XOR	CH,CH");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("MOV	AX,0x0018");
	ASM_INLINE("MUL	DI");
	ASM_INLINE("ADD	AX,0x0030");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("ADD	BX,0x0010");
	ASM_INLINE("POP	CX");
	ASM_INLINE("AND	CL,0x0F");
	ASM_INLINE("XOR	CH,CH");
	ASM_INLINE("CALLF	unk_81BF4_, SEG unk_81BF4_");
	ASM_INLINE("INC	DI");
ASM_INLINE("_81E4D:");
	ASM_INLINE("CMP	DI,0x0008");
	ASM_INLINE("JL	_81DFE");
	ASM_INLINE("INC	SI");
ASM_INLINE("_81E53:");
	ASM_INLINE("CMP	SI,0x0008");
	ASM_INLINE("JGE	_81E5B");
	ASM_INLINE("JMP	_81D7F");
ASM_INLINE("_81E5B:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

void memory_dump_init()
{
	s16 i, j;
	s16 val;
	s16 val2;

	task_delete();
	task_append((task_pointer)unk_82093, 0);
	nbg_ddf(0, 0);
	nbg_ddf(1, 0);
	font_load(1,KEYBOARD_char_adr);

	val = *(s16 far*)(&KEYBOARD_char_adr[4]) >> 3;
	val -= 1;
	val2 = get_bmp_cell_no(val, 0, KEYBOARD_char_adr);

	for(i = 0; i < 0x20; i++)
	{
		for(j = 0; j < 0x20; j++)
		{
			put_cell_no(j * 8, i * 8, 0, val2);
			put_cell_no(j * 8, i * 8, 1, val2 | 0x0800);
		}
	}

	val2 = get_bmp_cell_no(15, 7, KEYBOARD_char_adr);
	put_cell_no(0x10, 0, 1, val2 | 0x0A00);
	put_cell_no(0x48, 0, 1, val2 | 0x0A00);
	put_cell_no(0x80, 0, 1, val2 | 0x0A00);
	put_cell_no(0xB8, 0, 1, val2 | 0x0A00);

	for(i = 0; i < 10; i++)
	{
		put_cell_no(0x18, (1 + i) * 8, 1, val2 | 0x0A00);
	}

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 0x1C; j++)
		{
			val2 = get_bmp_cell_no(j, i, KEYBOARD_char_adr);
			put_cell_no(j * 8, i * 8, 0, val2);
		}
	}

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 0x1C; j++)
		{
			val2 = get_bmp_cell_no(j, 10 + i, KEYBOARD_char_adr);
			put_cell_no(j * 8, (10 + i) * 8, 0, val2);
		}
	}

	font_putXY(0, 12, 0x1c, 6, 0, 12, 1, KEYBOARD_char_adr);

	memory_test.unk0 = 2;
	memory_test.unk2 = 0;
	memory_test.unk4 = 0x1000;
	memory_test.unk6 = 0;

	unk_81C27(memory_test.unk0);
	unk_81C56(memory_test.unk4);
	unk_81CB3(memory_test.unk6);
	unk_81D10(memory_test.unk2);
	unk_81D3F(memory_test.unk0, memory_test.unk4, memory_test.unk6, memory_test.unk2);

	nbg_ddf(0, 1);
	nbg_ddf(1, 1);
}

static void unk_82093()
{
	if(pad[0].unk8 & 0x0100)
	{
		memory_test.unk6 -= 16;
		unk_81D3F(memory_test.unk0, memory_test.unk4, memory_test.unk6, memory_test.unk2);
	}
	else if(pad[0].unk8 & 0x0400)
	{
		memory_test.unk6 += 16;
		unk_81D3F(memory_test.unk0, memory_test.unk4, memory_test.unk6, memory_test.unk2);
	}
	if(pad[0].unk8 & 0x0200)
	{
		memory_test.unk6 -= 1;
		unk_81D3F(memory_test.unk0, memory_test.unk4, memory_test.unk6, memory_test.unk2);
	}
	else if(pad[0].unk8 & 0x0800)
	{
		memory_test.unk6 += 1;
		unk_81D3F(memory_test.unk0, memory_test.unk4, memory_test.unk6, memory_test.unk2);
	}
	if(pad[0].unk4 & 0x02)
	{
		task_delete();
	}
}








