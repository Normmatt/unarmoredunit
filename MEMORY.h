
#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

typedef struct memory_node {
    struct memory_node * unk0;
    struct memory_node * unk2;
    u16 unk4;
    u16 unk6;
} memory_node_t;

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
