/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:18:07 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:27:32 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr_base(unsigned long nb, char *base)
{
	unsigned int			size_base;
	int						count;

	count = 0;
	size_base = ft_strlen(base);
	if (nb >= size_base)
		count += ft_putnbr_base(nb / size_base, base);
	count += ft_putchar(base[nb % size_base]);
	return (count);
}

int	ft_print_hexa(unsigned long nb, int status)
{
	if (status)
		return (ft_putnbr_base(nb, "0123456789abcdef"));
	return (ft_putnbr_base(nb, "0123456789ABCDEF"));
}

int	ft_print_ptr(void *ptr)
{
	int	count;

	count = 0;
	if (!(size_t)ptr)
		count += ft_putstr("(nil)");
	else
	{
		count += ft_putstr("0x");
		count += ft_print_hexa((unsigned long)ptr, 1);
	}
	return (count);
}
