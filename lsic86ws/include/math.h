/*
	math.h			mathematics library
*/

#ifndef	__MATH_H
#define	__MATH_H


#define	HUGE_VAL	_huge_double	/* for double */
extern	double	_huge_double;

#define	PI	3.1415926535897932386

double	sin(double);
double	cos(double);
double	tan(double);
double	asin(double);
double	acos(double);
double	atan(double);
double	atan2(double, double);
double	sinh(double);
double	cosh(double);
double	tanh(double);

double	log(double);
double	log10(double);
double	exp(double);
double	pow(double, double);
double	sqrt(double);
double	fabs(double);
double	fmod(double, double);
double	ceil(double);
double	floor(double);

double	modf(double, double *);
double	frexp(double, int *);
double	ldexp(double, int);

#ifndef	ANSI
long int	labs(long int);
int	abs(int);
double	atof(const char *);

struct	exception	{
	int	type;
	char	*name;
	double	arg1;
	double	arg2;
	double	retval;
};

#define	DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6

int	matherr(struct exception *);

#endif

#endif
