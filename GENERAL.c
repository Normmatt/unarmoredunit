#include <machine.h>
#include "types.h"

int max(s16 a, s16 b)
{
	if(b > a)
	{
		a = b;
	}
	return a;
}

