/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:48:39 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/05/13 19:47:50 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	unsigned int	i;
	unsigned int	count;
	va_list			args;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_format(format, &i, args);
		}
		else
			count += ft_putchar(format[i++]);
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	char letter = 'H';
	char *str = "sdhSUhdUSD";

	ft_printf("[abcd]\n");
	ft_printf("[%c]\n", letter);
	ft_printf("[%s]\n", str);
	ft_printf("[%%]\n");
	ft_printf("[%d]\n", 42);
	ft_printf("[%i]\n", 2147483649);
}*/

/*
c = prints single caracter
s = prints a string
p = the void * point argument has to be printed in hexadecimal
d = prints a decimal (base 10) number.
i = prints a integer in base 10.
u = prints an unsigned decimal base 10 number.
x = prints a number in hexadecimal base 16 lower case format
X = prints a number in hexadecimal base 16 uppercase format.
% = prints a percent sign
*/
/*
Manage any combination of the following flags: ’-0.’ and the field minimum width
under all conversions
Manage all the following flags: ’# +’ (Yes, one of them is a space)
*/
