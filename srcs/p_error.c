#include "../includes/minishell.h"

void	ft_error(char *s, int code, t_base *base)
{
	base->exit_code = code;
	ft_putstr_fd(s, 2);
	/*	A supprimer	*/
	if (base != NULL)
		ft_printf("\nexit code = %d\n", base->exit_code);
	/*			 */
	free_base(base);
	if (getpid() == 0)
		exit (base->exit_code);
}
