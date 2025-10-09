#include <machine.h>
#include <stdrom.h>
#include "types.h"

#include "ASM.h"
#include "CONSOLE.h"
#include "DEBUG.h"
#include "ending.h"
#include "flash.h"
#include "IP_MES.h"
#include "LOGO.h"
#include "m_cpu2p.h"
#include "m_game.h"
#include "m_sub.h"
#include "m_weapon.h"
#include "MEMORY.h"
#include "menu.h"
#include "PAD.h"
#include "PUT_TEXT.h"
#include "select.h"
#include "SERIAL.h"
#include "SPRINTF.h"
#include "stagesel.h"
#include "story.h"
#include "STRING.h"
#include "SYSTEM.h"
#include "TITLE.h"
#include "tuneup.h"
#include "unisel.h"
#include "SWANMAIN.h"
#include "SWAN_L_C.h"
#include "SOUND_CODE.h"

static char str0[] = "."; /*0178*/
static char str1[] = "%1d.%02d"; /*017A*/
static char str2[] = "%03d"; /*0184*/

static u16 unk0 = 0x0000;

static u16 unkD76; /* 0D76 */
static u16 unkD78; /* 0D78 */
static s16 unkD7A; /* 0D7A */
static u16 unkD7C; /* 0D7C */
static u16 unkD7E; /* 0D7E */

static u8 select_stuff[] = {
	0x01, 0x00, 0xA8, 0xC0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 
	0x02, 0x00
};

static char str3[] = "%04X"; /*01A2*/
static char str4[] = "%04X"; /*01A8*/
static char str5[] = "%04X"; /*01AE*/
static char str6[] = "%04X"; /*01B4*/
static char str7[] = "%04X"; /*01BA*/
static char str8[] = "%04X"; /*01C0*/
static char str9[] = "%04X"; /*01C6*/
static char str10[] = "%04X"; /*01CC*/
static char str11[] = "%04X"; /*01D2*/
static char str12[] = "%04X"; /*01D8*/
static char str13[] = "%04X"; /*01DE*/
static char str14[] = "%03X"; /*01E4*/
static char str15[] = "%04X"; /*01EA*/
static char str16[] = "%04X"; /*01F0*/
static char str17[] = " "; /*01F6*/
static char str18[] = ">"; /*01F8*/
static char str19[] = " "; /*01FA*/
static char str20[] = "max=%2d"; /*01FC*/
static char str21[] = "%2d"; /*0204*/
static char str22[] = "%2d"; /*0208*/

const char far select_debug_text00[] = "   Sammy Special Version    ";
const char far select_debug_text01[] = "     Swan OS level2.13 9/18 ";
const char far select_debug_text02[] = "  Swan ??????????? Program  ";
const char far select_debug_text03[] = "                    By ?????";
const char far select_debug_text04[] = "  Copyright 1998 SUCCESS/   ";
const char far select_debug_text05[] = "    minisoft/switches95/    ";
const char far select_debug_text06[] = "      FillSail/CHARA.       ";
const char far select_debug_text07[] = "----------------------------";
const char far select_debug_text08[] = "        pad check!!         ";
const char far select_debug_text09[] = "X: dat: aeg: rep: Swan-ID : ";
const char far select_debug_text10[] = "0:    :    :    :         : ";
const char far select_debug_text11[] = "1:    :    :    :         : ";
const char far select_debug_text12[] = "       system check!!       ";
const char far select_debug_text13[] = "vCnt:vInt:hCnt:SRct:SWct:cnt";
const char far select_debug_text14[] = "    :    :    :    :    :   ";
const char far select_debug_text15[] = "        sound check!        ";
const char far select_debug_text16[] = "SEno:SE2P:    :    :Seri:Lv.";
const char far select_debug_text17[] = "    :    :    :    :    :   ";

const char far * far select_debug_text_all[] =
{
    select_debug_text00,
    select_debug_text01,
    select_debug_text02,
    select_debug_text03,
    select_debug_text04,
    select_debug_text05,
    select_debug_text06,
    select_debug_text07,
    select_debug_text08,
    select_debug_text09,
    select_debug_text10,
    select_debug_text11,
    select_debug_text12,
    select_debug_text13,
    select_debug_text14,
    select_debug_text15,
    select_debug_text16,
    select_debug_text17,
};

