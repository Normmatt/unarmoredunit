
#include <machine.h>
#include "types.h"
#include "STORY.h"
#include "PUT_TEXT.h"
#include "SWAN_L_C.h"
#include "SPRINTF.h"

extern u8 G_FACE_char_adr[];
extern u8 G_GAME_char_adr[];
extern u8 G_MSG_bin_adr[];
extern u8 G_FON16H_char_adr[];
extern u8 G_FON16L_char_adr[];

// "DUMMY"
static const char far unk00[] = "¥x0Eﾀﾞﾐｰ";

// "Not enough energy"
static const char far unk01[] = "¥x0Eｴﾈﾙｷﾞｰ¥x0Fｶﾞﾀﾘﾏｾﾝ";

// "Charging"
static const char far unk02[] = "¥x0Eﾁｬｰｼﾞ¥x0Fﾁｭｳﾃﾞｽ";

// "Search area designation"
static const char far unk03[] = "¥x0Eｻｰﾁｴﾘｱ¥x0Fﾉｼﾃｲ";

// "Enemy AU discovered!"
static const char far unk04[] = "¥x0FﾃｷAUｦﾊｯｹﾝ!";

// "Enemy AU detected"
static const char far unk05[] = "¥x0FﾃｷAUｦｶﾝﾁｼﾏｼﾀ";

// "No response"
static const char far unk06[] = "¥x0Fﾊﾝﾉｳﾊｱﾘﾏｾﾝ";

// "Please select a target"
static const char far unk07[] = "¥x0Fﾓｸﾋｮｳｦｷﾒﾃｸﾀﾞｻｲ";

// "Hit! %1d damage!"
static const char far unk08[] = "¥x0Eﾋｯﾄ!%1d¥x0Fﾉ¥x0Eﾀﾞﾒｰｼﾞ!";

// "Miss / No damage"
static const char far unk09[] = "¥x0Eﾐｽ･ﾉｰﾀﾞﾒｰｼﾞ";

// "Took %1d damage!"
static const char far unk10[] = "¥x0F%1dﾉ¥x0Eﾀﾞﾒｰｼﾞ¥x0Fｦｸﾗｯﾀ!";

// "Select command"
static const char far unk11[] = "¥x0Eｺﾏﾝﾄﾞ¥x0Fｦｾﾝﾀｸ";

// "Attack %1d ready"
static const char far unk12[] = "Attack %1d ready";

// "Won a battle!"
static const char far unk13[] = "Won a battle!";

// "Stage Cleared"
static const char far unk14[] = "Stage Cleared";

// "Lost a battle"
static const char far unk15[] = "Lost a battle";

// "Mission failed"
static const char far unk16[] = "Mission failed";

// "Draw a battle"
static const char far unk17[] = "Draw a battle";

// "Hit A Button!"
static const char far unk18[] = "Hit A Button!";

// "Wait.."
static const char far unk19[] = "Wait..";

// "AU movement"
static const char far unk20[] = "AU¥x0Fﾉｲﾄﾞｳ";

// "Standard search"
static const char far unk21[] = "¥x0Fﾋｮｳｼﾞｭﾝﾃｷﾅ¥x0Eｻｰﾁ";

// "Low-cost search"
static const char far unk22[] = "¥x0Eｺｽﾄ¥x0Fﾉｶﾙｲ¥x0Eｻｰﾁ";

// "High-performance search equipment"
static const char far unk23[] = "¥x0Fｺｳｾｲﾉｳﾅ¥x0Eｻｰﾁ¥x0Fｿｳﾋﾞ";

// "Standard weapon"
static const char far unk24[] = "¥x0Fﾋｮｳｼﾞｭﾝﾃｷﾅﾌﾞｷ";

// "Powerful rifle"
static const char far unk25[] = "¥x0Fｲﾘｮｸﾉｱﾙ¥x0Eﾗｲﾌﾙ";

