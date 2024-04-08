
#include <machine.h>
#include "types.h"
#include "SOUND_CODE.h"
#include "SWANMAIN.h"
#include "SPRINTF.h"
#include "SYSTEM.h"
#include "PAD.h"
#include "select.h"
#include "flash.h"
#include "memory.h"
#include "SERIAL.h"
#include "IP_MES.h"
#include "SWAN_L_C.h"

void remain()
{
	nbg_ddf(0,0);
	nbg_ddf(1,0);
	spr_ddf(0);
	cls(0);
	cls(1);
	spr_cls();
	nbg_scroll(0,0,0);
	nbg_scroll(1,0,0);
	fade_in(100);
	bgmreq(0);
	sereq(0);
	SetPalette(0,7,5,3,0);
	SetPalette(1,7,6,5,4);
	SetPalette(2,5,4,3,2);
	SetPalette(3,3,2,1,0);
}

void task_default_task(u16 unk)
{
	task_delete();
	task_append(task_default_task2,0);
	font_load(1,DFONT_char_adr);
	nbg_ddf(1,1);
	print(0,0,1,10,DFONT_char_adr);
	print(0,1,1,0x18,DFONT_char_adr);
	print(0,2,1,0x2c,DFONT_char_adr);
	print(0,3,1,0x46,DFONT_char_adr);
}

void task_default_task2(u16 unk)
{
	if(!(pad.unk0 & 4)) return;
	if(!(pad.unk0 & 8)) return;
	if(!(pad.unk4 & 2)) return;
	
	meminit();
	pad_init();
	tsk_init();
	remain();
}

s16 tsk_init()
{
	s16 i;

	for(i = 0; i < 16; i++)
	{
		tsk1cont.unk2[i] = NULL;
		tsk1cont.unk42[i] = NULL;
		tsk1cont.unk82[i] = NULL;
		tsk1cont.unkA2[i] = NULL;
	}

	tsk1cont.unk2[0] = alpha_init;
	tsk1cont.unk2[1] = flash_init;
	tsk1cont.unk0 = 2;
	return 0;
}

s16 task_append(task_pointer task, short unk)
{
	if(tsk1cont.unk0 < 16)
	{
		tsk1cont.unk2[tsk1cont.unk0] = task;
		tsk1cont.unk82[tsk1cont.unk0] = unk;
		tsk1cont.unk0++;
		return 0;
	}
	return -1;
}

s16 task_call()
{
	if(tsk1cont.unk0 < 1)
	{
		return -1;
	}
	tsk1cont.unk2[tsk1cont.unk0](tsk1cont.unk82[tsk1cont.unk0]);
	return 0;
}

s16 task_call_param2()
{
	if(tsk1cont.unk0 < 1)
	{
		return 0;
	}
	return tsk1cont.unk82[tsk1cont.unk0];
}

s16 task_delete()
{
	if(tsk1cont.unk0 > 1)
	{
		tsk1cont.unk0--;
		return 0;
	}
	else 
	{
		tsk1cont.unk0 = 0;
		task_append(task_default_task,0);
		return -1;
	}
}

static void task_delete_fade_unk(u16 unk)
{
	if (fade[1] == 0)
	{
		task_delete();
		bgmreq(0);
	}
}

s16 task_delete_fade(u16 unk)
{
	task_append(task_delete_fade_unk,0);
	fade_out(unk);
	return 0;
}

s16 task_delete_all()
{
	tsk1cont.unk0 = 0;
	task_append(task_default_task,0);
	return 0;
}

s16 task_append2(task_pointer2 task, short unk)
{
	s16 val = 0;
	while (val < 16)
	{
		if (tsk1cont.unk42[val] == 0)
		{
			tsk1cont.unk42[val] = task;
			tsk1cont.unkA2[val] = unk;
			return 0;
		}
		val++;
	}
	return -1;
}

s16 task_call2(u16 unk)
{
	if(tsk1cont.unk42[unk] == NULL)
	{
		return -1;
	}
	tsk1cont.unk42[unk](unk, tsk1cont.unkA2[unk]);
	return 0;
}

s16 task_delete2(task_pointer2 task)
{
	s16 val = 0;
	while (val < 16)
	{
		if (tsk1cont.unk42[val] == task)
		{
			tsk1cont.unk42[val] = NULL;
			tsk1cont.unkA2[val] = 0;
			return 0;
		}
		val++;
	}
	return -1;
}

s16 task_delete2_all()
{
	s16 i;

	for(i=0; i<16; i++)
	{
		tsk1cont.unk42[i] = NULL;
		tsk1cont.unkA2[i] = 0;
	}
	return 0;
}

static void unk0494()
{
	tsk1cont.unkC2 = ~v_blank_cnt_count;
}

static void unk049D()
{
	while(tsk1cont.unkC2 == v_blank_cnt_count);
	tsk1cont.unkC2 = v_blank_cnt_count;
}

void SWANmain()
{
	s16 val;

	init_system();
	meminit();
	pad_init();
	tsk_init();
	remain();
	ei();
	unk0494();
	do
	{
		unk049D();
		lcd_option_1(0);
		lcd_option_2(0);
		lcd_option_3(0);
		val = serial_in_frag();
		if (val != 0) {
			lcd_option_2(1);
		}
		pad_task();
		val = task_call();
		if (val != 0) {
			task_delete_all();
			task_delete2_all();
		}
		for (val = 0; val < 16; val++)
		{
			task_call2(val);
		}
		rand();
		fade_run();
	} while( 1 );
}

void v_blank_int()
{
	serial_exist();
}
