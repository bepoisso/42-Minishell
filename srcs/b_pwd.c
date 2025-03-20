#include "../includes/minishell.h"

int	builtin_pwd(t_base *base)
{
	char buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
		return(1);
	ft_putendl_fd(buff, 1);
	base->exit_code = 0;
	return (0);
}