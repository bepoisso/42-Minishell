/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:28:35 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 12:28:46 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	substract_and_save(char **stash, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	*line = malloc(i + 2);
	if (!*line)
		return (free(*stash));
	ft_strlcpy(*line, *stash, i + 2);
	if ((*stash)[i] == '\n')
		i++;
	temp = ft_strdup(*stash + i);
	if (!temp)
		return (free(*line), free(*stash));
	free(*stash);
	*stash = temp;
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			readed;
	char		*line;
	static char	*stash;
	char		*temp_stash;

	line = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff || (fd < 0 || BUFFER_SIZE <= 0))
		return (free(buff), free(stash), stash = NULL, NULL);
	if (!stash)
		stash = ft_strdup("");
	while (line == NULL)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1 || (readed == 0 && stash[0] == '\0'))
			return (free(buff), free(stash), stash = NULL, NULL);
		buff[readed] = '\0';
		temp_stash = ft_strjoin(stash, buff);
		free(stash);
		stash = temp_stash;
		if (ft_strchr(stash, '\n') || readed == 0)
			substract_and_save(&stash, &line);
	}
	return (free(buff), line);
}
