#include "../includes/minishell.h"

void	messages_heredeoc(int hrdoc_size, char *data)
{
	ft_putstr_fd("minishell: warning: here-document at line \n", 2);
	ft_putnbr_fd(hrdoc_size, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd("')\n", 2);
}

int	handle_hrdoc_no_cmd(t_token *tokens, t_base *base)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(HRDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("Error openin file", 2), -1);
	line = strdup(" ");
	if (!line)
		return (-1);
	while (line && ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
	{
		free_null((void **)&line);
		line = readline(BLUE">"RESET);
		if (!line)
			messages_heredeoc(base->hrdoc_size, tokens->data);
		else if (line[0] == '\0' || ft_strncmp(line, tokens->data
				, ft_strlen(tokens->data) + 1))
		{
			if (write(fd, line, ft_strlen(line)) < 0)
				return (free_null((void **)line), close(fd), -1);
			if (write(fd, "\n", 1) < 0)
				return (close(fd), -1);
			base->hrdoc_size += ft_strlen(line);
		}
	}
	close(fd);
	free_null((void **)&line);
	base->input = add_in_command(base);
	return (0);
}