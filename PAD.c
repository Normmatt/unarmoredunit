#include <machine.h>
#include "types.h"
#include "PAD.h"
#include "SWAN_L_C.h"
#include "MEMORY.h"
#include "SWANMAIN.h"
#include "IP_MES.h"

struct padState pad[2];

/*static u8 pad_data[] = {
	0x00, 0x00, 0xA8, 0xC0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x02, 0x00
};*/

void pad_init()
{
	pad[0].unkC = 0;
	pad[0].unkA = 0;
	pad[0].unk8 = 0;
	pad[0].unk6 = 0;
	pad[0].unk4 = 0;
	pad[0].unk2 = 0;
	pad[0].unk0 = 0;
	pad[1].unkC = 0;
	pad[1].unkA = 0;
	pad[1].unk8 = 0;
	pad[1].unk6 = 0;
	pad[1].unk4 = 0;
	pad[1].unk2 = 0;
	pad[1].unk0 = 0;
}

void pad_task()
{
	//00FA
	u8 pad_data[] = {
		0x00, 0x00, 0xA8, 0xC0,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x02, 0x00
	};
	struct padState *p = &pad[0];
	s16 i;
	u16 val;

	p->unk0 = pad_in();

	if((pad[0].unk0 & 4) && (pad[0].unk0 & 8) && (pad[0].unk0 & 2))
	{
		meminit();
		pad_init();
		tsk_init();
		remain();
	}

	if(pad[0].unk0 != pad[0].unk2)
	{
		pad_data[4] = (pad[0].unk0 >> 8) & 0xFF;
		pad_data[5] = pad[0].unk0 & 0xFF;
		ip_w(pad_data);
	}

	if(!ip_r(pad_data))
	{
		pad[1].unk2 = pad_data[4] << 8 | pad_data[5];
	}

	pad[1].unk0 = pad[1].unk2;

	for(i = 0; i < 2; i++, p++)
	{
		val = ‾p->unk2 & p->unk0;
		p->unk6 = val;
		p->unk4 = val;
		if(p->unk4)
		{
			p->unk8 = p->unk0;
			p->unkA = 0;
			p->unkC = 3;
		}
		else
		{
			p->unk8 = 0;
			if(p->unkA > 9)
			{
				p->unkC++;
				if(p->unkC > 3)
				{
					p->unkC = 0;
					p->unk8 = p->unk0;
				}
			}
			else
			{
				p->unkA++;
			}
		}
		p->unk2 = p->unk0;
	}
}

u16 get_pad(u16 a, s16 b)
{
	do
	{
		pad_task();
	} while (!pad[a].unk8 && b);
	
	return pad[a].unk8;

}

