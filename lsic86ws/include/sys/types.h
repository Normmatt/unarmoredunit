/*
	types.h		type definitions
*/

#ifndef	__TYPES_H
#define	__TYPES_H

#ifdef	ANSI
#error	<sys/types.h> is not an ANSI header
#endif

#ifndef	__INO_T_DEFINED
#define	__INO_T_DEFINED
typedef	unsigned short	ino_t;
#endif

#ifndef	__DEV_T_DEFINED
#define	__DEV_T_DEFINED
typedef	short		dev_t;
#endif

#ifndef	__OFF_T_DEFINED
#define	__OFF_T_DEFINED
typedef	long		off_t;
#endif

#ifndef	__TIME_T_DEFINED
#define	__TIME_T_DEFINED
typedef	long		time_t;
#endif

#endif