const char far com_status00[] = "SINGLE   ";
const char far com_status01[] = "PRIMARY  ";
const char far com_status02[] = "SECONDARY";
const char far com_status03[] = "NotFound!";

const char far * far com_status[] =
{
    com_status00,
    com_status01,
    com_status02,
    com_status03,
};

const char far SampleMasterMode[] = "Alpha->SampleMasterMode";
const char far OSReturnMain[] = "OS->Return.Main";
const char far OSReturnBOM[] = "OS->Return.BOM";
const char far SysIPmes[] = "Sys->ipmes()";
const char far SysDebug[] = "Sys->debug()";
const char far SysConsole[] = "Sys->console()";
const char far SysMemory[] = "Sys->memory()";
const char far Dummy[] = "Dummy";
const char far SysLogo[] = "Debug->Logo()";
const char far SysTitle[] = "Debug->Title()";
const char far SysMenu[] = "Debug->Menu()";
const char far SysMgame[] = "Debug->Mgame()";
const char far SysTuneup[] = "Debug->Tuneup()";
const char far SysUnitSelect[] = "Debug->UnitSelect()";
const char far SysStageSelect[] = "Debug->StageSelect()";
const char far SysStory[] = "Debug->Story()";
const char far SysEnding[] = "Debug->Ending()";

struct DebugHandler
{
    u16 unk;
    const char far * namestr;
    task_pointer func;
};

static const struct DebugHandler far DebugHandlers[] =
{
    { 0,  SampleMasterMode,     alpha_init          }, 
    { 0,  SysLogo,              logo_init           },
    { 0,  SysTitle,             title_init          },
    { 0,  SysMenu,              menu_init           },
    { 0,  SysMgame,             m_game_init         },
    { 0,  SysTuneup,            tuneup_init         },
    { 0,  SysUnitSelect,        unisel_init         },
    { 0,  SysStageSelect,       stage_select_init   },
    { 0,  SysStory,             story_init          },
    { 0,  SysEnding,            ending_init         },
    { 1,  OSReturnMain,         NULL                },
    { 1,  OSReturnMain,         NULL                },
    { 2,  OSReturnBOM,          NULL                },
    { 0,  SysIPmes,             ip_mes_test_init    },
    { 0,  SysDebug,             debug_init          },
    { 0,  SysConsole,           console_init        },
    { 0,  SysMemory,            memory_test_init    },
    { -1, Dummy,                NULL                },

    /**/
};

static void unk_829B9();
static void unk_82AB8();

void select_init()
{
	task_delete; //Force include
	task_append; //Force include
	task_append2; //Force include
	font_load; //Force include
	nbg_ddf; //Force include
	print; //Force include
	far_strcpy; //Force include
	serial_ver_info; //Force include
	hsprintf; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0100");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unk_8226E_");
	ASM_INLINE("MOV	BX,SEG unk_8226E_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,unk_826F3_");
	ASM_INLINE("MOV	BX,SEG unk_826F3_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append2_, SEG task_append2_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	DX,0xA000");
	ASM_INLINE("CALLF	font_load_, SEG font_load_");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,0x0001");
	ASM_INLINE("CALLF	nbg_ddf_, SEG nbg_ddf_");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_821A0");
ASM_INLINE("_8217C:");
	ASM_INLINE("XOR	DI,DI");
	ASM_INLINE("JMP	_8219A");
ASM_INLINE("_82180:");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,DI");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("MOV	DX,str0_");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	DI");
ASM_INLINE("_8219A:");
	ASM_INLINE("CMP	DI,0x001D");
	ASM_INLINE("JL	_82180");
	ASM_INLINE("INC	SI");
ASM_INLINE("_821A0:");
	ASM_INLINE("CMP	SI,0x0013");
	ASM_INLINE("JL	_8217C");
	ASM_INLINE("XOR	SI,SI");
	ASM_INLINE("JMP	_821E7");
