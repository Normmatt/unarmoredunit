/*
	errno.h		error constants

	14-Sep-1988 15:47
*/

#ifndef	__ERRNO_H
#define	__ERRNO_H

#define	EZERO		0	/* Error 0			*/
#define	ENOENT		2	/* No such file or directory	*/
#define	E2BIG		7	/* Arg list too long		*/
#define	ENOEXEC		8	/* Exec format error		*/
#define EBADF		9	/* Bad file number		*/
#define	ENOMEM		12	/* Not enough core		*/
#define EACCES		13	/* Permission denied		*/
#define	EEXIST		17	/* File Exists			*/
#define	EXDEV		18	/* Cross-device link		*/
#define ENODEV		19	/* No such device		*/
#define EINVAL		22	/* Invalid argument		*/
#define	EMFILE		24	/* Too many open files		*/
#define ENOSPC		28	/* No space left on device	*/
#define EDOM		33	/* Math argument		*/
#define ERANGE		34	/* Result too large		*/

extern	int	errno;

#ifndef	ANSI
extern	char	*sys_errlist[];
extern	int	sys_nerr;
#endif

#endif
