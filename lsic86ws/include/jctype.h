/*
	jctype.h		kanji character handling
*/

#ifndef	__JCTYPE_H
#define	__JCTYPE_H

#ifdef	ANSI
#error	<jctype.h> is not an ANSI header
#endif

#include <ctype.h>

extern	const	unsigned char	_jctype[];

#define	_J_KPUN_P	0x01	/* katakana punctuation character */
#define	_J_KANA_P	0x02	/* katakana character */
#define	_J_KNJ1_P	0x04	/* kanji 1st character */
#define	_J_KNJ2_P	0x08	/* kanji 2nd character */

#define	iskana(c)	((_jctype[(c)+1] & (_J_KPUN_P | _J_KANA_P)) != 0)
#define	iskpun(c)	((_jctype[(c)+1] & _J_KPUN_P) != 0)
#define	iskmoji(c)	((_jctype[(c)+1] & _J_KANA_P) != 0)
#define	isalkana(c)	(isalpha(c) || iskmoji(c))
#define	ispnkana(c)	(ispunct(c) || iskpun(c))
#define	isalnmkana(c)	(isalnum(c) || iskmoji(c))
#define	isprkana(c)	(isprint(c) || iskana(c))
#define	isgrkana(c)	(isgraph(c) || iskana(c))

#define	iskanji(c)	((_jctype[(c)+1] & _J_KNJ1_P) != 0)
#define	iskanji2(c)	((_jctype[(c)+1] & _J_KNJ2_P) != 0)


int	jiszen(unsigned short);
#define	jisl0(c)	(jiszen(c) && (c) <= 0x889e)
#define	jisl1(c)	(jiszen(c) && 0x889f <= (c) && (c) <= 0x9872)
#define	jisl2(c)	(jiszen(c) && 0x989f <= (c) && (c) <= 0xea9e)

#define	jisalpha(c)	(jisupper(c) || jislower(c))
#define	jisupper(c)	(0x8260 <= (c) && (c) <= 0x8279)
#define	jislower(c)	(0x8281 <= (c) && (c) <= 0x829a)
#define	jisdigit(c)	(0x824f <= (c) && (c) <= 0x8258)
#define	jiskata(c)	(0x8340 <= (c) && (c) <= 0x8396 && (c) != 0x837f)
#define	jishira(c)	(0x829f <= (c) && (c) <= 0x82f1)
#define	jiskigou(c)	(0x8141 <= (c) && (c) <= 0x81ac && (c) != 0x817f)
#define	jisspace(c)	((c) == 0x8140)

unsigned short	jtolower(unsigned short);
unsigned short	jtoupper(unsigned short);
unsigned short	jtohira(unsigned short);
unsigned short	jtokata(unsigned short);
unsigned short	hantozen(unsigned short);
unsigned short	zentohan(unsigned short);
unsigned short	mstojis(unsigned short);
unsigned short	jistoms(unsigned short);
#define	jmstojis	mstojis
#define	jistojms	jistoms

int	chkctype(char, int);
int	nthctype(const char *, int);

#define	CT_ANK	0
#define	CT_KJ1	1
#define	CT_KJ2	2
#define	CT_ILGL	-1

#endif
