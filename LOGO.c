
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
	struct LogoWork *work;

	task_delete();
	work = (struct LogoWork *)memalloc(sizeof (struct LogoWork));
	if (work != NULL)
	{
		task_append((task_pointer)unk_842E6, (u16)work);
		work->unk0 = a;
		work->unk2 = 0;
		work->unk4 = 0;
		font_load(1, SAMMYL_char_adr);
		font_put(1, SAMMYL_char_adr);
		fade_tone(0);
		fade_out(100);
		fade_run();
		nbg_ddf(1, 1);
	}
}

static void unk_842E6(struct LogoWork *a)
{
	struct LogoWork *b = a;
	switch(a->unk2)
	{
		case 0:
		{
			if(0x1e < ++b->unk4)
			{
				b->unk2++;
				fade_in(10);
			}
			break;
		}
		case 1:
		{
			if (fade[0] == 100)
			{
				b->unk2++;
			}
			break;
		}
		case 2:
		{
			if (0x3c < ++b->unk4)
			{
				b->unk2++;
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


