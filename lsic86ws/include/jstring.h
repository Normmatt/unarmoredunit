/*
	jstring.h		kanji string handling
*/

#ifndef	__JSTRING_H
#define	__JSTRING_H

#ifdef	ANSI
#error	<jstring.h> is not an ANSI header
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

char	*jstrstr(const char *, const char *);
char	*jstrrev(char *);
char	*jstradv(const char *, int);
int	jstrlen(const char *);
int	jstrcmp(const char *, const char *);
char	*jstrncat(char *, const char *, size_t);
int	jstrncmp(const char *, const char *, size_t);
char	*jstrncpy(char *, const char *, size_t);
char	*jstrchr(const char *, unsigned short);
char	*jstrskip(const char *, const char *);
char	*jstrtok(char *, const char *);
char	*jstrrchr(const char *, unsigned short);
char	*jstrmatch(const char *, const char *);

int	btom(const char *, int);
int	mtob(const char *, int);

#endif
