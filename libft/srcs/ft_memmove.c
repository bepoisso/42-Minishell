/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:36:30 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:28:31 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dest;
	int				i;

	if (!src && !dest)
		return ((void *)dest);
	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	if (src < dest && src + n > dest)
	{
		i = n;
		while (--i >= 0)
			ptr_dest[i] = ptr_src[i];
	}
	else
	{
		i = -1;
		while (++i < (int)n)
			ptr_dest[i] = ptr_src[i];
	}
	return ((void *)dest);
}
