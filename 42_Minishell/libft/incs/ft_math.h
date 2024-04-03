/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:00:09 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 01:02:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <stdint.h>

/*
** -- DEFINES --
** math constants
**
** pi constant and its variables
** Scheme:
**
**        T_PI_2
**          |   T_PI_4
**          | /
** T_PI ---- ---- T_2PI
**          |
**          |
**       T_3PI_2
*/

/*
** pi/4
*/
# define T_PI_4 0.785398163397448309615660845819875721

/*
** pi/2
*/
# define T_PI_2 1.57079632679489661923132169163975144

/*
** pi
*/
# define T_PI 3.14159265358979323846264338327950288

/*
** (3*pi)/2 or pi+(pi/2)
*/
# define T_3PI_2 4.71238898038468967399694520281627774

/*
** 2*pi
*/
# define T_2PI 6.28318530717958623199592693708837032

/*
** 1/pi
*/
# define T_1_PI 0.318309886183790671537767526745028724

/*
** 2/pi
*/
# define T_2_PI 0.636619772367581343075535053490057448

/*
** 2/sqrt(pi)
*/
# define T_2_SQRTPI 1.12837916709551257389615890312154517

/*
** sqrt(2)
*/
# define T_SQRT2 1.41421356237309504880168872420969808

/*
** 1/sqrt(2)
*/
# define T_SQRT1_2 0.707106781186547524400844362104849039

/*
** E constant
*/
# define T_E 2.71828182845904523536028747135266250

/*
** log2(e)
*/
# define T_LOG2E 1.44269504088896340735992468100189214

/*
** log10(e)
*/
# define T_LOG10E 0.434294481903251827651128918916605082

/*
** loge(2)
*/
# define T_LN2 0.693147180559945309417232121458176568

/*
** loge(10)
*/
# define T_LN10 2.30258509299404568401799145468436421

/*
** -- TYPEDEFS & DATA STRUCTURES --
** u_dbl80 is used to extract data from a `long double' variable
*/
union				u_dbl80
{
	long double		ld;
	struct
	{
		uint64_t	m;
		uint16_t	exp;
	}				s_xtr;
};

/*
** -- PROTOTYPES --
** custom functions
*/
size_t				ft_factorial(size_t nb);
int					ft_isprime(unsigned long long nb);
unsigned long long	ft_find_next_prime(unsigned long long nb);
int					ft_gcd(int i, int j);

/*
** (almost) real libc functions - with their types variants
*/
int					ft_isnanf(float x);
int					ft_isnan(double x);
int					ft_isnanl(long double x);

int					ft_isinff(float x);
int					ft_isinf(double x);
int					ft_isinfl(long double x);

int					ft_signbitf(float x);
int					ft_signbit(double x);
int					ft_signbitl(long double x);

float				ft_copysignf(float x, float y);
double				ft_copysign(double x, double y);
long double			ft_copysignl(long double x, long double y);

float				ft_ceilf(float f);
double				ft_ceil(double f);

float				ft_floorf(float x);
double				ft_floor(double x);

/*
** ft_*round* functions are false in certain cases
*/
float				ft_roundf(float x);
double				ft_round(double x);

long int			ft_lround(double x);
long int			ft_lroundf(float x);
/*
** END ft_*round* functions are false in certain cases
*/

float				ft_truncf(float x);
double				ft_trunc(double x);

/*
** ft_fmod is imprecise with very large numbers
*/
float				ft_fmodf(float x, float y);
double				ft_fmod(double x, double y);
/*
** END ft_fmod is imprecise with very large numbers
*/

float				ft_fdimf(float x, float y);
double				ft_fdim(double x, double y);
long double			ft_fdiml(long double x, long double y);

float				ft_fmaxf(float x, float y);
double				ft_fmax(double x, double y);
long double			ft_fmaxl(long double x, long double y);

float				ft_fminf(float x, float y);
double				ft_fmin(double x, double y);
long double			ft_fminl(long double x, long double y);

float				ft_fmaf(float x, float y, float z);
double				ft_fma(double x, double y, double z);
long double			ft_fmal(long double x, long double y, long double z);

int					ft_abs(int i) __attribute__((const));
float				ft_fabsf(float x);
double				ft_fabs(double x);
long double			ft_fabsl(long double x);

float				ft_sqrtf(float x);
double				ft_sqrt(double x);
long double			ft_sqrtl(long double x);

float				ft_hypotf(float x, float y);
double				ft_hypot(double x, double y);
long double			ft_hypotl(long double x, long double y);

float				ft_modff(float value, float *iptr);
double				ft_modf(double value, double *iptr);

float				ft_frexpf(float value, int *exp);
double				ft_frexp(double value, int *exp);
long double			ft_frexpl(long double value, int *exp);

double				ft_ldexp(double x, int n);

double				ft_pow(double nb, int power);

#endif
