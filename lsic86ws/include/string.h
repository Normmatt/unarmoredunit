/*
 *	string.h - string handling
 */

#ifndef	__STRING_H
#define	__STRING_H

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

void	*memcpy(void *, const void *, size_t);
void	*memmove(void *, const void *, size_t);
int	memcmp(const void *, const void *, size_t);
void	*memchr(const void *, char, size_t);
void	*memset(void *, char, size_t);

#ifndef	ANSI
void	*memccpy(void *, const void *, char, size_t);
int	memicmp(const void *, const void *, size_t);
void	movedata(unsigned, unsigned, unsigned, unsigned, size_t);
#endif


char	*strcpy(char *, const char *);
char	*strncpy(char *, const char *, size_t);
char	*strcat(char *, const char *);
char	*strncat(char *, const char *, size_t);
int	strcmp(const char *, const char *);
int	strncmp(const char *, const char *, size_t);
char	*strchr(const char *, char);
char	*strrchr(const char *, char);
size_t	strspn(const char *, const char *);
size_t	strcspn(const char *, const char *);
char	*strpbrk(const char *, const char *);
char	*strstr(const char *, const char *);
size_t	strlen(const char *);
char	*strerror(int);
char	*strtok(char *, const char *);

#ifndef	ANSI
char	*strset(char *, char);
char	*strnset(char *, char, size_t);
char	*strrev(char *);
char	*strlwr(char *);
char	*strupr(char *);
int	stricmp(const char *, const char *);
#define	strcmpi		stricmp
int	strnicmp(const char *, const char *, size_t);
#define	strncmpi	strnicmp
#ifndef	__STDROM_H
char	*strdup(const char *);
#endif
char	*stpcpy(char *, const char *);

#define	movmem(src, dst, len)	memcpy((dst), (src), (len))
#define	setmem(dst, len, dat)	memset((dst), (dat), (len))
#endif	/* ANSI */

#endif	/* __STRING_H */
