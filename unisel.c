#include <machine.h>
#include "types.h"
#include "unisel.h"

static const char far str_01[] = " AU-NAME HP EN TP";
static const char far str_02[] = " No File -- -- --";
static const char far str_03[] = "  PLAY   DELETE  ";
static const char far str_04[] = "TYPE";
static const char far str_05[] = "NAME";
static const char far str_06[] = "STAGE";
static const char far str_07[] = "HP";
static const char far str_08[] = "ENG";
static const char far str_09[] = "TP";
static const char far str_10[] = "PLAYER    ";
static const char far str_11[] = "       CPU";
static const char far str_12[] = "PLAYER/CPU";
static const char far str_13[] = "SAVE FILE%1d";
static const char far str_14[] = "NEW GAME  ";
static const char far str_15[] = "          ";

static const char far * far str_all[] =
{
    str_10,
    str_10,
    str_11,
    str_12,
    str_13,
    str_14,
    str_15,
};

void unisel_init()
{
}

 