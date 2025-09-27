
#include <machine.h>
#include <stdrom.h>
#include "types.h"
#include "DEBUG.h"
#include "SWANMAIN.h"
#include "SWAN_L_C.h"
#include "MEMORY.h"
#include "SYSTEM.h"
#include "SPRINTF.h"
#include "IP_MES.h"
#include "SOUND_CODE.h"
#include "PAD.h"

static void unk_83949();

static void near unk_83853()
{
	s16 i;
	s16 j;
	s16 tmp;
	u16 far *m = MK_FP(vram, map_tbl[1]);

	for(i = 0; i < 0x12; i++)
	{
		for(j = 0; j < 0x1C; j++)
		{
			m[(0x20 * i) + j] = m[(0x20 * (i+1)) + j];
		}
	}
}

void debug_init()
{
	s16 i;
	u16 val;
	struct DebugWork *work;
	char buf[256];

	task_delete();
	work = (struct DebugWork*)memalloc(sizeof (struct DebugWork));

	if(work)
	{
		task_append((task_pointer)unk_83949, (u16)work);
		font_load(1,DFONT_char_adr);
		nbg_ddf(1, 1);
		unk_83853();

		for(i = 0; i < 16; i++)
		{
			val = e2lib_i_read(0x30 + i);
			hsprintf(buf, 0x2d2, i, val);
			print(0, 0x11, 1, buf, DFONT_char_adr);
			unk_83853();
		}
	}

}

static void unk_83949(struct DebugWork* work)
{
	s16 i;
	u8 buf[] = {
		0x03, 0x00, 0xA8, 0xC0,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00
	};
	u16 *ptr = buf;

	if(ip_r(ptr) == 0)
	{
		sereq(13);
		print(0, 17, 1, ptr + 2, DFONT_char_adr);
		unk_83853();
	}

	if (pad[0].unk4 & 2)
	{
		for (i = 0; i < 18; i++)
		{
			unk_83853();
		}
		memfree(work);
		task_delete();
	}
}



 