#ifndef PAD_H
#define PAD_H

struct padState
{
	unsigned short unk0;	/*0952*/
	unsigned short unk2;	/*0954*/
	unsigned short unk4;	/*0956*/
	unsigned short unk6;	/*0958*/
	unsigned short unk8;	/*095A*/
	unsigned short unkA;	/*095C*/
	unsigned short unkC;	/*095E*/
};
extern struct padState pad[2];

void pad_init();
void pad_task();
u16 get_pad(u16 a, s16 b);

#endif
