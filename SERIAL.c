#include <machine.h>
#include "types.h"
#include "SERIAL.h"

u8 rcv_work[12];
u8 receive_buf[630];
u16 mother_child;

static void near unk_2BAC()
{
	ASM_DB(0x56);
	ASM_DB(0x8b);
	ASM_DB(0xf0);
	ASM_DB(0x8b);
	ASM_DB(0x1c);
	ASM_DB(0x03);
	ASM_DB(0x5c);
	ASM_DB(0x04);
	ASM_DB(0x81);
	ASM_DB(0xe3);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0x03);
	ASM_DB(0x5c);
	ASM_DB(0x0a);
	ASM_DB(0x8a);
	ASM_DB(0x07);
	ASM_DB(0xff);
	ASM_DB(0x44);
	ASM_DB(0x04);
	ASM_DB(0x32);
	ASM_DB(0xe4);
	ASM_DB(0x5e);
}

static void near unk_2BC4()
{
	ASM_DB(0x56);
	ASM_DB(0x8b);
	ASM_DB(0xf0);
	ASM_DB(0x8b);
	ASM_DB(0xde);
	ASM_DB(0x8b);
	ASM_DB(0x44);
	ASM_DB(0x04);
	ASM_DB(0x01);
	ASM_DB(0x07);
	ASM_DB(0x81);
	ASM_DB(0x24);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0xc7);
	ASM_DB(0x44);
	ASM_DB(0x04);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xff);
	ASM_DB(0x4c);
	ASM_DB(0x08);
	ASM_DB(0x5e);
}

static void near unk_2BDC()
{
	ASM_DB(0x51);
	ASM_DB(0x56);
	ASM_DB(0x57);
	ASM_DB(0x8b);
	ASM_DB(0xf8);
	ASM_DB(0x8b);
	ASM_DB(0x75);
	ASM_DB(0x02);
	ASM_DB(0x03);
	ASM_DB(0x75);
	ASM_DB(0x06);
	ASM_DB(0x83);
	ASM_DB(0x3d);
	ASM_DB(0x00);
	ASM_DB(0x74);
	ASM_DB(0x05);
	ASM_DB(0x8b);
	ASM_DB(0x0d);
	ASM_DB(0x49);
	ASM_DB(0xeb);
	ASM_DB(0x03);
	ASM_DB(0xb9);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0x8b);
	ASM_DB(0xc6);
	ASM_DB(0x25);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0x3b);
	ASM_DB(0xc1);
	ASM_DB(0x74);
	ASM_DB(0x10);
	ASM_DB(0x81);
	ASM_DB(0xe6);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0x03);
	ASM_DB(0x75);
	ASM_DB(0x0a);
	ASM_DB(0x88);
	ASM_DB(0x1c);
	ASM_DB(0xff);
	ASM_DB(0x45);
	ASM_DB(0x06);
	ASM_DB(0x33);
	ASM_DB(0xc0);
	ASM_DB(0xeb);
	ASM_DB(0x03);
	ASM_DB(0xb8);
	ASM_DB(0xff);
	ASM_DB(0xff);
	ASM_DB(0x5f);
	ASM_DB(0x5e);
	ASM_DB(0x59);
}

static void near unk_2C14()
{
	ASM_DB(0x56);
	ASM_DB(0x8b);
	ASM_DB(0xf0);
	ASM_DB(0x8b);
	ASM_DB(0xde);
	ASM_DB(0x8b);
	ASM_DB(0x44);
	ASM_DB(0x06);
	ASM_DB(0x01);
	ASM_DB(0x47);
	ASM_DB(0x02);
	ASM_DB(0x81);
	ASM_DB(0x64);
	ASM_DB(0x02);
	ASM_DB(0xff);
	ASM_DB(0x00);
	ASM_DB(0xc7);
	ASM_DB(0x44);
	ASM_DB(0x06);
	ASM_DB(0x00);
	ASM_DB(0x00);
	ASM_DB(0xff);
	ASM_DB(0x44);
	ASM_DB(0x08);
	ASM_DB(0x5e);
}

void serial_init()
{
}

void serial_receive()
{
}

void serial_in()
{
}

void serial_out_sub()
{
}

void serial_out()
{
}

void serial_ver_info()
{
}

void serial_exist()
{
}

s16 serial_in_frag()
{
}

