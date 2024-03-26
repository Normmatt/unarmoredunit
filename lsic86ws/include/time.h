/*
	time.h	header for time functions
*/

#ifndef	__TIME_H
#define	__TIME_H

#ifndef	NULL
#if	defined(_D_FAR)
#define	NULL	(0L)
#else
#define	NULL	(0)
#endif
#endif

#define	CLOCKS_PER_SEC	1

#ifndef	__SIZE_T_DEFINED
#define	__SIZE_T_DEFINED
typedef	unsigned size_t;
#endif

#ifndef	__STRUCT_TM_DEFINED
#define	__STRUCT_TM_DEFINED
struct	tm	{
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};
#endif

#ifndef	__CLOCK_T_DEFINED
#define	__CLOCK_T_DEFINED
typedef	long	clock_t;
#endif

#ifndef	__TIME_T_DEFINED
#define	__TIME_T_DEFINED
typedef	long	time_t;
#endif


struct	tm	*localtime(const time_t *);
struct	tm	*gmtime(const time_t *);
char	*asctime(const struct tm *);
char	*ctime(const time_t *);
double	difftime(time_t, time_t);
time_t	mktime(struct tm *);

time_t	time(time_t *);
clock_t	clock(void);

size_t	strftime(char *, size_t, const char *, const struct tm *);

#ifndef	ANSI
void	stime(const time_t *);
void	tzset(void);

extern	int	daylight;
extern	long	timezone;
extern	char	*tzname[2];
#endif	/* ANSI */

#endif	/* __TIME_H */
