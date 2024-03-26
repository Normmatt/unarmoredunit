/*
	memory.h	memory handlers
*/

#ifndef	__MEMORY_H
#define	__MEMORY_H

#ifdef	ANSI
#error	<memory.h> is not an ANSI header
#endif

#ifndef	NULL
#if	defined(_D_FAR)
#define	NULL	(0L)
#else
#define	NULL	(0)
#endif
#endif

#ifndef	__SIZE_T_DEFINED
#define	__SIZE_T_DEFINED
typedef	unsigned size_t;
#endif

void	*memcpy(void *, const void *, size_t);
void	*memmove(void *, const void *, size_t);
void	*memset(void *, char, size_t);
int	memcmp(const void *, const void *, size_t);
void	*memchr(const void *, char, size_t);
void	*memccpy(void *, const void *, char, size_t);
int	memicmp(const void *, const void *, size_t);
void	movedata(unsigned, unsigned, unsigned, unsigned, size_t);

#define	movmem(src, dst, len)	memcpy((dst), (src), (len))
#define	setmem(dst, len, dat)	memset((dst), (dat), (len))

#endif
