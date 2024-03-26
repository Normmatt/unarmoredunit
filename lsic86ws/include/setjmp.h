/*
	setjmp.h - header non-local jumps
*/

#ifndef	__SETJMP_H
#define	__SETJMP_H

#ifndef	__JMP_BUF_DEFINED
#define	__JMP_BUF_DEFINED
typedef	int	jmp_buf[8];
#endif

int	setjmp(jmp_buf);
void	longjmp(jmp_buf, int);

#endif
