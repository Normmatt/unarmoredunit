/*
	stdarg.h  -  header for variable arguments

	26-Mar-86
*/

#ifndef	__STDARG_H
#define	__STDARG_H

#ifdef	__VARARGS_H
#error	cannot use <stdarg.h> with <varargs.h>
#endif

#ifndef	__VA_LIST_DEFINED
#define	__VA_LIST_DEFINED
typedef	void	*va_list;
#endif

#define	va_start(ap, pn)	(ap = (va_list)(&pn + 1))
#define	va_arg(ap, t)		(*(*(t **)&ap)++)
#define	va_end(ap)

#endif
