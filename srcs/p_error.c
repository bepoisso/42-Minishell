#include "../includes/minishell.h"

/** Modif par jrinaudo de t_base base en *base pour modifier 
*  base->exit_code dans la base, pas la copie  */
void	ft_error(char *s, int code, t_base *base)
{
	if (!(code == -1))
		base->exit_code = code;
	ft_putstr_fd(s, 2);
	// A SUPPRE
	ft_printf("\nexit code = %d\n", base->exit_code);
}
