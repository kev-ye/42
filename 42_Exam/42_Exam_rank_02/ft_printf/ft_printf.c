/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:09:39 by kaye              #+#    #+#             */
/*   Updated: 2021/01/21 00:09:55 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

static long ft_abs(long i)
{
    return ((i < 0)? -i : i);
}

static int conv(int i)
{
    if (i < 0)
        i = ft_abs(i);
    if (i < 10)
        return (i + '0');
    else
        return (i - 10 + 'a');
}

static int int_len(int i, int base)
{
    int count;

    count = 0;
    if (i == 0)
        count = 1;
    while (i != 0)
    {
        i /= base;
        ++count;
    }
    return (count);
}

static int uint_len(unsigned int i, int base)
{
    int count;

    count = 0;
    if (i == 0)
        count = 1;
    while (i != 0)
    {
        i /= base;
        ++count;
    }
    return (count);
}

static char *ft_itoa_base(long i, int base)
{
    char *s;
    int len;
    long tmp_i;

    tmp_i = i;
    len = int_len(i, base);
    if (i < 0)
        len++;
    s = malloc(sizeof(char) * (len + 1));
    if (!s)
        return (NULL);
    s[len] = '\0';
    while (len--)
    {
        s[len] = conv(i % base);
        i /= base;
    }
    if (tmp_i < 0)
        s[0] = '-';
    return (s); 
}

static char *ft_uitoa_base(unsigned int i, int base)
{
    char *s;
    int len;

    len = uint_len(i, base);
    s = malloc(sizeof(char) * (len + 1));
    if (!s)
        return (NULL);
    s[len] = '\0';
    while (len--)
    {
        s[len] = conv(i % base);
        i /= base;
    }
    return (s); 
}

size_t ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        ++i;
    return (i);
}

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *s)
{
    int len;

    len = ft_strlen(s);
    write(1, s, len);
    return (len);
}

int ft_putstr_prec(char *s, int prec)
{
    int i;

    i = 0;
    while (s[i] && i < prec)
    {
        ft_putchar(s[i++]);
    }
    return (i);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int parse_s(char *s, int width, int prec)
{
    int count;
    int len;

    count = 0;
    if (!s)
        s = "(null)";
    len = ft_strlen(s);
    if (prec < 0)
    {
        if (width)
            width -= len;
        while (width > 0)
        {
            count += ft_putchar(' ');
            width--;
        }
        count += ft_putstr(s);
    }
    else if (prec >= 0)
    {
        if (prec > len)
            prec = len;
        if (width)
            width -= prec;
        while (width > 0)
        {
            count += ft_putchar(' ');
            width--;
        }
        count += ft_putstr_prec(s, prec);
    }
    return (count);
}

int parse_d(long i, int width, int prec)
{
    char *s;
    int count;
    int len;
    int tmp_i;

    count = 0;
    len = 0;
    tmp_i = i;
    i = ft_abs(i);
    s = ft_itoa_base(i, 10);
    len = ft_strlen(s);
    if (prec < 0)
    {
        if (width)
            width -= len;
        if (tmp_i < 0)
            width--;
        while (width > 0)
        {
            count += ft_putchar(' ');
            width--;
        }
        if (tmp_i < 0)
        {
            count += ft_putchar('-');
        }
        count += ft_putstr(s);
    }
    else if (prec >= 0)
    {
        if (i == 0 && prec == 0)
        {
            while (width > 0)
            {
                count += ft_putchar(' ');
                --width;
            }
            return (count);
        }
        if (prec > len)
            prec -= len;
        else
            prec = 0;
        width -= prec + len;
        if (tmp_i < 0)
        {
            width--;
        }
        while (width > 0)
        {
            count += ft_putchar(' ');
            --width;
        }
        if (tmp_i < 0)
        {
            count += ft_putchar('-');
        }
        while (prec > 0)
        {
            count += ft_putchar('0');
            --prec;
        }
        count += ft_putstr(s);
    }
    free(s);
    return (count);
}

int parse_x(unsigned int i, int width, int prec)
{
    char *s;
    int count;
    int len;

    count = 0;
    len = 0;
    s = ft_uitoa_base(i, 16);
    len = ft_strlen(s);
    if (prec < 0)
    {
        if (width)
            width -= len;
        while (width > 0)
        {
            count += ft_putchar(' ');
            width--;
        }
        count += ft_putstr(s);
    }
    else if (prec >= 0)
    {
        if (i == 0 && prec == 0)
        {
            while (width > 0)
            {
                count += ft_putchar(' ');
                --width;
            }
            return (count);
        }
        if (prec > len)
            prec -= len;
        else
            prec = 0;
        width -= prec + len;
        while (width > 0)
        {
            count += ft_putchar(' ');
            --width;
        }
        while (prec > 0)
        {
            count += ft_putchar('0');
            --prec;
        }
        count += ft_putstr(s);
    }
    free(s);
    return (count);
}

int process(const char *format, va_list arg)
{
    int count;
    int i;
    int width;
    int prec;

    i = 0;
    count = 0;
    width = 0;
    prec = -1;
    while (format[i])
    {
        width = 0;
        prec = -1;
        if (format[i] == '%')
        {
            i++;
            while (ft_isdigit(format[i]))
            {
                width = width * 10 + format[i] - '0';
                i++;
            }
            if (format[i] == '.')
            {
                prec = 0;
                i++;
                while (ft_isdigit(format[i]))
                {
                    prec = prec * 10 + format[i] - '0';
                    i++;
                }
            }
            if (format[i] == 's')
            {
                count += parse_s(va_arg(arg, char *), width, prec);
            }
            else if ((format[i] == 'd'))
            {
                count += parse_d(va_arg(arg, int), width, prec);
            }
            else if ((format[i] == 'x'))
            {
                count += parse_x(va_arg(arg, unsigned int), width, prec);
            }           
        }
        else
           count += ft_putchar(format[i]);
        ++i; 
    }
    return (count);
}

int ft_printf(const char *format, ...)
{
    va_list arg;
    int i = 0;

    va_start(arg, format);
    i = process(format, arg);
    va_end(arg);
    return (i);
}