// "Long-range laser"
static const char far unk26[] = "¥x0Fｼｬﾃｲﾉﾅｶﾞｲ¥x0Eﾚｰｻﾞｰ";

// "Medium-type linear weapon"
static const char far unk27[] = "¥x0Fﾁｭｳｶﾞﾀﾉ¥x0Eﾘﾆｱ¥x0Fﾍｲｷ";

// "Small gun"
static const char far unk28[] = "¥x0Fｺｶﾞﾀﾉｼﾞｭｳ";

// "Powerful gun"
static const char far unk29[] = "¥x0Fﾊｶｲﾘｮｸﾉｱﾙｼﾞｭｳ";

// "Search-capable bomb"
static const char far unk30[] = "¥x0Eｻｰﾁ¥x0Fｶﾉｳﾅ¥x0Eﾎﾞﾑ";

// "Anti-AU small missile"
static const char far unk31[] = "¥x0FﾀｲAUﾖｳｺｶﾞﾀ¥x0Eﾐｻｲﾙ";

// "Wide-range explosive shell"
static const char far unk32[] = "¥x0Fﾊﾝｲﾉﾋﾛｲｻｸﾚﾂﾀﾞﾝ";

// "Fires multiple shots"
static const char far unk33[] = "¥x0Fﾑｽｳﾉﾀﾏｦﾊｯｼｬｽﾙ";

// "Wide-area laser"
static const char far unk34[] = "¥x0Fｺｳｶﾉﾋﾛｲ¥x0Eﾚｰｻﾞｰ";

// "AU-use warp device"
static const char far unk35[] = "AU¥x0Fﾖｳﾉ¥x0Eﾜｰﾌﾟ¥x0Fｿｳﾁ";

// "Double movement possible"
static const char far unk36[] = "2¥x0Fﾊﾞｲﾉｲﾄﾞｳｶﾞｶﾉｳ";

// "Charge 10 ENG"
static const char far unk37[] = "ENG¥x0Fｦ10¥x0Eﾁｬｰｼﾞ¥x0Fｽﾙ";

// "Disturb enemy information"
static const char far unk38[] = "¥x0Fﾃｷﾉｼﾞｮｳﾎｳｦｶｸﾗﾝ";

// "Copy enemy appearance"
static const char far unk39[] = "¥x0Fﾃｷﾉｽｶﾞﾀｦｳﾂｽ";

// "Decoy unit"
static const char far unk40[] = "¥x0Fｵﾄﾘﾖｳ¥x0Eﾕﾆｯﾄ";

// "Copy enemy appearance" (duplicate of unk39)
static const char far unk41[] = "¥x0Fﾃｷﾉｽｶﾞﾀｦｳﾂｽ";

// "Melee weapon"
static const char far unk42[] = "¥x0Fｷﾝｾﾂﾖｳﾉﾌﾞｷ";

// "Federation weapon 2"
static const char far unk43[] = "¥x0Fﾚﾝﾎﾟｳﾉ¥x0Eﾌﾞｷ2";

// "Federation weapon 1"
static const char far unk44[] = "¥x0Fﾚﾝﾎﾟｳﾉ¥x0Eﾌﾞｷ1";

// "Raise max HP"
static const char far unk45[] = "¥x0FHPﾉMAXｦｱｹﾞﾏｽ";

// "Raise max ENG"
static const char far unk46[] = "ENG¥x0FﾉMAXｦｱｹﾞﾏｽ";

// "Lower max HP"
static const char far unk47[] = "¥x0FHPﾉMAXｦｻｹﾞﾏｽ";

// "Lower max ENG"
static const char far unk48[] = "ENG¥x0FﾉMAXｦｻｹﾞﾏｽ";

// "Cannot increase further"
static const char far unk49[] = "¥x0Fｺﾚｲｼﾞｮｳﾌｴﾏｾﾝ";

// "Cannot decrease further"
static const char far unk50[] = "¥x0Fｺﾚｲｼﾞｮｳﾍﾘﾏｾﾝ";

