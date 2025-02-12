/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:53:48 by bepoisso          #+#    #+#             */
/*   Updated: 2024/11/12 10:30:59 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//__________DEFINE__________
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
//____________________

//__________INCLUDE__________
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
//____________________

//__________FUNC__________
char	*get_next_line(int fd);
void	substract_and_save(char **stash, char **line);
//____________________

#endif
