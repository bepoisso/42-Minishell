/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinaudo <jrinaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:59:45 by jrinaudo          #+#    #+#             */
/*   Updated: 2025/03/18 13:55:45 by jrinaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**				b_builtins.c */
void	exec_builtins(t_token *actual);

void	builtin_env(t_token *actual_tok);
void	builtin_pwd(t_base *base);
void	builtin_echo(t_token *actual_tok);
//void	builtin_exit(t_base *base);

/**				b_export.c */
void	builtin_export(t_token *actual_tok);

/**				b_cd.c */
int		cd_dot(t_base *base);
int		ft_strslen(char **array);
int		builtin_cd(t_token *actual_tok, t_base *base);
//t_var	*search_in_var(t_var *var, char *search);

/**				b_unset.c */
int		builtin_unset(t_token *actual_tok);

#endif