// "This part cannot be removed"
static const char far unk51[] = "¥x0Fｺﾉ¥x0Eﾊﾟｰﾂ¥x0Fﾊﾊｽﾞｾﾏｾﾝ";

// "Cannot do any more"
static const char far unk52[] = "¥x0Fｺﾚｲｼﾞｮｳﾃﾞｷﾏｾﾝ";

// "Tuning finished"
static const char far unk53[] = "¥x0Eﾁｭｰﾝ¥x0Fｦｼｭｳﾘｮｳｼﾏｽ";

// "Not enough TP"
static const char far unk54[] = "¥x0FTPｶﾞﾀﾘﾏｾﾝ";

// "Raise max HP"
static const char far unk55[] = "¥x0FHPﾉMAXｦｱｹﾞﾏｽ";

// "Raise max EN"
static const char far unk56[] = "EN¥x0FﾉMAXｦｱｹﾞﾏｽ";

static const u8 far * far unk57[] = {
	NULL,
	unk01,
	unk02,
	unk03,
	unk04,
	unk05,
	unk06,
	unk07,
	unk08,
	unk09,
	unk10,
	unk11,
};

static const u8 far * far unk58[] = {
	NULL,
	unk12,
	unk13,
	unk14,
	unk15,
	unk16,
	unk17,
	unk18,
	unk19,
};

static const u8 far * far unk59[] = {
	NULL,
	unk20,
	unk21,
	unk22,
	unk23,
	unk24,
	unk25,
	unk26,
	unk27,
	unk28,
	unk29,
	unk30,
	unk31,
	unk32,
	unk33,
	unk34,
	unk35,
	unk36,
	unk37,
	unk38,
	unk39,
	unk40,
	unk41,
	unk42,
	unk43,
	unk44,
	NULL,
	NULL,
	NULL,
	unk45,
	unk46,
	unk47,
	unk48,
	unk49,
	unk50,
	unk51,
	unk52,
	unk53,
	unk54,
	unk55,
	unk56,
};

void put_message()
{
	font_put2XY; //Force include
	hsprintf; //Force include
	G_GAME_char_adr; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0084");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	DX,SI");
	ASM_INLINE("MOV	CL,0x0F");
	ASM_INLINE("SAR	DX,CL");
	ASM_INLINE("AND	DX,0x0001");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	CL,0x08");
	ASM_INLINE("SAR	AX,CL");
	ASM_INLINE("AND	AX,0x007F");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("AND	SI,0x00FF");
	ASM_INLINE("LEA	DI,[BP-0x40].B");
	ASM_INLINE("MOV	[BP-0x44].W,0x0000");
	ASM_INLINE("MOV	[BP-0x42].W,0xCF3E");
	ASM_INLINE("MOV	DX,G_GAME_char_adr_");
	ASM_INLINE("MOV	CX,SEG G_GAME_char_adr_");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	CX,0x0010");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0010");
	ASM_INLINE("MOV	CX,0x001C");
	ASM_INLINE("MOV	DX,0x0002");
	ASM_INLINE("CALLF	font_put2XY_, SEG font_put2XY_");
	ASM_INLINE("ADD	SP,0x000A");
	ASM_INLINE("TEST	SI,SI");
	ASM_INLINE("POP	AX");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	BX");
	ASM_INLINE("JNZ	_90485");
	ASM_INLINE("JMP	_90585");
ASM_INLINE("_90485:");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("CMP	AX,0x0002");
	ASM_INLINE("JZ	_904F9");
	ASM_INLINE("CMP	AX,0x0001");
	ASM_INLINE("JZ	_904C8");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_90497");
	ASM_INLINE("JMP	_90528");
