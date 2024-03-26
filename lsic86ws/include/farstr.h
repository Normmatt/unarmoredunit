/*
 *	farstr.h - far string handling
 */

#ifndef	__FARSTR_H
#define	__FARSTR_H

#ifdef	ANSI
#error	<farstr.h> is not an ANSI header
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

void	far *far_memcpy(void far *, const void far *, size_t);
void	far *far_memmove(void far *, const void far *, size_t);
void	far *far_memset(void far *, char, size_t);
int	far_memcmp(const void far *, const void far *, size_t);
void	far *far_memchr(const void far *, char, size_t);
int	far_memicmp(const void far *, const void far *, size_t);
void	far *far_memccpy(void far *, const void far *, char, size_t);

char	far *far_strcpy(char far *, const char far *);
char	far *far_strncpy(char far *, const char far *, size_t);
char	far *far_strcat(char far *, const char far *);
char	far *far_strncat(char far *, const char far *, size_t);
int	far_strcmp(const char far *, const char far *);
int	far_strncmp(const char far *, const char far *, size_t);
size_t	far_strlen(const char far *);
char	far *far_strchr(const char far *, char);
char	far *far_strrchr(const char far *, char);
char	far *far_strstr(const char far *, const char far *);
size_t	far_strspn(const char far *, const char far *);
size_t	far_strcspn(const char far *, const char far *);
char	far *far_strpbrk(const char far *, const char far *);
char	far *far_strtok(char far *, const char far *);
char	far *far_stpcpy(char far *, const char far *);
char	far *far_strnset(char far *, char, size_t);
char	far *far_strset(char far *, char);
char	far *far_strrev(char far *);
char	far *far_strlwr(char far *);
char	far *far_strupr(char far *);
int	far_strnicmp(const char far *, const char far *, size_t);
#define	far_strncmpi	far_strnicmp
int	far_stricmp(const char far *, const char far *);
#define	far_strcmpi	far_stricmp
#ifndef	__STDROM_H
char	far *far_strdup(const char far *);
#endif

#define	far_movmem(src, dst, len)	far_memcpy((dst), (src), (len))
#define	far_setmem(dst, len, dat)	far_memset((dst), (dat), (len))

#endif
