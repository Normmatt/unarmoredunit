/*
 *	dos.h - MS-DOS interface
 *
 *	21/Jul/1989	add MS-DOS interface functions
 */

#ifndef	__DOS_H
#define	__DOS_H

#ifdef	ANSI
#error	<dos.h> is not an ANSI header
#endif

#ifndef	__REGS_DEFINED
#define	__REGS_DEFINED
union REGS	{
	struct XREGS	{
		unsigned short	ax, bx, cx, dx, si, di, bp, ds, es, flags, cflag;
	}	x;
	struct HREGS	{
		unsigned char	al, ah, bl, bh, cl, ch, dl, dh;
	}	h;
};

struct SREGS	{
	unsigned short	es, cs, ss, ds;
};
#endif

char	bdos(char, int, char);
char	bdosp(char, void *);
void	segread(struct SREGS *);
int	int86(int, union REGS *, union REGS *);
int	int86y(int, union REGS *, union REGS *);
int	int86x(int, union REGS *, union REGS *, struct SREGS *);
int	intdos(union REGS *, union REGS *);
int	intdosy(union REGS *, union REGS *);
int	intdosx(union REGS *, union REGS *, struct SREGS *);

int	getpid(void);
extern	unsigned int	_psp;

void far *farmalloc(unsigned long);
void far *farcalloc(unsigned long, unsigned long);
void far *farrealloc(void far *, unsigned long);
void	farfree(void far *);
unsigned long	farcoreleft(void);

#define	FP_SEG(p)	((unsigned)((unsigned long)((void far *)(p)) >> 16))
#define	FP_OFF(p)	(unsigned)(p)
#define	MK_FP(s, o)	((void far*)(((unsigned long)(s) << 16)|(unsigned)(o)))

struct	find_t	{
	char	reserved[21];
	char	attrib;
	unsigned wr_time;
	unsigned wr_date;
	long	size;
	char	name[13];
};
#define	_A_NORMAL	0x00
#define	_A_RDONLY	0x01
#define	_A_HIDDEN	0x02
#define	_A_SYSTEM	0x04
#define	_A_VOLID	0x08
#define	_A_SUBDIR	0x10
#define	_A_ARCH		0x20

struct	diskfree_t	{
	unsigned total_clusters;
	unsigned avail_clusters;
	unsigned sectors_per_cluster;
	unsigned bytes_per_sector;
};

struct	dosdate_t	{
	unsigned char	day;
	unsigned char	month;
	unsigned int	year;
	unsigned char	dayofweek;
};

struct	dostime_t	{
	unsigned char	hour;
	unsigned char	minute;
	unsigned char	second;
	unsigned char	hsecond;
};

#define	SH_COMPAT	0x00
#define	SH_DENYRW	0x10
#define	SH_DENYWR	0x20
#define	SH_DENYRD	0x30
#define	SH_DENYNONE	0x40
#define	O_NOINHERIT	0x80

struct	DOSERROR	{
	int	exterror;
	char	class;
	char	action;
	char	locus;
};

unsigned _dos_allocmem(unsigned, unsigned *);
unsigned _dos_close(int);
unsigned _dos_creat(const char *, unsigned, int *);
unsigned _dos_creatnew(const char *, unsigned, int *);
unsigned _dos_findfirst(const char *, unsigned, struct find_t *);
unsigned _dos_findnext(struct find_t *);
unsigned _dos_freemem(unsigned);
void	_dos_getdate(struct dosdate_t *);
unsigned _dos_getdiskfree(unsigned, struct diskfree_t *);
void	_dos_getdrive(unsigned *);
unsigned _dos_getfileattr(const char *, unsigned *);
unsigned _dos_getftime(int, unsigned *, unsigned *);
void	_dos_gettime(struct dostime_t *);
void	(far *_dos_getvect(unsigned))();
void	_dos_keep(unsigned, unsigned);
unsigned _dos_open(const char *, unsigned, int *);
unsigned _dos_read(int, void far *, unsigned, unsigned *);
unsigned _dos_setblock(unsigned, unsigned, unsigned *);
unsigned _dos_setdate(struct dosdate_t *);
void	_dos_setdrive(unsigned, unsigned *);
unsigned _dos_setfileattr(const char *, unsigned);
unsigned _dos_setftime(int, unsigned, unsigned);
unsigned _dos_settime(struct dostime_t *);
void	_dos_setvect(unsigned, void (far *)());
unsigned _dos_write(int, const void far *, unsigned, unsigned *);
int	dosexterr(struct DOSERROR *);

#define	_HARDERR_IGNORE	0
#define	_HARDERR_RETRY	1
#define	_HARDERR_ABORT	2
#define	_HARDERR_FAIL	3

void	_harderr(int (far*)());
void	_hardresume(int);
void	_hardretn(int);

#include <machine.h>

#endif
