/*
	timeb.h		definition for ftime
*/

#ifndef	__TIMEB_H
#define	__TIMEB_H

#ifdef	ANSI
#error	<sys/timeb.h> is not an ANSI header
#endif

#ifndef	__TIME_T_DEFINED
#define	__TIME_T_DEFINED
typedef	long	time_t;
#endif

#ifndef	__TIMEB_DEFINED
#define	__TIMEB_DEFINED
struct	timeb	{
	time_t		time;
	unsigned short	millitm;
	short		timezone;
	short		dstflag;
};
#endif

void	ftime(struct timeb *);

#endif
