/*
	io.h		non-ANSI I/O functions
*/

#ifndef	__IO_H
#define	__IO_H

#ifdef	ANSI
#error	<io.h> is not an ANSI header
#endif

#ifdef	CPM
int	creat(const char *);
int	open(const char *, int);
#else
int	creat(const char *, int);
int	open(const char *, int, ...);
#endif
long	lseek(int, long, int);
long	tell(int);
int	read(int, void *, int);
int	write(int, const void *, int);
int	close(int);
int	isatty(int);
int	dup(int);
int	dup2(int, int);
long	filelength(int);
int	unlink(const char *);
int	remove(const char *);
int	rename(const char *, const char *);
int	access(const char *, int);
int	chmod(const char *, int);
#ifndef	CPM
int	truncate(const char *, long);
int	ftruncate(int, long);
int	chsize(int, long);
int	eof(int);
int	umask(int);
char	*mktemp(char *);
#ifndef	__TIME_T_DEFINED
#define	__TIME_T_DEFINED
typedef	long	time_t;
#endif
int	utime(const char *, const time_t [2]);
int	gftime(const char *, time_t [2]);

#endif	/* CPM */
#include <direct.h>	/* for compatibility to older version */
#endif	/* __IO_H */
