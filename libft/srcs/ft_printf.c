/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:16:56 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:28:39 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	check_format(char format, va_list ap)
{
	int	count;

	count = 0;
	if (format == '%')
		count += ft_putchar('%');
	else if (format == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (format == 'u')
		count += ft_put_unsigned_nbr(va_arg(ap, unsigned int));
	else if (format == 'x')
		count += ft_print_hexa(va_arg(ap, unsigned int), 1);
	else if (format == 'X')
		count += ft_print_hexa(va_arg(ap, unsigned int), 0);
	else if (format == 'p')
		count += ft_print_ptr(va_arg(ap, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
			count += check_format(*(++str), ap);
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (count);
}
