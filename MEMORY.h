
#ifndef MEMORY_H
#define MEMORY_H

extern unsigned char memory_alloc_work[1042];

void meminit();
void memalloc();
void memfree();
void memory_test_init();
void memory_dump_init();

#endif