ASM_INLINE("_821A9:");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,0xA0A1");
	ASM_INLINE("MOV	ES,CX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("MOV	CX,ES:[BX+0x0002].W");
	ASM_OP5(0x26,0x8B,0x8F,0x02,0x00);
	//ASM_INLINE("MOV	DX,ES:[BX+0x0004].W");
	ASM_OP5(0x26,0x8B,0x97,0x04,0x00);
	ASM_INLINE("POP	BX");
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,SI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	SI");
ASM_INLINE("_821E7:");
	ASM_INLINE("CMP	SI,0x0012");
	ASM_INLINE("JL	_821A9");
	ASM_INLINE("CALLF	serial_ver_info_, SEG serial_ver_info_");
	ASM_INLINE("MOV	BX,0x0064");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("DIV	BX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("CALLF	serial_ver_info_, SEG serial_ver_info_");
	ASM_INLINE("MOV	BX,0x0064");
	ASM_INLINE("XOR	DX,DX");
	ASM_INLINE("DIV	BX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,str1_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0008");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x0886].W");
	ASM_INLINE("MOV	AX,str2_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0019");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_8226E()
{
	sereq; //Force include
	ip_r; //Force include
	ip_w; //Force include
	task_delete2; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0116");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("PUSH	[0x0952].W");
	ASM_INLINE("MOV	AX,str3_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0002");
	ASM_INLINE("MOV	BX,0x000A");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x0956].W");
	ASM_INLINE("MOV	AX,str4_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("MOV	BX,0x000A");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x095A].W");
	ASM_INLINE("MOV	AX,str5_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x000A");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,0xA0A8");
	ASM_INLINE("MOV	ES,CX");
	ASM_INLINE("MOV	AL,[0x020C].B");
	ASM_INLINE("CBW");
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("SHL	BX,1");
	ASM_INLINE("SHL	BX,1");
	//ASM_INLINE("MOV	CX,ES:[BX+0x0002].W");
	ASM_OP5(0x26,0x8B,0x8F,0x02,0x00);
	//ASM_INLINE("MOV	DX,ES:[BX+0x0004].W");
	ASM_OP5(0x26,0x8B,0x97,0x04,0x00);
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0011");
	ASM_INLINE("MOV	BX,0x000A");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x0960].W");
	ASM_INLINE("MOV	AX,str6_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0002");
	ASM_INLINE("MOV	BX,0x000B");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x0964].W");
	ASM_INLINE("MOV	AX,str7_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0007");
	ASM_INLINE("MOV	BX,0x000B");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x0968].W");
	ASM_INLINE("MOV	AX,str8_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x000C");
	ASM_INLINE("MOV	BX,0x000B");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	AL,[0x020C].B");
	ASM_INLINE("CMP	AL,0x02");
	ASM_INLINE("JZ	_8242D");
	ASM_INLINE("CMP	AL,0x01");
	ASM_INLINE("JZ	_82411");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("MOV	CX,0xA0A8");
	ASM_INLINE("MOV	ES,CX");
	//ASM_INLINE("MOV	CX,ES:[0x000E].W");
	ASM_OP5(0x26,0x8B,0x0E,0x0E,0x00);
	//ASM_INLINE("MOV	DX,ES:[0x0010].W");
	ASM_OP5(0x26,0x8B,0x16,0x10,0x00);
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
	ASM_INLINE("JMP	_82447");
ASM_INLINE("_82411:");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("MOV	CX,0xA0A8");
	ASM_INLINE("MOV	ES,CX");
	//ASM_INLINE("MOV	CX,ES:[0x000A].W");
	ASM_OP5(0x26,0x8B,0x0E,0x0A,0x00);
	//ASM_INLINE("MOV	DX,ES:[0x000C].W");
	ASM_OP5(0x26,0x8B,0x16,0x0C,0x00);
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
	ASM_INLINE("JMP	_82447");
