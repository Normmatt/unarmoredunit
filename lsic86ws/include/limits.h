/*
	limits.h	defines constants for the sizes of integral types

	14-Sep-1988 14:02
*/

#ifndef	__LIMITS_H
#define	__LIMITS_H

#define	CHAR_BIT	8

#define	CHAR_MAX	UCHAR_MAX
#define	CHAR_MIN	0

#define	INT_MAX		+32767
#define	INT_MIN		-32767

#define	LONG_MAX	+2147483647L
#define	LONG_MIN	-2147483647L

#define	SCHAR_MAX	+127
#define	SCHAR_MIN	-127

#define	SHRT_MAX	+32767
#define	SHRT_MIN	-32767

#define	UCHAR_MAX	255U
#define	UINT_MAX	65535U
#define	ULONG_MAX	4294967295UL
#define	USHRT_MAX	65535U

#endif
