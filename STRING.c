
#include <machine.h>
#include "types.h"

void toupper()
{
	ASM_DB(0x8B);
	ASM_DB(0xD8);
	ASM_DB(0xF6);
	ASM_DB(0x87);
	ASM_DB(0x85);
	ASM_DB(0x07);
	ASM_DB(0x02);
	ASM_DB(0x74);
	ASM_DB(0x03);
	ASM_DB(0x83);
	ASM_DB(0xEB);
	ASM_DB(0x20);
	ASM_DB(0x8B);
	ASM_DB(0xC3);
}