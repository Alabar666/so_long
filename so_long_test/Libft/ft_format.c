/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:21:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/05/13 20:38:39 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_print_decimal(long int nb, int base, char flag)
{
	unsigned int	count;
	char			*symbols;

	symbols = "0123456789abcdef";
	if (flag == 'X')
		symbols = "0123456789ABCDEF";
	count = 0;
	if (nb < 0)
	{
		count += ft_putchar('-');
		return (ft_print_decimal(-nb, base, flag) + 1);
	}
	else if (nb < base)
		return (ft_putchar(symbols[nb]));
	else
	{
		count += ft_print_decimal(nb / base, base, flag);
		return (count + ft_print_decimal(nb % base, base, flag));
	}
	return (count);
}

static unsigned int	ft_print_p(size_t nb, size_t base, char flag)
{
	unsigned int	count;
	char			*symbols;

	symbols = "0123456789abcdef";
	count = 0;
	if (nb < base)
		return (ft_putchar(symbols[nb]));
	else
	{
		count += ft_print_decimal(nb / base, base, flag);
		return (count + ft_print_decimal(nb % base, base, flag));
	}
	return (count);
}

static unsigned int	ft_print_hexx0(size_t nb)
{
	unsigned int	count;

	count = 0;
	if (nb == 0)
		return (write(1, "(nil)", 5));
	count += ft_putstr("0x");
	count += ft_print_p(nb, 16, 'p');
	return (count);
}

int	ft_format(const char *format, unsigned int *i, va_list args)
{
	unsigned int	count;

	count = 0;
	if (format[*i] == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format[*i] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format[*i] == 'd' || format[*i] == 'i')
		count += ft_print_decimal(va_arg(args, int), 10, 'd');
	else if (format[*i] == 'x')
		count += ft_print_decimal(va_arg(args, unsigned int), 16, 'x');
	else if (format[*i] == 'X')
		count += ft_print_decimal(va_arg(args, unsigned int), 16, 'X');
	else if (format[*i] == 'u')
		count += ft_print_decimal(va_arg(args, unsigned int), 10, 'u');
	else if (format[*i] == 'p')
		count += ft_print_hexx0(va_arg(args, size_t));
	else if (format[*i] == '%')
		count += ft_putchar('%');
	(*i)++;
	return (count);
}
