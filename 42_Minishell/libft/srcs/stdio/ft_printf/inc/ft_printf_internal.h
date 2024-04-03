/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 21:02:45 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 22:15:32 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_printf.h"
# include "libft.h"

/*
** -- STRUCTURES & TYPEDEFS --
*/
typedef struct s_types
{
	char	type;
	void	(*f)();
}	t_types;

typedef struct s_indicators
{
	int	width;
	int	minus;
	int	zero;
	int	dot;
	int	htag;
	int	space;
	int	plus;
	int	is_specifier;
	int	h;
	int	hh;
	int	l;
	int	ll;
	int	lf;
}	t_indicators;

typedef struct s_data
{
	char			*data;
	int				size;
	struct s_data	*next;
}	t_data;

typedef unsigned long long	t_ull;

/*
** -- PROTOTYPES --
** Common
*/
int			ft_len_base(long long n, int base);
void		*ft_malloc_c(size_t size, char c);
char		*ft_mcat(char *dst, char *src);
void		ft_free(size_t nb, ...);
char		*convert_base(long long ptr, char *base);
char		*convert_base_u(t_ull n, char *base);
char		*conv_add_sign(t_indicators t, int sign);
char		*conv_add_z(t_indicators t, char *data, t_ull n, int s);
char		*conv_d(t_indicators t, t_ull n, int sign, char *base);
char		*conv_x(t_indicators t, unsigned long long n, int sign);
char		*space_padding(char *data, int padding);
char		*convert_to_float(long long n, int sign);

/*
** Float Specialized
*/
int			ft_round_str(char *str, int precision);
int			prec_zero_case(long double n, int sign);

/*
** Lists
*/
t_data		*ft_lstd_new(char *data, int size);
t_data		*ft_lstd_last(t_data *lst);
void		ft_lstd_add(t_data **lst, t_data *new);
void		add_lstd(t_data **s, char *str);
void		ft_lstd_get_size(t_data **s, int *size);
void		ft_lstd_print(t_data **s, int *size, int fd);
void		ft_lstd_clear(t_data **lst);
void		ft_fill_ret(t_data **s, char **ret);

/*
** Flags checks
*/
int			check_htag(t_indicators *table);
int			check_spce(t_indicators *table);
int			check_plus(t_indicators *table);
int			check_min(t_indicators *table);
int			check_zero(const char *format, va_list ap, t_indicators *table);
int			check_wdt(const char *format, va_list ap, t_indicators *table);
int			check_prec(const char *format, va_list ap, t_indicators *table);

/*
** Sub-Specifiers conversions
*/
long long	d_spec(t_indicators *t, va_list ap);
t_ull		u_spec(t_indicators *t, va_list ap);
long double	f_spec(t_indicators *t, va_list ap);

/*
** Alloc
*/
t_data		*ft_parse_format(const char *format, va_list ap);
t_types		*ft_init_conversions(void);
void		ft_alloc_mod(t_data **s, t_indicators t);
void		ft_alloc_c(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_s(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_p(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_d(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_i(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_u(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_hex_min(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_hex_maj(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_f(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_n(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_o(t_data **s, t_indicators t, va_list ap);
void		ft_alloc_b(t_data **s, t_indicators t, va_list ap);

int			ft_process(const char *format, va_list ap, int fd);
int			ft_alloc_txt(const char *format, t_data **s);
int			ft_alloc_format(const char *format, va_list ap, t_data **s,
				t_types	*t);

#endif