ASM_INLINE("_90497:");
	ASM_INLINE("MOV	AX,0xCF72");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("LES	BX,ES:[BX+0x000A]");
	ASM_OP5(0x26,0xC4,0x9F,0x0A,0x00);
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_90528");
	ASM_INLINE("MOV	AX,0xCF72");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("SHL	SI,1");
	ASM_INLINE("SHL	SI,1");
	//ASM_INLINE("MOV	AX,ES:[SI+0x000A].W");
	ASM_OP5(0x26,0x8B,0x84,0x0A,0x00);
	//ASM_INLINE("MOV	CX,ES:[SI+0x000C].W");
	ASM_OP5(0x26,0x8B,0x8C,0x0C,0x00);
	ASM_INLINE("MOV	[BP-0x44].W,AX");
	ASM_INLINE("MOV	[BP-0x42].W,CX");
	ASM_INLINE("JMP	_90528");
ASM_INLINE("_904C8:");
	ASM_INLINE("MOV	AX,0xCF75");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("LES	BX,ES:[BX+0x000A]");
	ASM_OP5(0x26,0xC4,0x9F,0x0A,0x00);
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_90528");
	ASM_INLINE("MOV	AX,0xCF75");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("SHL	SI,1");
	ASM_INLINE("SHL	SI,1");
	//ASM_INLINE("MOV	AX,ES:[SI+0x000A].W");
	ASM_OP5(0x26,0x8B,0x84,0x0A,0x00);
	//ASM_INLINE("MOV	CX,ES:[SI+0x000C].W");
	ASM_OP5(0x26,0x8B,0x8C,0x0C,0x00);
	ASM_INLINE("MOV	[BP-0x44].W,AX");
	ASM_INLINE("MOV	[BP-0x42].W,CX");
	ASM_INLINE("JMP	_90528");
ASM_INLINE("_904F9:");
	ASM_INLINE("MOV	AX,0xCF77");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("LES	BX,ES:[BX+0x000E]");
	ASM_OP5(0x26,0xC4,0x9F,0x0E,0x00);
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_90528");
	ASM_INLINE("MOV	AX,0xCF77");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("SHL	SI,1");
	ASM_INLINE("SHL	SI,1");
	//ASM_INLINE("MOV	AX,ES:[SI+0x000E].W");
	ASM_OP5(0x26,0x8B,0x84,0x0E,0x00);
	//ASM_INLINE("MOV	CX,ES:[SI+0x0010].W");
	ASM_OP5(0x26,0x8B,0x8C,0x10,0x00);
	ASM_INLINE("MOV	[BP-0x44].W,AX");
	ASM_INLINE("MOV	[BP-0x42].W,CX");
ASM_INLINE("_90528:");
	ASM_INLINE("INC	[BP-0x44].W");
	ASM_INLINE("LES	SI,[BP-0x44]");
	ASM_INLINE("DEC	SI");
	ASM_INLINE("MOV	AL,ES:[SI].B");
	ASM_INLINE("MOV	[DI].B,AL");
	ASM_INLINE("INC	DI");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_90528");
	ASM_INLINE("POP	BX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("LEA	AX,[BP-0x40].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0084].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("CMP	DX,0x0001");
	ASM_INLINE("JZ	_9056E");
	ASM_INLINE("TEST	DX,DX");
	ASM_INLINE("JNZ	_90585");
	ASM_INLINE("LEA	AX,[BP-0x0084].B");
	ASM_INLINE("PUSH	SS");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0082");
	ASM_INLINE("MOV	CX,0x00E0");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALL	unk_9058D_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("JMP	_90585");
ASM_INLINE("_9056E:");
	ASM_INLINE("LEA	AX,[BP-0x0084].B");
	ASM_INLINE("PUSH	SS");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0082");
	ASM_INLINE("MOV	CX,0x00E0");
	ASM_INLINE("MOV	DX,0x0001");
	ASM_INLINE("CALL	unk_90663_");
	ASM_INLINE("ADD	SP,0x0004");
