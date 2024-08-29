
#include <machine.h>
#include "types.h"
#include "LOGO.h"
#include "MEMORY.h"
#include "SWANMAIN.h"
#include "SWAN_L_C.h"
#include "SYSTEM.h"

extern u8 far SAMMYL_char_adr[];

void logo_init(u16 a)
{
	struct logo_struct *puVar1;

	task_delete();
	puVar1 = (struct logo_struct *)memalloc(6);
	if (puVar1 != NULL)
	{
		task_append((task_pointer)unk_842E6,(u16)puVar1);
		puVar1->field0_0x0 = a;
		puVar1->field1_0x2 = 0;
		puVar1->field2_0x4 = 0;
		font_load(1,SAMMYL_char_adr);
		font_put(1,SAMMYL_char_adr);
		fade_tone(0);
		fade_out(100);
		fade_run();
		nbg_ddf(1,1);
	}
}

static void unk_842E6(struct logo_struct *a)
{
	struct logo_struct *b = a;
	switch(a->field1_0x2)
	{
		case 0:
		{
			if(0x1e < ++b->field2_0x4)
			{
				b->field1_0x2++;
				fade_in(10);
			}
			break;
		}
		case 1:
		{
			if (fade[0] == 100)
			{
				b->field1_0x2++;
			}
			break;
		}
		case 2:
		{
			if (0x3c < ++b->field2_0x4)
			{
				b->field1_0x2++;
				fade_out(10);
			}
			break;
		}
		case 3:
		{
			if (fade[0] == 0)
			{
				task_delete();
				memfree(b);
			}
			break;
		}
	}
}


