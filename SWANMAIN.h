
#ifndef SWANMAIN_H
#define SWANMAIN_H

#include "types.h"

extern u8 far DFONT_char_adr[];

void remain();
void task_default_task();
void task_default_task2();
s16 tsk_init();
s16 task_append(task_pointer task, short unk);
s16 task_call();
s16 task_call_param2();
s16 task_delete();
s16 task_delete_fade(u16 unk);
s16 task_delete_all();
s16 task_append2(task_pointer2 task, short unk);
s16 task_call2(u16 unk);
s16 task_delete2(task_pointer2 task);
s16 task_delete2_all();
void SWANmain();
void v_blank_int();

#endif
