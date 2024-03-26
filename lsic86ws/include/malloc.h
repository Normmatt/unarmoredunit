/*
	malloc.h	memory allocation
*/

#ifndef	__MALLOC_H
#define	__MALLOC_H

#ifdef	ANSI
#error	<malloc.h> is not an ANSI header
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


void	*calloc(size_t, size_t);
void	*malloc(size_t);
void	*realloc(void *, size_t);
void	free(void *);

void	*sbrk(size_t);

size_t	stackavail(void);

#endif
