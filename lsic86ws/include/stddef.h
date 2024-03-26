/*
	stddef.h	standard common definitions
*/

#ifndef	__STDDEF_H
#define	__STDDEF_H

#ifndef	__PTRDIFF_T_DEFINED
#define	__PTRDIFF_T_DEFINED
typedef	int	ptrdiff_t;
#endif

#ifndef	__SIZE_T_DEFINED
#define	__SIZE_T_DEFINED
typedef	unsigned size_t;
#endif

#ifndef	NULL
#if	defined(_D_FAR)
#define	NULL	(0L)
#else
#define	NULL	(0)
#endif
#endif

#define	offsetof(type, mem)	((size_t)&((type *)0)->mem)

extern	int	errno;

#endif
