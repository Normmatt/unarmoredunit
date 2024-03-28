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
	unsigned short unkE;	/*0960*/
	unsigned short unk10;	/*0962*/
	unsigned short unk12;	/*0964*/
	unsigned short unk14;	/*0966*/
	unsigned short unk16;	/*0968*/
	unsigned short unk18;	/*096A*/
	unsigned short unk1A;	/*096C*/
};
extern struct padState pad;

void pad_init();
void pad_task();
void get_pad();

#endif
