/*
	direct.h	directory handlers
*/

#ifndef	__DIRECT_H
#define	__DIRECT_H

#ifdef	ANSI
#error	<direct.h> is not an ANSI header
#endif

char	*getcwd(char *, int);
int	mkdir(const char *);
int	rmdir(const char *);
int	chdir(const char *);

#endif
