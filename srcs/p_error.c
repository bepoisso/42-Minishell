#include "../includes/minishell.h"

void	ft_error(char *s, int code, t_base base)
{
	if (!(code == -1))
		base.exit_code = code;
	ft_putstr_fd(s, 2);
	// A SUPPRE
	ft_printf("\nexit code = %d\n", base.exit_code);
}
