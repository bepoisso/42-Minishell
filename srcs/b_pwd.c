#include "../includes/minishell.h"

void	builtin_pwd(t_base *base)
{
	char buff[4096];

	getcwd(buff, sizeof(buff));
	ft_putendl_fd(buff, 1);
	base->exit_code = 0;
}