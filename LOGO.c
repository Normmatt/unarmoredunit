
#include <machine.h>
#include "types.h"
#include "LOGO.h"
#include "MEMORY.h"
#include "SWANMAIN.h"
#include "SYSTEM.h"

void logo_init()
{
	ASM_DB(0x51);
	ASM_DB(0x52);
	ASM_DB(0x56);
	ASM_DB(0x8B);
	ASM_DB(0xD0);
	ASM_DB(0x9A);
	ASM_DB(0x74);
	ASM_DB(0x02);
	ASM_DB(0x0A);
	ASM_DB(0x80);
	ASM_DB(0xB8);
	ASM_DB(0x06);
	ASM_DB(0x00);
	ASM_DB(0x9A);
	ASM_DB(0x59);
	ASM_DB(0x00);
	ASM_DB(0x4D);
	ASM_DB(0x81);
	ASM_DB(0x8B);
	ASM_DB(0xF0);
	ASM_DB(0x85);
	ASM_DB(0xF6);
	ASM_DB(0x74);
	ASM_DB(0x54);
	ASM_DB(0xB8);
	ASM_DB(0x76);
	ASM_DB(0x00);
	ASM_DB(0xBB);
	ASM_DB(0x27);
	ASM_DB(0x84);
	ASM_DB(0x8B);
	ASM_DB(0xCE);
	ASM_DB(0x9A);
	ASM_DB(0xF7);
	ASM_DB(0x01);
	ASM_DB(0x0A);
	ASM_DB(0x80);
	ASM_DB(0x89);
	ASM_DB(0x14);
	ASM_DB(0xC7);
	ASM_DB(0x44);
	ASM_DB(0x02);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xC7);
	ASM_DB(0x44);
	ASM_DB(0x04);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xB8);
	ASM_DB(0x01);
	ASM_DB(0x00);
	ASM_DB(0xB9);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xBA);
	ASM_DB(0xD4);
	ASM_DB(0xA2);
	ASM_DB(0x9A);
	ASM_DB(0x0A);
	ASM_DB(0x00);
	ASM_DB(0x8E);
	ASM_DB(0x91);
	ASM_DB(0xB8);
	ASM_DB(0x01);
	ASM_DB(0x00);
	ASM_DB(0xB9);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xBA);
	ASM_DB(0xD4);
	ASM_DB(0xA2);
	ASM_DB(0x9A);
	ASM_DB(0xEE);
	ASM_DB(0x00);
	ASM_DB(0x8E);
	ASM_DB(0x91);
	ASM_DB(0x33);
	ASM_DB(0xC0);
	ASM_DB(0x9A);
	ASM_DB(0x70);
	ASM_DB(0x03);
	ASM_DB(0xEB);
	ASM_DB(0x80);
	ASM_DB(0xB8);
	ASM_DB(0x64);
	ASM_DB(0x00);
	ASM_DB(0x9A);
	ASM_DB(0x7F);
	ASM_DB(0x03);
	ASM_DB(0xEB);
	ASM_DB(0x80);
	ASM_DB(0x9A);
	ASM_DB(0x2E);
	ASM_DB(0x03);
	ASM_DB(0xEB);
	ASM_DB(0x80);
	ASM_DB(0xB8);
	ASM_DB(0x01);
	ASM_DB(0x00);
	ASM_DB(0xBB);
	ASM_DB(0x01);
	ASM_DB(0x00);
	ASM_DB(0x9A);
	ASM_DB(0x07);
	ASM_DB(0x00);
	ASM_DB(0xEB);
	ASM_DB(0x80);
	ASM_DB(0x5E);
	ASM_DB(0x5A);
	ASM_DB(0x59);
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