ASM_INLINE("_90585:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_9058D()
{
	get_bmp_cell_pixel; //Force include
	G_MSG_bin_adr; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0008");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	[BP-0x02].W,AX");
	ASM_INLINE("MOV	[BP-0x04].W,BX");
	ASM_INLINE("MOV	[BP-0x06].W,DX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	[BP-0x08].W,0x0000");
	ASM_INLINE("JMP	_9064F");
ASM_INLINE("_905AA:");
	ASM_INLINE("INC	[BP+0x04].W");
	ASM_INLINE("LES	BX,[BP+0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("CMP	BL,0x0F");
	ASM_INLINE("JZ	_905C3");
	ASM_INLINE("CMP	BL,0x0E");
	ASM_INLINE("JNZ	_905C9");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("JMP	_9064F");
ASM_INLINE("_905C3:");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("JMP	_9064F");
ASM_INLINE("_905C9:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JZ	_905E1");
	ASM_INLINE("CMP	BL,0xA0");
	ASM_INLINE("JB	_905E1");
	ASM_INLINE("CMP	BL,0xC0");
	ASM_INLINE("JB	_905DD");
	ASM_INLINE("MOV	DL,0x20");
	ASM_INLINE("JMP	_905DF");
ASM_INLINE("_905DD:");
	ASM_INLINE("MOV	DL,0xE0");
ASM_INLINE("_905DF:");
	ASM_INLINE("ADD	BL,DL");
ASM_INLINE("_905E1:");
	ASM_INLINE("MOV	AL,BL");
	ASM_INLINE("SHL	AL,1");
	ASM_INLINE("SHL	AL,1");
	ASM_INLINE("SHL	AL,1");
	ASM_INLINE("SHL	AL,1");
	ASM_INLINE("AND	AL,0xF0");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("AND	BL,0xF0");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_90636");
ASM_INLINE("_905F8:");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("JMP	_90630");
ASM_INLINE("_905FC:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("ADD	AX,CX");
	ASM_INLINE("ADD	BX,SI");
	ASM_INLINE("MOV	CX,G_MSG_bin_adr_");
	ASM_INLINE("MOV	DX,SEG G_MSG_bin_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_pixel_, SEG get_bmp_cell_pixel_");
	ASM_INLINE("MOV	DI,AX");
	ASM_INLINE("MOV	AX,[BP-0x02].W");
	ASM_INLINE("ADD	AX,[BP-0x08].W");
	ASM_INLINE("POP	CX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("ADD	AX,CX");
	ASM_INLINE("MOV	BX,[BP-0x04].W");
	ASM_INLINE("ADD	BX,SI");
	ASM_INLINE("MOV	CX,[BP-0x06].W");
	ASM_INLINE("MOV	DX,0x0003");
	ASM_INLINE("SUB	DX,DI");
	ASM_INLINE("CALLF	put_cell_pixel_, SEG put_cell_pixel_");
	ASM_INLINE("POP	CX");
	ASM_INLINE("INC	CX");
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	AX");
ASM_INLINE("_90630:");
	ASM_INLINE("CMP	CX,0x000A");
	ASM_INLINE("JL	_905FC");
	ASM_INLINE("INC	SI");
ASM_INLINE("_90636:");
	ASM_INLINE("CMP	SI,0x000C");
	ASM_INLINE("JL	_905F8");
	ASM_INLINE("ADD	[BP-0x08].W,0x000A");
	ASM_INLINE("POP	CX");
	ASM_INLINE("CMP	CX,[BP-0x08].W");
	ASM_INLINE("JGE	_9064E");
	ASM_INLINE("MOV	[BP-0x08].W,0x0000");
	ASM_INLINE("ADD	[BP-0x04].W,0x000C");
ASM_INLINE("_9064E:");
	ASM_INLINE("POP	AX");
ASM_INLINE("_9064F:");
	ASM_INLINE("LES	BX,[BP+0x04]");
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_9065B");
	ASM_INLINE("JMP	_905AA");
ASM_INLINE("_9065B:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void near unk_90663()
{
	font_put2XY; //Force include
	G_FON16H_char_adr; //Force include
	G_FON16L_char_adr; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0004");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("MOV	DI,BX");
	ASM_INLINE("MOV	AX,CX");
	ASM_INLINE("MOV	[BP-0x02].W,DX");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("MOV	[BP-0x04].W,0x0000");
	ASM_INLINE("JMP	_9074A");
ASM_INLINE("_90680:");
	ASM_INLINE("INC	[BP+0x04].W");
	ASM_INLINE("LES	BX,[BP+0x04]");
	ASM_INLINE("DEC	BX");
	ASM_INLINE("MOV	BL,ES:[BX].B");
	ASM_INLINE("CMP	BL,0x0F");
	ASM_INLINE("JZ	_90699");
	ASM_INLINE("CMP	BL,0x0E");
	ASM_INLINE("JNZ	_9069F");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("JMP	_9074A");
ASM_INLINE("_90699:");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("JMP	_9074A");
ASM_INLINE("_9069F:");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("TEST	CX,CX");
	ASM_INLINE("JZ	_906B7");
	ASM_INLINE("CMP	BL,0xA0");
	ASM_INLINE("JB	_906B7");
	ASM_INLINE("CMP	BL,0xC0");
	ASM_INLINE("JB	_906B3");
	ASM_INLINE("MOV	AL,0x20");
	ASM_INLINE("JMP	_906B5");
ASM_INLINE("_906B3:");
	ASM_INLINE("MOV	AL,0xE0");
ASM_INLINE("_906B5:");
	ASM_INLINE("ADD	BL,AL");
ASM_INLINE("_906B7:");
	ASM_INLINE("MOV	AL,BL");
	ASM_INLINE("AND	AL,0x0F");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("MOV	CL,BL");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("SHR	CL,1");
	ASM_INLINE("AND	CL,0x07");
	ASM_INLINE("XOR	CH,CH");
	ASM_INLINE("SHL	CX,1");
	ASM_INLINE("TEST	BL,0x80");
	ASM_INLINE("JZ	_90707");
	ASM_INLINE("MOV	DX,G_FON16H_char_adr_");
	ASM_INLINE("MOV	BX,SEG G_FON16H_char_adr_");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	[BP-0x02].W");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,[BP-0x04].W");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,CX");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0002");
	ASM_INLINE("CALLF	font_put2XY_, SEG font_put2XY_");
	ASM_INLINE("ADD	SP,0x000A");
	ASM_INLINE("JMP	_90737");
ASM_INLINE("_90707:");
	ASM_INLINE("MOV	DX,G_FON16L_char_adr_");
	ASM_INLINE("MOV	BX,SEG G_FON16L_char_adr_");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	[BP-0x02].W");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("ADD	BX,[BP-0x04].W");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("SAR	BX,1");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,CX");
	ASM_INLINE("MOV	CX,0x0002");
	ASM_INLINE("MOV	DX,0x0002");
	ASM_INLINE("CALLF	font_put2XY_, SEG font_put2XY_");
	ASM_INLINE("ADD	SP,0x000A");
ASM_INLINE("_90737:");
	ASM_INLINE("ADD	[BP-0x04].W,0x0010");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CMP	AX,[BP-0x04].W");
	ASM_INLINE("JGE	_90749");
	ASM_INLINE("MOV	[BP-0x04].W,0x0000");
	ASM_INLINE("ADD	DI,0x0010");
ASM_INLINE("_90749:");
	ASM_INLINE("POP	CX");
ASM_INLINE("_9074A:");
	ASM_INLINE("LES	BX,[BP+0x04]");
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_90756");
	ASM_INLINE("JMP	_90680");
ASM_INLINE("_90756:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static s8 near unk_9075E(struct StoryWorkSub *work, u16 unk)
{
	put_cell_pixel; //Force include
	get_bmp_cell_pixel; //Force include
	font_put2XY; //Force include
	G_FACE_char_adr; //Force include
	G_MSG_bin_adr; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0002");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	[BP-0x02].W,AX");
	ASM_INLINE("MOV	DI,BX");
ASM_INLINE("_9076D:");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("LES	SI,[BX+0x0E]");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("ADD	SI,[BX+0x0A].W");
	ASM_INLINE("MOV	AL,ES:[SI].B");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JZ	_9078A");
	ASM_INLINE("CMP	AL,0x09");
	ASM_INLINE("JZ	_9078A");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("INC	[BX+0x0A].W");
ASM_INLINE("_9078A:");
	ASM_INLINE("CMP	AL,0x0A");
	ASM_INLINE("JZ	_90809");
	ASM_INLINE("CMP	AL,0x09");
	ASM_INLINE("JNZ	_90795");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_90795:");
	ASM_INLINE("CMP	AL,0x0F");
	ASM_INLINE("JZ	_907FE");
	ASM_INLINE("CMP	AL,0x0E");
	ASM_INLINE("JZ	_907F3");
	ASM_INLINE("CMP	AL,0x05");
	ASM_INLINE("JZ	_907BA");
	ASM_INLINE("CMP	AL,0x04");
	ASM_INLINE("JZ	_907BA");
	ASM_INLINE("CMP	AL,0x03");
	ASM_INLINE("JZ	_907BA");
	ASM_INLINE("CMP	AL,0x02");
	ASM_INLINE("JZ	_907BA");
	ASM_INLINE("CMP	AL,0x01");
	ASM_INLINE("JZ	_907BA");
	ASM_INLINE("TEST	AL,AL");
	ASM_INLINE("JNZ	_907B8");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_907B8:");
	ASM_INLINE("JMP	_9081B");
ASM_INLINE("_907BA:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	BL,AL");
	ASM_INLINE("DEC	BL");
	ASM_INLINE("MOV	[DI+0x03].B,BL");
	ASM_INLINE("MOV	CX,G_FACE_char_adr_");
	ASM_INLINE("MOV	BX,SEG G_FACE_char_adr_");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,0x0004");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	BX,0x0003");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AL,[DI+0x03].B");
	ASM_INLINE("CBW");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("SHL	AX,1");
	ASM_INLINE("XOR	BX,BX");
	ASM_INLINE("MOV	CX,0x0008");
	ASM_INLINE("MOV	DX,0x0008");
	ASM_INLINE("CALLF	font_put2XY_, SEG font_put2XY_");
	ASM_INLINE("ADD	SP,0x000A");
	ASM_INLINE("POP	AX");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_907F3:");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("MOV	[BX+0x0C].W,0x0000");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_907FE:");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("MOV	[BX+0x0C].W,0x0001");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_90809:");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("MOV	[BX+0x06].W,0x0000");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("ADD	[BX+0x08].W,0x000C");
	ASM_INLINE("JMP	_908AB");
ASM_INLINE("_9081B:");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("CMP	[BX+0x0C].W,0x0000");
	ASM_INLINE("JZ	_90835");
	ASM_INLINE("CMP	AL,0xA0");
	ASM_INLINE("JB	_90835");
	ASM_INLINE("CMP	AL,0xC0");
	ASM_INLINE("JB	_90831");
	ASM_INLINE("MOV	BL,0x20");
	ASM_INLINE("JMP	_90833");
ASM_INLINE("_90831:");
	ASM_INLINE("MOV	BL,0xE0");
ASM_INLINE("_90833:");
	ASM_INLINE("ADD	AL,BL");
ASM_INLINE("_90835:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	DL,AL");
	ASM_INLINE("SHL	DL,1");
	ASM_INLINE("SHL	DL,1");
	ASM_INLINE("SHL	DL,1");
	ASM_INLINE("SHL	DL,1");
	ASM_INLINE("AND	DL,0xF0");
	ASM_INLINE("XOR	DH,DH");
	ASM_INLINE("MOV	BL,AL");
	ASM_INLINE("AND	BL,0xF0");
	ASM_INLINE("XOR	BH,BH");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_9089D");
ASM_INLINE("_90850:");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("JMP	_90897");
ASM_INLINE("_90854:");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	AX,DX");
	ASM_INLINE("ADD	AX,CX");
	ASM_INLINE("ADD	BX,SI");
	ASM_INLINE("MOV	CX,G_MSG_bin_adr_");
	ASM_INLINE("MOV	DX,SEG G_MSG_bin_adr_");
	ASM_INLINE("CALLF	get_bmp_cell_pixel_, SEG get_bmp_cell_pixel_");
	ASM_INLINE("MOV	DI,AX");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("MOV	AX,[BX].W");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("ADD	AX,[BX+0x06].W");
	ASM_INLINE("POP	CX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("ADD	AX,CX");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("MOV	BX,[BX+0x08].W");
	ASM_INLINE("ADD	BX,SI");
	ASM_INLINE("MOV	SI,[BP-0x02].W");
	ASM_INLINE("MOV	CX,[SI+0x12].W");
	ASM_INLINE("MOV	DX,0x0003");
	ASM_INLINE("SUB	DX,DI");
	ASM_INLINE("CALLF	put_cell_pixel_, SEG put_cell_pixel_");
	ASM_INLINE("POP	CX");
	ASM_INLINE("INC	CX");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	DX");
ASM_INLINE("_90897:");
	ASM_INLINE("CMP	CX,0x000A");
	ASM_INLINE("JL	_90854");
	ASM_INLINE("INC	SI");
ASM_INLINE("_9089D:");
	ASM_INLINE("CMP	SI,0x000C");
	ASM_INLINE("JL	_90850");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("ADD	[BX+0x06].W,0x000A");
	ASM_INLINE("POP	AX");
	ASM_INLINE("POP	DI");
ASM_INLINE("_908AB:");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("LES	SI,[BX+0x0E]");
	ASM_INLINE("MOV	BX,[BP-0x02].W");
	ASM_INLINE("ADD	SI,[BX+0x0A].W");
	ASM_INLINE("CMP	ES:[SI].B,0xDE");
	ASM_INLINE("JNZ	_908C0");
	ASM_INLINE("JMP	_9076D");
ASM_INLINE("_908C0:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

s16 put_char(u16 mode, struct StoryWorkSub *work, u16 unk)
{
	s16 res;
	char tmp;

	if(work == NULL)
	{
		return -1;
	}

	if(work->unkE == NULL)
	{
		return -1;
	}

	switch(mode)
	{
		case 0:
		{
			work->unk6 = 0;
			work->unk8 = work->unk2;
			work->unkA = 0;
			work->unkC = 0;
			work->unk14 = 10;
			work->unk16 = 10;
			goto END;
		}
		case 4:
		{
			do
			{
				tmp = unk_9075E(work, unk);
				if(tmp == 0)
				{
					goto END;
				}
				else if(tmp == 9)
				{
					goto END;
				}
			} while (1);
			break;
		}
		case 3:
		{
			work->unk6 = 0;
			work->unk8 = work->unk2;
			if (work->unkE[work->unkA] == 9)
			{
				work->unkA++;
			}
			work->unkC = 0;
			work->unk14 = 10;
			work->unk16 = 10;
			goto END;
		}
		case 2:
		{
			tmp = work->unkE[work->unkA];
			if(tmp == 9)
			{
				goto CASE_09;
			}
			if(tmp != 0)
			{
				goto CASE_00;
			}
		CASE_NEG2:
			return -2;
		CASE_09:
			return 9;
		CASE_00:
			return 0;
		}
		case 1:
		{
			break;
		}
	}
	
	if (work->unk16 >= work->unk14)
	{
		work->unk16 = 0;
	}
	else 
	{
		++work->unk16;
	}

	if (work->unk16)
	{
		return 0;
	}

	do
	{
		do
		{
			tmp = unk_9075E(work, unk);
		} while (tmp == 0x0E);
	} while (tmp == 0x0F);
	if (tmp == 0)
	{
		return -1;
	}
END:
	return 0;
}

