/*
	stdrom.h - standard ROMable functions
*/

#ifndef	__STDROM_H
#define	__STDROM_H

#ifdef	ANSI
#error	<stdrom.h> is not an ANSI header
#endif

#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <setjmp.h>
#include <stdarg.h>
#include <machine.h>
#include <farstr.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <jctype.h>
#include <jstring.h>
#include <errno.h>


/*    excerpt from stdlib.h    */
long		atol(const char *);
int		atoi(const char *);
double		atof(const char *);
long double	atold(const char *);
long int	strtol(const char *, char **, int);
unsigned long	strtoul(const char *, char **, int);
double		strtod(const char *, char **);
long double	strtold(const char *, char **);
char		*gcvt(double, int, char *);
char		*fcvt(double, int, int *, int *);
char		*ecvt(double, int, int *, int *);
char		*itoa(int, char *, int);
char		*ltoa(long, char *, int);
char		*ultoa(unsigned long, char *, int);

#define	RAND_MAX	32767
int	rand(void);
void	srand(unsigned int);
void	*bsearch(const void *, const void *, size_t, size_t, int (*)());
void	qsort(void *, size_t, size_t, int (*)());
int	min(int, int);
int	max(int, int);
int	abs(int);
long int	labs(long int);

#ifndef	__DIV_T_DEFINED
#define	__DIV_T_DEFINED
typedef	struct	{
	int	quot;
	int	rem;
}	div_t;

typedef	struct	{
	long	quot;
	long	rem;
}	ldiv_t;
#endif

div_t	div(int, int);
ldiv_t	ldiv(long, long);

unsigned _asm_uuc(char *, unsigned, unsigned (*)(), char);
#define	_rotl(v, c)	_asm_uuc("\n\trol\tax,cl\n", (v), _asm_uuc, (c))
#define	_rotr(v, c)	_asm_uuc("\n\tror\tax,cl\n", (v), _asm_uuc, (c))

unsigned long	_lrotl(unsigned long, int);
unsigned long	_lrotr(unsigned long, int);

void	swab(const char *, char *, int);


/*    excerpt from dos.h    */
#define	FP_SEG(p)	((unsigned)((unsigned long)((void far *)(p)) >> 16))
#define	FP_OFF(p)	(unsigned)(p)
#define	MK_FP(s, o)	((void far*)(((unsigned long)(s) << 16)|(unsigned)(o)))

#ifndef	__REGS_DEFINED
#define	__REGS_DEFINED
union REGS	{
	struct XREGS	{
		unsigned short	ax, bx, cx, dx, si, di, bp, ds, es, flags, cflag;
	}	x;
	struct HREGS	{
		unsigned char	al, ah, bl, bh, cl, ch, dl, dh;
	}	h;
};

struct SREGS	{
	unsigned short	es, cs, ss, ds;
};
#endif
void	segread(struct SREGS *);
int	int86(int, union REGS *, union REGS *);
int	int86y(int, union REGS *, union REGS *);
int	int86x(int, union REGS *, union REGS *, struct SREGS *);


/* printf/scanf for ROM programs */

int	sprintf(char *, const char *, ...);
int	sscanf(const char *, const char *, ...);
int	xprintf(int (*)(char), const char *, ...);
int	xscanf(int (*)(char), const char *, ...);

#endif	/* __STDROM_H */
