#include <machine.h>
#include "types.h"
#include "unisel.h"

static const char far str_uni_01[] = " AU-NAME HP EN TP";
static const char far str_uni_02[] = " No File -- -- --";
static const char far str_uni_03[] = "  PLAY   DELETE  ";
static const char far str_uni_04[] = "TYPE";
static const char far str_uni_05[] = "NAME";
static const char far str_uni_06[] = "STAGE";
static const char far str_uni_07[] = "HP";
static const char far str_uni_08[] = "ENG";
static const char far str_uni_09[] = "TP";
static const char far str_uni_10[] = "PLAYER    ";
static const char far str_uni_11[] = "       CPU";
static const char far str_uni_12[] = "PLAYER/CPU";
static const char far str_uni_13[] = "SAVE FILE%1d";
static const char far str_uni_14[] = "NEW GAME  ";
static const char far str_uni_15[] = "          ";

static const char far * far str_uni_all[] =
{
    str_uni_10,
    str_uni_10,
    str_uni_11,
    str_uni_12,
    str_uni_13,
    str_uni_14,
    str_uni_15,
};

void unisel_init()
{
}

 