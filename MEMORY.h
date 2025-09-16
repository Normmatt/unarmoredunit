
#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

typedef struct memory_node {
    struct memory_node * unk0;
    struct memory_node * unk2;
    u16 unk4;
    u16 unk6;
} memory_node_t;

typedef struct memory_test {
    u16 unk0; /* 0D6E */
    u16 unk2; /* 0D70 */
    u16 unk4; /* 0D72 */
    u16 unk6; /* 0D74 */
    u16 unk8; /* 0D76 */
    u16 unkA; /* 0D78 */
    u16 unkC; /* 0D7A */
    u16 unkE; /* 0D7C */
    u16 unk10; /* 0D7E */
} memory_test_t;

#define MEMORY_FLAG_FF41 0xFF41
#define MEMORY_FLAG_FF42 0xFF42
#define MEMORY_FLAG_FF46 0xFF46
#define MEMORY_FLAG_FF55 0xFF55

extern memory_node_t memory_alloc_work[128];

void meminit();
void *memalloc(u16 size);
void memfree();
void memory_test_init();
void memory_dump_init();

#endif
