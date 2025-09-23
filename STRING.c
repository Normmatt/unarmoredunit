
#include <machine.h>
#include <ctype.h>
#include "types.h"

//This is actually toupper.obj from doslib.lib
int toupper()
{
	_ctype;
	ASM_INLINE("MOV	BX,AX");
	ASM_INLINE("TEST	[BX+_ctype_+1].B,0x02");
	ASM_INLINE("JZ	_9213A");
	ASM_INLINE("SUB	BX,0x0020");
ASM_INLINE("_9213A:");
	ASM_INLINE("MOV	AX,BX");
}