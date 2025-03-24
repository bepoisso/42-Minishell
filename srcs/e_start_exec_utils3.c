#include "../includes/minishell.h"

static void	messages_heredeoc(int hrdoc_size, char *data)
{
	ft_putstr_fd("minishell: warning: here-document at line \n", 2);
	ft_putnbr_fd(hrdoc_size, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd("')\n", 2);
}

int	open_hrdoc_file(void)
{
	int	fd;

	fd = open(HRDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_putstr_fd("Error opening file", 2);
	return (fd);
}

char	*read_heredoc_input(t_token *tokens)
{
	char	*line;

	line = strdup(" ");
	if (!line)
		return (NULL);
	while (line && ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
	{
		free_null((void **)&line);
		line = readline(BLUE">"RESET);
		if (!line)
			messages_heredeoc(0, tokens->data);
	}
	return (line);
}

int	process_heredoc_input(char *line, t_token *tokens, int fd)
{
	int	hrdoc_size;

	hrdoc_size = 0;
	while (line && ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
	{
		if (write(fd, line, ft_strlen(line)) < 0)
			return (free_null((void **)&line), close(fd), -1);
		if (write(fd, "\n", 1) < 0)
			return (close(fd), -1);
		hrdoc_size += ft_strlen(line);
		free_null((void **)&line);
		line = readline(BLUE">"RESET);
		if (!line)
			messages_heredeoc(hrdoc_size, tokens->data);
	}
	return (hrdoc_size);
}

int	handle_hrdoc_no_cmd(t_token *tokens, t_base *base)
{
	int		fd;
	char	*line;
	int		hrdoc_size;

	fd = open_hrdoc_file();
	if (fd < 0)
		return (-1);
	line = read_heredoc_input(tokens);
	if (!line)
		return (close(fd), -1);
	hrdoc_size = process_heredoc_input(line, tokens, fd);
	close(fd);
	free_null((void **)&line);
	base->input = add_in_command(base);
	return (0);
}

/* int	handle_hrdoc_no_cmd(t_token *tokens, t_base *base)
{
	char	*line;
	int		fd;
	int		hrdoc_size;

	line = NULL;
	hrdoc_size = 0;
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
			messages_heredeoc(hrdoc_size, tokens->data);
		else if (line[0] == '\0' || ft_strncmp(line, tokens->data
				, ft_strlen(tokens->data) + 1))
		{
			if (write(fd, line, ft_strlen(line)) < 0)
				return (free_null((void **)line), close(fd), -1);
			if (write(fd, "\n", 1) < 0)
				return (close(fd), -1);
			hrdoc_size += ft_strlen(line);
		}
	}
	close(fd);
	free_null((void **)&line);
	base->input = add_in_command(base);
	return (0);
} */