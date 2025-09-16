
#include <machine.h>
#include "types.h"

void toupper()
{
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("TEST	[BX+0x0785].B,0x02");
	ASM_INLINE("JZ	_9213A");
	ASM_INLINE("SUB	BX,0x0020");
ASM_INLINE("_9213A:");
	ASM_INLINE("MOV	AX,BX");
}