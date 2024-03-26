/*
	float.h		constants related to floating-point arithmetic

	14-Sep-1988 14:14
*/

#ifndef	__FLOAT_H
#define	__FLOAT_H

#define	FLT_RADIX	2
#define	FLT_ROUNDS	1

#define	FLT_MANT_DIG	24
#define	FLT_DIG		6
#define	FLT_MIN_EXP	-125
#define	FLT_MIN_10_EXP	-37
#define	FLT_MAX_EXP	128
#define	FLT_MAX_10_EXP	38
#define	FLT_MAX		_huge_float	/* 3.4028e+38 */
#define	FLT_EPSILON	1.19209290e-7F
#define	FLT_MIN		1.1755e-38F

#define	DBL_MANT_DIG	53
#define	DBL_DIG		15
#define	DBL_MIN_EXP	-1021
#define	DBL_MIN_10_EXP	-307
#define	DBL_MAX_EXP	1024
#define	DBL_MAX_10_EXP	308
#define	DBL_MAX		_huge_double	/* 1.7977e+308 */
#define	DBL_EPSILON	2.2204460492503131e-16
#define	DBL_MIN		2.2250738585072014e-308

#define	LDBL_MANT_DIG	64
#define	LDBL_DIG	19
#define	LDBL_MIN_EXP	-16381
#define	LDBL_MIN_10_EXP	-4931
#define	LDBL_MAX_EXP	16384
#define	LDBL_MAX_10_EXP	4932
#define	LDBL_MAX	_huge_ldouble	/* 1.1897e+4932 */
#define	LDBL_EPSILON	1.084202172485504e-19L
#define	LDBL_MIN	_tiny_ldouble	/* 3.3621e-4932 */

extern	float		_huge_float;
extern	double		_huge_double;
extern	long double	_huge_ldouble, _tiny_ldouble;

#ifndef	ANSI
/* definitions of subcode for signal handler */
#define	FPE_INTDIV0	1
#define	FPE_INVALID	2
#define	FPE_DENORMAL	3
#define	FPE_ZERODIVIDE	4
#define	FPE_OVERFLOW	5
#define	FPE_UNDERFLOW	6
#define	FPE_INEXACT	7
#define	FPE_EXPLICITGEN	8


/* 80x87 status word */
#define	SW_INVALID		0x0001
#define	SW_DENORMAL		0x0002
#define	SW_ZERODIVIDE		0x0004
#define	SW_OVERFLOW		0x0008
#define	SW_UNDERFLOW		0x0010
#define	SW_INEXACT		0x0020

/* 80x87 control word */
#define	MCW_EM			0x003F
#define		EM_INVALID	0x0001
#define		EM_DENORMAL	0x0002
#define		EM_ZERODIVIDE	0x0004
#define		EM_OVERFLOW	0x0008
#define		EM_UNDERFLOW	0x0010
#define		EM_INEXACT	0x0020
#define	MCW_PC			0x0300
#define		PC_24		0x0000
#define		PC_53		0x0200
#define		PC_64		0x0300
#define	MCW_RC			0x0C00
#define		RC_NEAR		0x0000
#define		RC_DOWN		0x0400
#define		RC_UP		0x0800
#define		RC_CHOP		0x0C00
#define	MCW_IC			0x1000
#define		IC_PROJECTIVE	0x0000
#define		IC_AFFINE	0x1000

#define	CW_DEFAULT	(RC_NEAR + PC_64 + IC_AFFINE + EM_UNDERFLOW + EM_INEXACT)

void	_fpreset(void);
unsigned _control87(unsigned, unsigned);
unsigned _clear87(void);
unsigned _status87(void);
#endif	/* ANSI */

#endif
