/*
	process.h	precess control functions
*/

#ifndef	__PROCESS_H
#define	__PROCESS_H

#ifdef	ANSI
#error	<process.h> is not an ANSI header
#endif

#define	P_WAIT		0
#define	P_OVERLAY	2

void	exit(int);
void	abort(void);

int	execl(const char *, ...);
int	execv(const char *, const char *const []);
int	spawnl(int, const char *, ...);
int	spawnv(int, const char *, const char *const []);
int	spawnlp(int, const char *, ...);
int	spawnvp(int, const char *, const char *const []);
#ifndef	CPM
int	execlp(const char *, ...);
int	execvp(const char *, const char *const []);
int	execle(const char *, ...);
int	execlpe(const char *, ...);
int	execve(const char *, const char *const [], const char *const []);
int	execvpe(const char *, const char *const [], const char *const []);
int	spawnle(int, const char *, ...);
int	spawnlpe(int, const char *, ...);
int	spawnve(int, const char *, const char *const [], const char *const []);
int	spawnvpe(int, const char *, const char *const [], const char *const[]);
#endif

int	getpid(void);
int	system(const char *);

#endif
