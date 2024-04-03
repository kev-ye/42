#include "malloc.h"


size_t	_strlen(const char *s) {
	const char	*str;

	str = s;
	while (*str)
		++str;
	return (str - s);
}

size_t	_intlen(size_t n) {
	size_t	count;

	if (n)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

void*	ft_memcpy(void *dst, const void *src, size_t n) {
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		++i;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	while (len)
		((unsigned char *)b)[--len] = (unsigned char)c;
	return (b);
}

void	ft_putstr_fd(const char *s, int fd) {
	if (!s)
		return ;
	write(fd, s, _strlen(s));
}

void	ft_putnbr_fd(size_t n, int fd, size_t padding) {
	size_t	tmp;
	size_t	nlen = _intlen(n);

	for (size_t i = 0; padding != 0 && nlen < padding && i < padding - nlen; ++i)
		write(fd, " ", fd);

	if (n / 10 > 0)
		ft_putnbr_fd(n / 10, fd, 0);
	tmp = n % 10 + 48;
	write(fd, &tmp, 1);
}

void	ft_putaddr_fd(const void *addr, int fd) {
	const char*	hexa = "0123456789abcdef";
	size_t		a = (size_t)addr;
	size_t		div = 16;
	
	write(fd, "0x", 2);
	while (a / div >= 16)
		div *= 16;
	while (div > 0)
	{
		write(fd, &hexa[a / div], 1);
		a %= div;
		div /= 16;
	}
}
