
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**				b_builtins.c */
int		exec_builtins(t_token *actual);

int		builtin_env(t_token *actual_tok);
int		builtin_pwd(t_base *base);
int		builtin_echo(t_token *actual_tok);

/**				b_export.c */
int		builtin_export(t_token *actual_tok);

/**				b_cd.c */
int		cd_dot(t_base *base);
int		ft_strslen(char **array);
int		builtin_cd(t_token *actual_tok, t_base *base);

/**				b_cd_utils1.c */
char	*error_message(char *str, ...);

/**				b_cd_utils2.c */

/**				b_unset.c */
int		builtin_unset(t_token *actual_tok);

#endif