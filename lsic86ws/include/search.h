/*
	search.h	search functions
*/

#ifndef	__SEARCH_H
#define	__SEARCH_H

#ifdef	ANSI
#error	<search.h> is not an ANSI header
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

void	*bsearch(const void *, const void *, size_t, size_t, int (*)());
void	qsort(void *, size_t, size_t, int (*)());

#endif
