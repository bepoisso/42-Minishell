/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_the_expansable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:26:29 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/20 12:31:44 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
* typedef struct s_token
* {
* 	int				id;
* 	char			*data;
* 	struct s_cmd	*cmd;
* 	bool			literal;
* 	struct s_base	*base;
* 	struct s_token	*next;
* 	struct s_token	*prev;
* }	t_token;
* 
* typedef struct s_dollar
* {
* 	char	*name;
* 	char	*data;
* 	bool	literal;
* 	struct s_dollar *prev;
* 	struct s_dollar *next;
* }	t_dollar;
* 
* exemples:
* SAISIE : echo """'$USER'"""blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* ou
* SAISIE : echo "'$USER'"blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* AFFICHE : 'zeph'blablablablablabla$USERblablabla
* mais 
* 
* SAISIE : echo ""'$USER'""blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* AFFICHE : $USERblablablablablabla$USERblablabla
* $USER '$USER' "$USER" "'$USER'" "'"$USER"'Je suis un argument"
* echo 'Bonjour '$USER' Je suis un argument de $USER pas "'$USER'"'
*/

static int	search_dol(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

static int	is_delim(char c)
{
	if (c == ' ' || c == '\'' || c == '"' || c == '$')
		return (1);
	else if (!ft_isalnum(c))
		return (1);
	return(0);
}

static	int	apply_expanse(t_token *act_tok, t_dollar *act_dol, int index,  )
{
	expanse_len = (ft_strlen(act_tok->data) - index) + ft_strlen(act_dol->data);
	new_data = ft_calloc(expanse_len + 1, sizeof(char));
	while (index2 < i)
	{
		new_data[index2] = act_tok->data[index2];
		index2++;
	}
	index = 0;
	while (act_dol->data[index])
	{
		new_data[index2] = act_dol->data[index];
		index2++;
		index++;
	}
	new_data[index2] = '\0';
}


static t_dollar	*the_expanse(t_token *act_tok, t_dollar *act_dol, int i)
{
	char	*new_data;
	int		expanse_len;
	int		index;
	int		index2;
			
	new_data = NULL;
	expanse_len = 0;
	index = i + 1;
	index2 = 0;
	while (act_tok->data[index] && !is_delim(act_tok->data[index]))
		index ++;
	
	return (act_dol->next);
}

int	apply_expanse(t_base *base)
{
	t_token		*act_tok;
	t_dollar	*act_dol;
	int			found_dol;

	act_tok = base->token;
	act_dol = base->dollars;
	found_dol = 1;
	while (act_tok && act_dol)
	{
		found_dol = search_dol(act_tok->data);
		if (found_dol > 0)
			act_dol = the_expanse(act_tok, act_dol, found_dol);
		act_tok = act_tok->next;
	}
}