/*
	ctype.h		character handling
*/

#ifndef	__CTYPE_H
#define	__CTYPE_H

extern	const	unsigned char	_ctype[];

int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int toupper(int);
int tolower(int);

#define _UPR_P	0x1	/* upper case character */
#define _LWR_P	0x2	/* lower case character */
#define _DGT_P	0x4	/* digit */
#define _SPC_P	0x8	/* ' ', '\t', '\r', '\n', '\v', '\f' */
#define _PUN_P	0x10	/* punctuation character */
#define _CNT_P	0x20	/* control character */
#define _HEX_P	0x40	/* hexadecimal digit */
#define _PRT_P	0x80	/* printable character */

#define	isalnum(c)	(_ctype[(c)+1] & (_UPR_P|_LWR_P|_DGT_P))
#define	isalpha(c)	(_ctype[(c)+1] & (_UPR_P|_LWR_P))
#define	iscntrl(c)	(_ctype[(c)+1] & _CNT_P)
#define	isdigit(c)	(_ctype[(c)+1] & _DGT_P)
#define	isgraph(c)	(_ctype[(c)+1] & (_PUN_P|_UPR_P|_LWR_P|_DGT_P))
#define	islower(c)	(_ctype[(c)+1] & _LWR_P)
#define	isprint(c)	(_ctype[(c)+1] & _PRT_P)
#define	ispunct(c)	(_ctype[(c)+1] & _PUN_P)
#define	isspace(c)	(_ctype[(c)+1] & _SPC_P)
#define	isupper(c)	(_ctype[(c)+1] & _UPR_P)
#define	isxdigit(c)	(_ctype[(c)+1] & _HEX_P)

#ifndef	ANSI
#define	_tolower(c)	((c) - 'A' + 'a')
#define	_toupper(c)	((c) - 'a' + 'A')

#define	isascii(c)	((unsigned)(c) < 0x80 )
#define	toascii(c)	((c) & 0x7f)
#define	iscsymf(c)	(isalpha(c) || (c) == '_')
#define	iscsym(c)	(isalnum(c) || (c) == '_')
#endif

#endif	/* __CTYPE_H */
