/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:41:40 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:27:56 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	get_size_of_int(long n)
{
	int		count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	long	nb;

	nb = n;
	i = get_size_of_int(nb);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		dest[0] = '-';
	}
	dest[i--] = '\0';
	if (nb == 0)
		dest[i] = '0';
	while (nb > 0)
	{
		dest[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (dest);
}
