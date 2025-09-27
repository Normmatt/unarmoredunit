#ifndef IP_MES_H
#define IP_MES_H

#include "types.h"

struct IpMesWork
{
    /* 00 */ u16 unk0;
}; //Total 2 bytes

s16 ip_init();
s16 ip_r(u16 *ptr);
void ip_w();
void ip_clear();
void ip_mes_test_init();

#endif
