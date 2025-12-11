#ifndef func_tbl_H
#define func_tbl_H

enum MAUWeapon
{
    WEAPON_MOVE,
    WEAPON_SONOR,
    WEAPON_SENSOR,
    WEAPON_RADAR,
    WEAPON_VULCAN,
    WEAPON_A_RIFLE,
    WEAPON_LASER,
    WEAPON_RAILGUN,
    WEAPON_H_GUN,
    WEAPON_BLAST,
    WEAPON_STUN_G,
    WEAPON_MISSILE,
    WEAPON_SPREAD,
    WEAPON_HEAVY_G,
    WEAPON_SPIRAL,
    WEAPON_WARP,
    WEAPON_BOOSTER,
    WEAPON_E_FIELD,
    WEAPON_JAMMER,
    WEAPON_FLASH,
    WEAPON_DECOY,
    WEAPON_PAINT,
    WEAPON_HUMMER,
    WEAPON_PHOTON,
    WEAPON_PHITHER,
    WEAPON_INVALID=-1,
};

enum MAUName
{
    NAME_SHUNER,
    NAME_WELG,
    NAME_ORNET,
    NAME_BEETZ,
    NAME_ROID,
    NAME_MONO,
    NAME_BLINK,
    NAME_CANAVIS,
    NAME_ORG,
    NAME_M_DOWN,
    NAME_GAZE,
    NAME_HYUMN,
    NAME_SOLID,
    NAME_MOLTH,
    NAME_DINGO,
    NAME_HOUND,
    NAME_GLID,
    NAME_APHEX,
    NAME_HOPER,
    NAME_CICADE,
    NAME_ROGUE,
    NAME_MUSHA,
    NAME_RENS,
    NAME_PSY_O,
    NAME_SILVER,
    NAME_ELVEN,
    NAME_ZERO,
    NAME_DEPT,
    NAME_CONFU,
    NAME_FLEA,
    NAME_TICK,
    NAME_RIKET,
    NAME_DIVA,
    NAME_GRIM,
    NAME_GOA,
    NAME_DIRIS,
    NAME_KEPTER,
    NAME_RENGS,
    NAME_VENOM,
    NAME_CASCADE,
    NAME_HYPNO,
    NAME_SIFER,
    NAME_UNKNOWN,
};

enum MAUType 
{
    TYPE_KNIGHT,
    TYPE_INSECT,
    TYPE_ROOK,
    TYPE_SEEKER,
    TYPE_RANGER,
    TYPE_PROTO,
    TYPE_UNK,
};

struct MAUData
{
    /* 00 */ s8 type;
    /* 01 */ u8 unk01;
    /* 02 */ u8 hp;
    /* 03 */ u8 en;
    /* 04 */ u8 tp;
    /* 05 */ s8 moves[8];
    /* 0D */ u8 unk0D;
    /* 0E */ u8 unk0E;
};

extern const u16 far functbl[][8];
extern const u16 far tuneup_table[][6];
extern const char far * far weapon_name[];
extern const struct MAUData far aulist[43];
extern const char far * far chara_name[];
extern const char far * far type_name[];
extern const u8 far stagelist[];
extern const u8 far stageadd[];

#endif
