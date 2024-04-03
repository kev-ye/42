/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:15:52 by besellem          #+#    #+#             */
/*   Updated: 2021/05/20 00:29:16 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_stdint.h"

int			ft_bcmp(const void *b1, const void *b2, size_t len);
void		ft_bcopy(const void *src, void *dst, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memdel(void **ptr);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);

int			ft_strisall(char *str, int (*f)(int));
int			ft_strisalnum(char *str);
int			ft_strisalpha(char *str);
int			ft_strisascii(char *str);
int			ft_strisdigit(char *str);
int			ft_strisprint(char *str);

int			ft_incharset(const char *charset, int c);
int			ft_stridx(const char *haystack, const char *needle);
size_t		ft_stroc(const char *haystack, char c);

char		*ft_index(const char *s, int c);
char		*ft_rindex(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strpbrk(const char *s, const char *charset);
char		*ft_strcasestr(const char *haystack, const char *needle);

char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t maxlen);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strupcase(char *str);
char		*ft_strlowcase(char *str);
char		*ft_strcapitalize(char *str);

char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		**ft_strsplit(const char *str, const char *charset);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strsjoin(size_t size, char **strs, char *sep);

size_t		ft_strslen(char **s);
void		*ft_strsfree(size_t size, char **s);

// Ternary operations
void		*ft_trn(int condition, void *if_true, void *if_false);
char		*ft_trns(int condition, char *if_true, char *if_false);
double		ft_trnd(int condition, double if_true, double if_false);
long double	ft_trnld(int condition, long double if_true, long double if_false);
int32_t		ft_trni(int condition, int32_t if_true, int32_t if_false);
ssize_t		ft_trnl(int condition, ssize_t if_true, ssize_t if_false);
int64_t		ft_trnll(int condition, int64_t if_true, int64_t if_false);
uint32_t	ft_trnu(int condition, uint32_t if_true, uint32_t if_false);
size_t		ft_trnul(int condition, size_t if_true, size_t if_false);
uint64_t	ft_trnull(int condition, uint64_t if_true, uint64_t if_false);
// END Ternary operations

#endif
