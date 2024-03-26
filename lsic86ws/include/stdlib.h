/*
	stdlib.h - general utilities
*/

#ifndef	__STDLIB_H
#define	__STDLIB_H

#ifndef	ANSI
#include <stddef.h>	/* for compatibility to older version */
#endif	/* ANSI */

#ifndef	__SIZE_T_DEFINED
#define	__SIZE_T_DEFINED
typedef	unsigned size_t;
#endif

#ifndef	ANSI
extern	char	*sys_errlist[];
extern	int	sys_nerr;
extern char	_osmajor;
extern char	_osminor;
#endif

#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

void	*calloc(size_t, size_t);
void	*malloc(size_t);
void	*realloc(void *, size_t);
void	free(void *);
#ifndef	ANSI
void	*sbrk(size_t);
#endif	/* ANSI */

void	abort(void);
void	exit(int);

int	atexit(void (*)(void));
#ifndef	ANSI
#ifndef	__ONEXIT_T_DEFINED
#define	__ONEXIT_T_DEFINED
typedef	void	(*onexit_t)(void);
#endif
onexit_t onexit(onexit_t);
extern	char	**environ;
int	putenv(const char *);
#include <process.h>
#endif	/* ANSI */

char	*getenv(const char *);
int	system(const char *);

#ifndef	__STDROM_H

int		atoi(const char *);
long		atol(const char *);
double		atof(const char *);
#ifndef	ANSI
long double	atold(const char *);
#endif	/* ANSI */

long int	strtol(const char *, char **, int);
unsigned long	strtoul(const char *, char **, int);
double		strtod(const char *, char **);

#ifndef	ANSI
long double	strtold(const char *, char **);
char		*gcvt(double, int, char *);
char		*fcvt(double, int, int *, int *);
char		*ecvt(double, int, int *, int *);
char		*itoa(int, char *, int);
char		*ltoa(long, char *, int);
char		*ultoa(unsigned long, char *, int);
#endif	/* ANSI */


#define	RAND_MAX	32767
int	rand(void);
void	srand(unsigned int);

#ifdef	ANSI
void	*bsearch(const void *, const void *, size_t, size_t,
		int (*)(const void *, const void *));
void	qsort(void *, size_t, size_t, int (*)(const void *, const void *));
#else	/* ANSI */
void	*bsearch(const void *, const void *, size_t, size_t, int (*)());
void	qsort(void *, size_t, size_t, int (*)());
#endif	/* ANSI */

int	abs(int);
long int labs(long int);

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

#ifndef	ANSI
unsigned _asm_uuc(char *, unsigned, unsigned (*)(), char);
#define	_rotl(v, c)	_asm_uuc("\n\trol\tax,cl\n", (v), _asm_uuc, (c))
#define	_rotr(v, c)	_asm_uuc("\n\tror\tax,cl\n", (v), _asm_uuc, (c))

unsigned long	_lrotl(unsigned long, int);
unsigned long	_lrotr(unsigned long, int);

int	min(int, int);
int	max(int, int);
void	swab(const char *, char *, int);
#endif	/* ANSI */

#endif	/* __STDROM_H */

#endif	/* __STDLIB_H */
