/*
	signal.h
*/

#ifndef	__SIGNAL_H
#define	__SIGNAL_H

#ifndef	__SIG_ATOMIC_T_DEFINED
#define	__SIG_ATOMIC_T_DEFINED
typedef	int	sig_atomic_t;
#endif

#define	SIG_ERR		((void (*)())-1)
#define	SIG_DFL		((void (*)())0)
#define	SIG_IGN		((void (*)())1)

#define	SIGINT		2
#define	SIGILL		4
#define	SIGABRT		6
#define	SIGFPE		8
#define	SIGSEGV		11
#define	SIGTERM		15

#define	NSIG		16

void	(*signal(int, void (*)()))();
int	raise(int);

#endif
