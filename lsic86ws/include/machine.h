/*
 *	machine.h - machine dependent functions
 */

#ifndef	__MACHINE_H
#define	__MACHINE_H

#ifdef	ANSI
#error	<machine.h> is not an ANSI header
#endif

/*    inline functions    */

char	_asm_c();
unsigned _asm_i();
#define	_qq_(s)	#s
#define	_q_(s)	_qq_(s)

#define	inp(p)	\
	_asm_c("\n\tIN\tAL,DX", _asm_c, _asm_c, _asm_c, (unsigned)(p))
#define	outp(p, c)	\
	_asm_c("\n\tOUT\tDX,AL", (char)(c), _asm_c, _asm_c, (unsigned)(p))
#define	inpw(p)	\
	_asm_i("\n\tIN\tAX,DX", _asm_c, _asm_c, _asm_c, (unsigned)(p))
#define	outpw(p, c)	\
	_asm_i("\n\tOUT\tDX,AX", (unsigned)(c), _asm_c, _asm_c, (unsigned)(p))
#define	inp8(p)		_asm_c("\n\tIN\tAL," _q_(__eval__(p)))
#define	outp8(p, c)	_asm_c("\n\tOUT\t" _q_(__eval__(p)) ",AL", (char)(c))
#define	inp8w(p)	_asm_i("\n\tIN\tAX," _q_(__eval__(p)))
#define	outp8w(p, c) _asm_i("\n\tOUT\t" _q_(__eval__(p)) ",AX", (unsigned)(c))

#define	di()		_asm_c("\n\tCLI")
#define	ei()		_asm_c("\n\tSTI")

#endif
