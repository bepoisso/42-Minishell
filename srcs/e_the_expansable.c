/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_the_expansable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:26:29 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/20 14:07:06 by jrinaudo         ###   ########.fr       */
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

static	int	proceed_expanse(t_token *act_tok, t_dollar *act_dol, int dol_begin,  )
{
	int		i_new;

	i_new = 0;
	while (i_new < dol_begin)
	{
		new_data[i_new] = act_tok->data[i_new];
		i_new++;
	}
	
	while (act_dol->data[i_dol])
	{
		new_data[i_new] = act_dol->data[i_dol];
		i_new++;
		i_dol++;
	}
	new_data[i_new] = '\0';
}

static t_dollar	*the_expanse(t_token *act_tok, t_dollar *act_dol, int dol_begin)
{
	char	*new_data;
	int		new_len;
	int		dol_end;
	//int		i_new;
	int		i_dol;
			
	new_data = NULL;
	new_len = 0;
	dol_end = dol_begin + 1;
	i_new = 0;
	i_dol = 0;
	while (act_tok->data[dol_end] && !is_delim(act_tok->data[dol_end]))
		dol_end ++;
	new_len = (ft_strlen(act_tok->data) - dol_end) + ft_strlen(act_dol->data);
	new_data = ft_calloc(new_len + 1, sizeof(char));
	while (i_new < dol_begin)
	{
		new_data[i_new] = act_tok->data[i_new];
		i_new++;
	}
	
	while (act_dol->data[i_dol])
	{
		new_data[i_new] = act_dol->data[i_dol];
		i_new++;
		i_dol++;
	}
	new_data[i_new] = '\0';
	act_dol->next;

	return (act_dol);
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