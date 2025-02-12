/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:18:11 by bepoisso          #+#    #+#             */
/*   Updated: 2024/08/29 14:28:12 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

int	ft_printf(const char *str, ...);
int	check_format(char format, va_list ap);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_put_unsigned_nbr(unsigned int n);
int	ft_print_hexa(unsigned long nb, int status);
int	ft_putnbr_base(unsigned long nbr, char *base);
int	ft_print_ptr(void *ptr);

#endif
