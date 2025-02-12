/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:23:59 by bepoisso          #+#    #+#             */
/*   Updated: 2024/12/19 14:13:18 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	word_count(char const *str, char c)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] != c && check == 0)
		{
			count++;
			check = 1;
		}
		else if (str[i] == c && check == 1)
			check = 0;
		i++;
	}
	return (count);
}

static int	ft_strllen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	free_2d_split(char **s, int index)
{
	while (index >= 0)
	{
		free(s[index]);
		index--;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		wc;

	i = 0;
	wc = word_count(s, c);
	strs = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!strs)
		return (NULL);
	while (i < wc)
	{
		while (*s == c)
			s++;
		strs[i] = malloc(sizeof(char) * ft_strllen(s, c) + 1);
		if (!strs[i])
		{
			free_2d_split(strs, i);
			return (NULL);
		}
		ft_strlcpy(strs[i], s, ft_strllen(s, c) + 1);
		s += ft_strllen(s, c) + 1;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
