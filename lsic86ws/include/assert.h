/*
 *	assert.h
 */

#ifndef	__ASSERT_H
#define	__ASSERT_H


#ifdef	NDEBUG
#define	assert(cond)	((void)0)
#else	/* NDEBUG */
#define	_qq_(s)	#s
#define	_q_(s)	_qq_(s)
#define	assert(cond)	\
	((cond) ? (void)0 : \
		  _assert(#cond ", file " __FILE__ ", line " _q_(__LINE__)))
void _assert(char *);
#endif	/* NDEBUG */

#endif	/* __ASSERT_H */
