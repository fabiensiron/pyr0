/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * from: @(#)fdlibm.h 5.1 93/09/24
 * $FreeBSD: src/lib/msun/src/math.h,v 1.61 2005/04/16 21:12:47 das Exp $
 */

#ifndef _MATH_H_
#define	_MATH_H_

#include <atomos/kernel.h>
#include <atomos/limits.h>

double	acos(double);
double	asin(double);
double	atan(double);
double	atan2(double, double);
double	cos(double);
double	sin(double);
double	tan(double);

double	cosh(double);
double	sinh(double);
double	tanh(double);

double	exp(double);
double	frexp(double, int *);	/* fundamentally !__pure2 */
double	ldexp(double, int);
double	log(double);
double	log10(double);
double	modf(double, double *);	/* fundamentally !  */

double	pow(double, double);
double	sqrt(double);

double	ceil(double);
double	fabs(double)  ;
double	floor(double);
double	fmod(double, double);

/*
 * These functions are not in C90.
 */
/* #if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE */
double	acosh(double);
double	asinh(double);
double	atanh(double);
double	cbrt(double);
double	erf(double);
double	erfc(double);
double	exp2(double);
double	expm1(double);
double	fma(double, double, double);
double	hypot(double, double);
int	ilogb(double)  ;
/* int	(isinf)(double)  ; */
int	(isnan)(double)  ;
double	lgamma(double);
long long llrint(double);
long long llround(double);
double	log1p(double);
double	logb(double);
long	lrint(double);
long	lround(double);
double	nan(const char *)  ;
double	nextafter(double, double);
double	remainder(double, double);
double	remquo(double, double, int *);
double	rint(double);
/* #endif */ /* __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE */

/* #if __BSD_VISIBLE || __XSI_VISIBLE */
double	j0(double);
double	j1(double);
double	jn(int, double);
double	scalb(double, double);
double	y0(double);
double	y1(double);
double	yn(int, double);

/* #if __XSI_VISIBLE <= 500 || __BSD_VISIBLE */
double	gamma(double);
/* #endif */
/* #endif */ /* __BSD_VISIBLE || __XSI_VISIBLE */

/* #if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 */
double	copysign(double, double)  ;
double	fdim(double, double);
double	fmax(double, double)  ;
double	fmin(double, double)  ;
double	nearbyint(double);
double	round(double);
double	scalbln(double, long);
double	scalbn(double, int);
double	tgamma(double);
double	trunc(double);
/* #endif */

/*
 * BSD math library entry points
 */
/* #if __BSD_VISIBLE */
double	drem(double, double);
int	finite(double)  ;
int	isnanf(float)  ;

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
double	gamma_r(double, int *);
double	lgamma_r(double, int *);

/*
 * IEEE Test Vector
 */
double	significand(double);
/* #endif */ /* __BSD_VISIBLE */

/* float versions of ANSI/POSIX functions */
/*#if __ISO_C_VISIBLE >= 1999 */
float	acosf(float);
float	asinf(float);
float	atanf(float);
float	atan2f(float, float);
float	cosf(float);
float	sinf(float);
float	tanf(float);

float	coshf(float);
float	sinhf(float);
float	tanhf(float);

float	exp2f(float);
float	expf(float);
float	expm1f(float);
float	frexpf(float, int *);	/* fundamentally !  */
int	ilogbf(float)  ;
float	ldexpf(float, int);
float	log10f(float);
float	log1pf(float);
float	logf(float);
float	modff(float, float *);	/* fundamentally !  */

float	powf(float, float);
float	sqrtf(float);

float	ceilf(float);
float	fabsf(float)  ;
float	floorf(float);
float	fmodf(float, float);
float	roundf(float);

float	erff(float);
float	erfcf(float);
float	hypotf(float, float);
float	lgammaf(float);
float	tgammaf(float);

float	acoshf(float);
float	asinhf(float);
float	atanhf(float);
float	cbrtf(float);
float	logbf(float);
float	copysignf(float, float)  ;
long long llrintf(float);
long long llroundf(float);
long	lrintf(float);
long	lroundf(float);
float	nanf(const char *)  ;
float	nearbyintf(float);
float	nextafterf(float, float);
float	remainderf(float, float);
float	remquof(float, float, int *);
float	rintf(float);
float	scalblnf(float, long);
float	scalbnf(float, int);
float	truncf(float);

float	fdimf(float, float);
float	fmaf(float, float, float);
float	fmaxf(float, float)  ;
float	fminf(float, float)  ;
/* #endif */

/*
 * float versions of BSD math library entry points
 */
/* #if __BSD_VISIBLE */
float	dremf(float, float);
int	finitef(float)  ;
float	gammaf(float);
float	j0f(float);
float	j1f(float);
float	jnf(int, float);
float	scalbf(float, float);
float	y0f(float);
float	y1f(float);
float	ynf(int, float);

/*
 * Float versions of reentrant version of gamma & lgamma; passes
 * signgam back by reference as the second argument; user must
 * allocate space for signgam.
 */
float	gammaf_r(float, int *);
float	lgammaf_r(float, int *);

/*
 * float version of IEEE Test Vector
 */
float	significandf(float);
/* #endif */	/* __BSD_VISIBLE */ 

#endif /* !_MATH_H_ */
