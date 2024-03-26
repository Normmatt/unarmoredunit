/*
	conio.h		console I/O
*/

#ifndef	__CONIO_H
#define	__CONIO_H

#ifdef	ANSI
#error	<conio.h> is not an ANSI header
#endif

int	kbhit(void);
char	getch(void);
char	getche(void);
char	putch(char);
int	ungetch(char);
void	cputs(const char *);
char	*cgets(char *);
void	sensebrk(void);
int	cprintf(const char *, ...);
int	cscanf(const char *, ...);
#include <machine.h>

#endif
