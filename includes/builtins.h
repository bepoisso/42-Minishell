
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**				b_builtins.c */
int		exec_builtins(t_token *actual);

int		builtin_env(t_token *actual_tok);
int		builtin_pwd(t_base *base);
void	builtin_echo(t_base *base, t_token *actual_tok);

/**				b_export.c */
int		builtin_export(t_token *actual_tok);

/**				b_cd.c */
int		ft_strslen(char **array);
int		builtin_cd(t_token *actual_tok, t_base *base);

/**				b_cd_utils1.c */
char	*error_message(char *str, ...);
int		go_back(t_base *base);
int		update_oldpwd(char *new_data, t_base *base);
int		update_pwd(char *new_data, t_base *base);
int		cd_dot(t_base *base);

/**				b_cd_utils2.c */
int		go_before(t_base *base);

/**				b_unset.c */
int		builtin_unset(t_token *actual_tok);

#endif