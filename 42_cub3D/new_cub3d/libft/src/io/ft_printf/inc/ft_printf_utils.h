/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:34:03 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 18:19:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H
# include "libft.h"
# define N_LOW 0x0
# define N_UP 0x1
# define TYPE_HH 0x8
# define TYPE_H 0x10
# define TYPE_L 0x40
# define TYPE_LL 0x80

typedef unsigned int		t_uint;
typedef unsigned char		t_uchar;
typedef unsigned short		t_ushort;
typedef unsigned long		t_ul;
typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef struct s_flag
{
	int	type;
	int	width;
	int	minus;
	int	zero;
	int	prec;
	int	star;
	int	plus;
	int	space;
	int	hashtag;
	int	h;
	int	hh;
	int	l;
	int	ll;
}				t_flag;

/*
** Function process
*/
t_flag	ft_init_flag(void);

int		ft_parse(int cnt, int type, va_list arg,
			t_flag flag);

int		ft_process(const char *format, va_list arg);

/*
** Function parse type
*/
int		ft_type(int type);
int		ft_parse_char(int c, t_flag flag);
int		ft_parse_string(char *s, t_flag flag);
int		ft_parse_pointer(void *p, t_flag flag);
int		ft_parse_int(t_ll i, t_flag flag);
int		ft_parse_uint(t_ull ui, t_flag flag);
int		ft_parse_hex(t_ull ui, int low_up, t_flag flag);
int		ft_parse_int_p(int *i, int count);
int		ft_parse_c_with_spec(va_list arg, t_flag flag);
int		ft_parse_s_with_spec(va_list arg, t_flag flag);
int		ft_parse_octal(t_ull ui, t_flag flag);

/*
** Function parse flags
*/
int		ft_flags(int flag);
int		ft_flags_check(const char *format, int count);
t_flag	ft_minus(t_flag flag);
t_flag	ft_width(t_flag flag, va_list arg);
t_flag	ft_digit(char format, t_flag flag);

int		ft_prec(const char *format, int begin_value,
			t_flag *flag, va_list arg);

int		ft_parse_width(int width, int hold, int zero);

int		ft_parse_flags(const char *format, int count,
			t_flag *flag, va_list arg);

void	ft_parse_flags_plus(const char *format, int count,
			t_flag **flag);

t_flag	ft_space(t_flag flag);
t_flag	ft_plus(t_flag flag);
t_flag	ft_hashtag(t_flag flag);

/*
** Function parse spec
*/
int		ft_spec_flag(char *s);
t_flag	ft_type_def(t_flag flag, int type);
t_ll	type_d(va_list arg, t_flag flag);
t_ull	type_u(va_list arg, t_flag flag);

/*
** Utils
*/
int		ft_putchar_pf(char c);
size_t	ft_putstr_pf(char *s);
int		ft_putstr_prec_pf(char *s, int prec);

/*
** Convert function
*/
int		ft_conv_dh_pf(int n, int low_up);
size_t	ft_lllen_base_pf(t_ll n, int base);
size_t	ft_uintlen_base_pf(t_uint n, int base);
size_t	ft_ulllen_base_pf(t_ull n, int base);
char	*ft_lltoa_base_pf(t_ll n, int base);
char	*ft_ulltoa_base_pf(t_ull un, int base, int low_up);

#endif
