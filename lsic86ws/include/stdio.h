/*
	stdio.h		header for input/output
*/

#ifndef	__STDIO_H
#define	__STDIO_H

#ifndef	ANSI
#include <stddef.h>	/* for compatibility to older version */
#endif	/* ANSI */

#ifndef	__SIZE_T_DEFINED
#define	__SIZE_T_DEFINED
typedef	unsigned size_t;
#endif

#ifndef	__VA_LIST_DEFINED
#define	__VA_LIST_DEFINED
typedef	void	*va_list;
#endif

#ifndef	__FPOS_T_DEFINED
#define	__FPOS_T_DEFINED
typedef	long	fpos_t;
#endif

#ifndef	__FILE_DEFINED
#define	__FILE_DEFINED
typedef	struct	{
	char	mode;		/*	file mode	R, W, R/W	*/
	char	*ptr;		/*	next character position		*/
	int	rcount;		/*	number of characters left	*/
	int	wcount;		/*	number of rooms left		*/
	char	*base;		/*	location of buffer		*/
	unsigned bufsiz;	/*	size of bufer			*/
	int	fd;		/*	file descriptor			*/
	char	smallbuf[1];	/*	used for buffer when unbufferd	*/
}	FILE;
#endif


#define	_READ	0001
#define	_WRITE	0002
#define	_EOF	0004
#define	_ERR	0010
#define	_BINARY	0020
#define	_R	0040
#define	_W	0100
#define	_BUFF	0200


#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define	SYS_OPEN	20	/*	maximum number of buffered I/O	*/
#define	BUFSIZ		1024	/*	default buffer size allocated	*/
				/*	by fopen.			*/

#define	FILENAME_MAX	65
#define	FOPEN_MAX	SYS_OPEN


extern	FILE	_iob[SYS_OPEN];

#define	stdin	(&_iob[0])
#define	stdout	(&_iob[1])
#define	stderr	(&_iob[2])
#ifndef	CPM
#define	stdaux	(&_iob[3])
#define	stdprn	(&_iob[4])
#define	_SYS_STREAMS	5
#else	/* CPM */
#define	_SYS_STREAMS	3
#endif	/* CPM */

#define	EOF	-1


FILE	*fopen(const char *, const char *);
FILE	*freopen(const char *, const char *, FILE *);
int	fflush(FILE *);
int	fclose(FILE *);
#ifndef	ANSI
FILE	*fdopen(int, const char *);
FILE	*fdreopen(int, const char *, FILE *);
int	flushall(void);
int	fcloseall(void);
#endif	/* ANSI */

int	fprintf(FILE *, const char *, ...);
int	printf(const char *, ...);
int	sprintf(char *, const char *, ...);
int	vprintf(const char *, va_list);
int	vfprintf(FILE *, const char *, va_list);
int	vsprintf(char *, const char *, va_list);

int	fscanf(FILE *, const char *, ...);
int	scanf(const char *, ...);
int	sscanf(const char *, const char *, ...);

int	fgetc(FILE *);
char	*fgets(char *, int, FILE *);
char	*gets(char *);
#define	getc	fgetc
#define	getchar()	getc(stdin)
#ifndef	ANSI
int	fgetchar(void);
#endif	/* ANSI */

int	fputc(char, FILE *);
int	fputs(const char *, FILE *);
int	puts(const char *);
#define	putc	fputc
#define	putchar(c)	putc(c, stdout)
#ifndef	ANSI
int	fputchar(char);
#endif	/* ANSI */

int	ungetc(char, FILE *);

int	fread(void *, size_t, size_t, FILE *);
int	fwrite(const void *, size_t, size_t, FILE *);
int	fseek(FILE *, long, int);
long	ftell(FILE *);
void	rewind(FILE *);
int	fgetpos(FILE *, fpos_t *);
int	fsetpos(FILE *, const fpos_t *);

#define	clearerr(fp)	((fp)->mode &= ~(_EOF | _ERR))
#define	feof(fp)	((fp)->mode & _EOF)
#define	ferror(fp)	((fp)->mode & _ERR)
#ifndef	ANSI
#define	fileno(fp)	((fp)->fd)
#endif	/* ANSI */

void	perror(const char *);

#ifndef	ANSI
#define	fsetbin(fp)	((fp)->mode |= _BINARY)
#define	fsettext(fp)	((fp)->mode &= ~_BINARY)
#endif	/* ANSI */

void	setbuf(FILE *, char *);
int	setvbuf(FILE *, char *, int, size_t);
#define	_IOFBF	0
#define	_IONBF	1
/* #define	_IOLBF... not yet supported */


#define	L_tmpnam	13
#define	TMP_MAX		65535
#define	FNAME_MAX	67

FILE	*tmpfile(void);
char	*tmpnam(char *);
#ifndef	ANSI
#define	P_tmpdir	"\\"
char	*tempnam(const char *, const char *);
int	rmtmp(void);
#endif	/* ANSI */

int	remove(const char *);
int	rename(const char *, const char *);

#ifndef	ANSI
int	unlink(const char *);

int	putw(int, FILE *);
int	getw(FILE *);

#include <io.h>		/* for compatibility to older version */
#include <conio.h>
#include <direct.h>
#endif	/* ANSI */

#endif	/* __STDIO_H */
