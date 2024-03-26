/*
	fcntl.h		- file control
*/

#ifndef	__FCNTL_H
#define	__FCNTL_H

#ifdef	ANSI
#error	<fcntl.h> is not an ANSI header
#endif

/* definitions of open flags */

#define	O_BINARY	0	/* Open for Binary files */

#define	O_RDONLY	0x00	/* Open for reading only */
#define	O_WRONLY	0x01	/* Open for writing only */
#define	O_RDWR		0x02	/* Open for reading and writing */

#define	O_APPEND	0x10	/* Set append mode */
#define	O_CREAT		0x20	/* Create file if it dosen't exist */
#define	O_TRUNC		0x40	/* Truncate flag */
#define	O_EXCL		0x80	/* Exclusive use flag */

#endif
