#include <machine.h>
#include "types.h"

void max()
{
	ASM_DB(0x3B);
	ASM_DB(0xC3);
	ASM_DB(0x7D);
	ASM_DB(0x02);
	ASM_DB(0x8B);
	ASM_DB(0xC3);
}