ASM_INLINE("_8242D:");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("MOV	CX,0xA0A8");
	ASM_INLINE("MOV	ES,CX");
	//ASM_INLINE("MOV	CX,ES:[0x0006].W");
	ASM_OP5(0x26,0x8B,0x0E,0x06,0x00);
	//ASM_INLINE("MOV	DX,ES:[0x0008].W");
	ASM_OP5(0x26,0x8B,0x16,0x08,0x00);
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
ASM_INLINE("_82447:");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0011");
	ASM_INLINE("MOV	BX,0x000B");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x1004].W");
	ASM_INLINE("MOV	AX,str9_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x1006].W");
	ASM_INLINE("MOV	AX,str10_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0005");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x1008].W");
	ASM_INLINE("MOV	AX,str11_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x100A].W");
	ASM_INLINE("MOV	AX,str12_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x000F");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[0x100C].W");
	ASM_INLINE("MOV	AX,str13_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0014");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("INC	[unkD76_].W");
	ASM_INLINE("MOV	AX,[unkD76_].W");
	ASM_INLINE("DEC	AX");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,str14_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0019");
	ASM_INLINE("MOV	BX,0x000E");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("LEA	DI,[BP-0x0116].B");
	ASM_INLINE("MOV	SI,select_stuff_");
	ASM_INLINE("MOV	CX,0x0016");
	ASM_INLINE("PUSH	DS");
	ASM_INLINE("POP	ES");
	ASM_INLINE("CLD");
	ASM_INLINE("REP MOVSB");
	ASM_INLINE("TEST	[0x095A].W,0x0100");
	ASM_INLINE("JZ	_825C5");
	ASM_INLINE("CMP	[0x018A].W,0x0000");
	ASM_INLINE("JLE	_825B7");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("JMP	_825B9");
ASM_INLINE("_825B7:");
	ASM_INLINE("XOR	AX,AX");
ASM_INLINE("_825B9:");
	ASM_INLINE("SUB	[0x018A].W,AX");
	ASM_INLINE("MOV	AX,[0x018A].W");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
ASM_INLINE("_825C5:");
	ASM_INLINE("TEST	[0x095A].W,0x0400");
	ASM_INLINE("JZ	_825E7");
	ASM_INLINE("CMP	[0x018A].W,0x0063");
	ASM_INLINE("JGE	_825D9");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("JMP	_825DB");
ASM_INLINE("_825D9:");
	ASM_INLINE("XOR	AX,AX");
ASM_INLINE("_825DB:");
	ASM_INLINE("ADD	[0x018A].W,AX");
	ASM_INLINE("MOV	AX,[0x018A].W");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
ASM_INLINE("_825E7:");
	ASM_INLINE("TEST	[0x095A].W,0xF000");
	ASM_INLINE("JZ	_8261F");
	ASM_INLINE("TEST	[0x095A].W,0x0004");
	ASM_INLINE("JZ	_82607");
	ASM_INLINE("MOV	AX,[0x018A].W");
	ASM_INLINE("MOV	[BP-0x0112].B,AL");
	ASM_INLINE("LEA	AX,[BP-0x0116].B");
	ASM_INLINE("CALLF	ip_w_, SEG ip_w_");
ASM_INLINE("_82607:");
	ASM_INLINE("TEST	[0x095A].W,0x0008");
	ASM_INLINE("JZ	_8263E");
	ASM_INLINE("MOV	[BP-0x0112].B,0x00");
	ASM_INLINE("LEA	AX,[BP-0x0116].B");
	ASM_INLINE("CALLF	ip_w_, SEG ip_w_");
	ASM_INLINE("JMP	_8263E");
ASM_INLINE("_8261F:");
	ASM_INLINE("TEST	[0x095A].W,0x0004");
	ASM_INLINE("JZ	_8262F");
	ASM_INLINE("MOV	AX,[0x018A].W");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
ASM_INLINE("_8262F:");
	ASM_INLINE("TEST	[0x095A].W,0x0008");
	ASM_INLINE("JZ	_8263E");
	ASM_INLINE("XOR	AL,AL");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
