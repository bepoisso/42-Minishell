/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:43:55 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:27:42 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int	*tab;

	tab = NULL;
	tab = malloc(nmemb * size);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, (size * nmemb));
	return ((void *)tab);
}
