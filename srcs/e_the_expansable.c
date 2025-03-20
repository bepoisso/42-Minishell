/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_the_expansable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:26:29 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/20 10:32:28 by jrinaudo         ###   ########.fr       */
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
*  $USER '$USER' "$USER" "'$USER'" '"$USER"'

*/

static int	the_expanse(t_token *act_tok, t_dollar *act_dol)
{

}


int	apply_expanse(t_base *base)
{
	t_token		*act_tok;
	t_dollar	*act_dol;

	act_tok = base->token;
	act_dol = base->dollars;
	while (act_tok)
	{
		if (ft_strchr(act_tok->data, '#'))
		{
			the_expanse(act_tok, act_dol);
			act_dol = act_dol->next;
		}
		act_tok = act_tok->next;
	}
}