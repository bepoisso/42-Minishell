#include "../includes/minishell.h"

void	messages_heredeoc(int hrdoc_size, char *data)
{
	ft_putstr_fd("minishell: warning: here-document at line \n", 2);
	ft_putnbr_fd(hrdoc_size, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd("')\n", 2);
}
