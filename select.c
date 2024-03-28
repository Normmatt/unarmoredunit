#include <machine.h>
#include "types.h"

#include "ASM.h"
#include "CONSOLE.h"
#include "DEBUG.h"
#include "ending.h"
#include "flash.h"
#include "GENERAL.h"
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
#include "GENERAL.h"
#include "SPRINTF.h"
#include "stagesel.h"
#include "story.h"
#include "STRING.h"
#include "SYSTEM.h"
#include "TITLE.h"
#include "tuneup.h"
#include "unisel.h"

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

const char far * far select_debug_textall[] =
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
    void_pointer func;
};

const struct DebugHandler far DebugHandlers[] =
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

void select_init()
{
}

void alpha_init(u16 a)
{
}