ASM_INLINE("_8263E:");
	ASM_INLINE("PUSH	[0x018A].W");
	ASM_INLINE("MOV	AX,str15_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("LEA	AX,[BP-0x0116].B");
	ASM_INLINE("CALLF	ip_r_, SEG ip_r_");
	ASM_INLINE("TEST	AX,AX");
	ASM_INLINE("JNZ	_826BA");
	ASM_INLINE("MOV	AL,[BP-0x0112].B");
	ASM_INLINE("CALLF	sereq_, SEG sereq_");
	ASM_INLINE("MOV	AL,[BP-0x0112].B");
	ASM_INLINE("XOR	AH,AH");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	AX,str16_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0005");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
ASM_INLINE("_826BA:");
	ASM_INLINE("TEST	[0x0956].W,0x0002");
	ASM_INLINE("JZ	_826EB");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unk_826F3_");
	ASM_INLINE("MOV	BX,SEG unk_826F3_");
	ASM_INLINE("CALLF	task_delete2_, SEG task_delete2_");
	ASM_INLINE("MOV	AX,unk_828B5_");
	ASM_INLINE("MOV	BX,SEG unk_828B5_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	[unkD76_].W,0x0000");
	ASM_INLINE("MOV	[unkD78_].W,0x0000");
ASM_INLINE("_826EB:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_826F3()
{
	if (unkD7A > 0x20)
	{
		unkD7A = 0;
		unkD7C = (unkD7C + 1) & 7;
		nbg_scroll(0, unkD7C, unkD7C);
	}
	unkD7A++;
}

static u16 unk_82720()
{
	s16 i;
	for (i = 0; DebugHandlers[i].unk != -1; i++)
	{
	}
	return i;
}

static void unk_82742(u16 a)
{
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0100");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("PUSH	SI");
	ASM_INLINE("PUSH	DI");
	ASM_INLINE("MOV	SI,AX");
	ASM_INLINE("MOV	DI,0x0001");
	ASM_INLINE("JMP	_827EF");
ASM_INLINE("_82755:");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("MOV	BX,SS");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	CX,0xA0BA");
	ASM_INLINE("MOV	ES,CX");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	CX,0x000A");
	ASM_INLINE("MUL	CX");
	ASM_INLINE("ADD	BX,AX");
	//ASM_INLINE("MOV	CX,ES:[BX+0x02].W");
	ASM_OP4(0x26,0x8B,0x4F,0x02);
	//ASM_INLINE("MOV	DX,ES:[BX+0x04].W");
	ASM_OP4(0x26,0x8B,0x57,0x04);
	ASM_INLINE("POP	BX");
	ASM_INLINE("POP	AX");
	ASM_INLINE("CALLF	far_strcpy_, SEG far_strcpy_");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("JMP	_827C1");
ASM_INLINE("_8279E:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	BX,0xA0BA");
	ASM_INLINE("MOV	ES,BX");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	CX,0x000A");
	ASM_INLINE("MUL	CX");
	ASM_INLINE("ADD	BX,AX");
	ASM_INLINE("LES	BX,ES:[BX+0x02]");
	ASM_INLINE("POP	AX");
	ASM_INLINE("MOV	CX,AX");
	ASM_INLINE("DEC	CX");
	ASM_INLINE("ADD	BX,CX");
	ASM_INLINE("CMP	ES:[BX].B,0x00");
	ASM_INLINE("JZ	_827E3");
	ASM_INLINE("INC	AX");
ASM_INLINE("_827C1:");
	ASM_INLINE("CMP	AX,0x001C");
	ASM_INLINE("JL	_8279E");
	ASM_INLINE("JMP	_827E3");
ASM_INLINE("_827C8:");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("MOV	CX,0x0000");
	ASM_INLINE("MOV	BX,0xA000");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("MOV	BX,DI");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("MOV	DX,str17_");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	AX");
	ASM_INLINE("INC	AX");
ASM_INLINE("_827E3:");
	ASM_INLINE("CMP	AX,0x001C");
	ASM_INLINE("JL	_827C8");
	ASM_INLINE("INC	DI");
	ASM_INLINE("INC	SI");
	ASM_INLINE("CMP	DI,0x0011");
	ASM_INLINE("JZ	_82808");
ASM_INLINE("_827EF:");
	ASM_INLINE("MOV	AX,0xA0BA");
	ASM_INLINE("MOV	ES,AX");
	ASM_INLINE("MOV	AX,SI");
	ASM_INLINE("MOV	BX,0x000A");
	ASM_INLINE("MUL	BX");
	ASM_INLINE("MOV	BX,AX");
	//ASM_INLINE("CMP	ES:[BX+0x0000].W,0xFFFF");
	ASM_OP6(0x26,0x83,0xBF,0x00,0x00,0xFF);
	ASM_INLINE("JZ	_82808");
	ASM_INLINE("JMP	_82755");
ASM_INLINE("_82808:");
	ASM_INLINE("POP	DI");
	ASM_INLINE("POP	SI");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_82810(u16 a, u16 b)
{
	if (a)
	{
		print(0, b + 1, 1, str18, DFONT_char_adr);
	}
	else
	{
		print(0, b + 1, 1, str19, DFONT_char_adr);
	}
}

static void unk_8284D(u16 idx)
{
	s16 i;
	
	switch(DebugHandlers[idx].unk)
	{
		case 0:
		{
			task_append(DebugHandlers[idx].func, 0);
			break;
		}
		case 1:
		{
			task_delete();
			task_append((task_pointer)select_init, 0);
			break;
		}
		default:
		{
			for (i = 0; i < 9; i++)
			{
				task_delete();
			}
			break;
		}
	}
}

static void unk_828B5()
{
	task_delete();
	task_append((task_pointer)unk_829B9, 0);
	cls(0);
	cls(1);
	font_load(1, DFONT_char_adr);
	nbg_ddf(0, 0);
	nbg_ddf(1, 1);
	unk_82742(unkD78);
	unk_82810(1, unkD76);
}

static void unk_82911()
{
	max; //Force include
	ASM_INLINE("PUSH	BP");
	ASM_INLINE("MOV	BP,SP");
	ASM_INLINE("SUB	SP,0x0100");
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("PUSH	DX");
	ASM_INLINE("MOV	BX,max_");
	ASM_INLINE("MOV	AX,SEG max_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,str20_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0008");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[unkD76_].W");
	ASM_INLINE("MOV	AX,str21_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x0008");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("PUSH	[unkD78_].W");
	ASM_INLINE("MOV	AX,str22_");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("LEA	AX,[BP-0x0100].B");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("CALLF	hsprintf_, SEG hsprintf_");
	ASM_INLINE("ADD	SP,0x0006");
	ASM_INLINE("MOV	BX,0x0000");
	ASM_INLINE("MOV	AX,0xA000");
	ASM_INLINE("PUSH	AX");
	ASM_INLINE("PUSH	BX");
	ASM_INLINE("MOV	AX,0x000A");
	ASM_INLINE("MOV	BX,0x0011");
	ASM_INLINE("MOV	CX,0x0001");
	ASM_INLINE("LEA	DX,[BP-0x0100].B");
	ASM_INLINE("CALLF	print_, SEG print_");
	ASM_INLINE("ADD	SP,0x0004");
	ASM_INLINE("POP	DX");
	ASM_INLINE("POP	CX");
	ASM_INLINE("MOV	SP,BP");
	ASM_INLINE("POP	BP");
}

static void unk_829B9()
{
	ASM_INLINE("PUSH	CX");
	ASM_INLINE("CALLF	unk_82720_, SEG unk_82720_");
	ASM_INLINE("MOV	CX,AX");
	ASM_INLINE("TEST	[0x095A].W,0x0100");
	ASM_INLINE("JZ	_82A17");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,[unkD76_].W");
	ASM_INLINE("CALLF	unk_82810_, SEG unk_82810_");
	ASM_INLINE("DEC	[unkD76_].W");
	ASM_INLINE("CMP	[unkD76_].W,0x0000");
	ASM_INLINE("JGE	_82A06");
	ASM_INLINE("MOV	[unkD76_].W,0x0000");
	ASM_INLINE("DEC	[unkD78_].W");
	ASM_INLINE("CMP	[unkD78_].W,0x0000");
	ASM_INLINE("JGE	_829FE");
	ASM_INLINE("MOV	[unkD76_].W,0x000F");
	ASM_INLINE("MOV	AX,CX");
	ASM_INLINE("SUB	AX,0x0010");
	ASM_INLINE("MOV	[unkD78_].W,AX");
ASM_INLINE("_829FE:");
	ASM_INLINE("MOV	AX,[unkD78_].W");
	ASM_INLINE("CALLF	unk_82742_, SEG unk_82742_");
ASM_INLINE("_82A06:");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,[unkD76_].W");
	ASM_INLINE("CALLF	unk_82810_, SEG unk_82810_");
	ASM_INLINE("CALLF	unk_82911_, SEG unk_82911_");
ASM_INLINE("_82A17:");
	ASM_INLINE("TEST	[0x095A].W,0x0400");
	ASM_INLINE("JZ	_82A6D");
	ASM_INLINE("XOR	AX,AX");
	ASM_INLINE("MOV	BX,[unkD76_].W");
	ASM_INLINE("CALLF	unk_82810_, SEG unk_82810_");
	ASM_INLINE("INC	[unkD76_].W");
	ASM_INLINE("CMP	[unkD76_].W,0x000F");
	ASM_INLINE("JLE	_82A5C");
	ASM_INLINE("MOV	[unkD76_].W,0x000F");
	ASM_INLINE("SUB	CX,0x0010");
	ASM_INLINE("INC	[unkD78_].W");
	ASM_INLINE("CMP	CX,[unkD78_].W");
	ASM_INLINE("JGE	_82A54");
	ASM_INLINE("MOV	[unkD76_].W,0x0000");
	ASM_INLINE("MOV	[unkD78_].W,0x0000");
ASM_INLINE("_82A54:");
	ASM_INLINE("MOV	AX,[unkD78_].W");
	ASM_INLINE("CALLF	unk_82742_, SEG unk_82742_");
ASM_INLINE("_82A5C:");
	ASM_INLINE("MOV	AX,0x0001");
	ASM_INLINE("MOV	BX,[unkD76_].W");
	ASM_INLINE("CALLF	unk_82810_, SEG unk_82810_");
	ASM_INLINE("CALLF	unk_82911_, SEG unk_82911_");
ASM_INLINE("_82A6D:");
	ASM_INLINE("TEST	[0x095A].W,0x0002");
	ASM_INLINE("JNZ	_82A7D");
	ASM_INLINE("TEST	[0x095A].W,0x0004");
	ASM_INLINE("JZ	_82A9B");
ASM_INLINE("_82A7D:");
	ASM_INLINE("CALLF	task_delete_, SEG task_delete_");
	ASM_INLINE("MOV	AX,unk_828B5_");
	ASM_INLINE("MOV	BX,SEG unk_828B5_");
	ASM_INLINE("XOR	CX,CX");
	ASM_INLINE("CALLF	task_append_, SEG task_append_");
	ASM_INLINE("MOV	AX,[unkD76_].W");
	ASM_INLINE("ADD	AX,[unkD78_].W");
	ASM_INLINE("CALLF	unk_8284D_, SEG unk_8284D_");
ASM_INLINE("_82A9B:");
	ASM_INLINE("POP	CX");
}

void alpha_init(u16 a)
{
    task_delete();
    task_append((task_pointer)unk_82AB8, 0);
    unkD7E = 2;
}

static void unk_82AB8()
{
	switch(unkD7E)
	{
		case 2:
		{
			task_append((task_pointer)logo_init, 0);
			break;
		}
		case 1:
		{
			task_append((task_pointer)title_init, 0);
			break;
		}
		case 0:
		{
			task_append((task_pointer)menu_init, 0);
			break;
		}
	}

	switch(unkD7E)
	{
		case 2:
		{
			unkD7E = 1;
			break;
		}
		case 1:
		{
			unkD7E = 0;
			break;
		}
		case 0:
		{
			unkD7E = 0;
			break;
		}
	}
}

