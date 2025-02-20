#include "../includes/minishell.h"

int	file_redir(t_cmd *actual_cmd, t_token *tok, t_base *base)
{
	int	fd;

	if (tok->id == 3 && filechk(tok->next->data, 1, base) == 1)
	{
		fd = 
		return (free_doubletab(&base->path_list), 1);
	}
	else if (tok->id == 5 && filechk(tok->next->data, 1, base) == 1)
	{
		return (free_doubletab(&base->path_list), 1);
	}
	else if (tok->id == 4 && filechk(tok->next->data, 2, base) == 1)
	{
		return (free_doubletab(&base->path_list), 1);
	}
	else if (tok->id == 6 && filechk(tok->next->data, 2, base) == 1)
	{
		return (free_doubletab(&base->path_list), 1);
	}
}
