
#include "../includes/minishell.h"

static int	handle_hrdoc_no_cmd(t_token *tokens, t_base *base)
{
	char	*line;
	int		fd;
	int		hrdoc_size;

	line = NULL;
	hrdoc_size = 0;
	fd = open(HRDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	line = strdup(" ");
	if (!line)
		return (-1);
	while (line && ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
	{
		free_null((void **)&line);
		line = readline(BLUE">"RESET);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document at line \n", 2);
			ft_putnbr_fd(hrdoc_size, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(tokens->data, 2);
			ft_putstr_fd(")\n", 2);
		}
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
}

static int	file_chk_no_command(t_token *token, int type, t_base *base)
{
	int		fd;
	char	*file;

	if (token)
		file = token->data;
	else
		return (ft_error("Minishell: syntax error near unexpected token\n", 1, base)
			, -1);
	fd = 0;
	if (type == 3)
		fd = open(file, O_RDONLY, 0644);
	if (type == 5)
		handle_hrdoc_no_cmd(token, token->base);
	else if (type == 4)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 6)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && errno == EACCES)
		ft_error("Permission denied\n", 1, base);
	if (fd == -1 && errno == ENOENT)
		ft_error("No such file or directory\n", 1, base);
	return (fd);
}

int	handle_redirec_alone(t_token *token)
{
	t_token	*actual;
	int		fd;

	actual = token;
	fd = 0;
	while(actual && actual->prev && actual->prev->id != 7)
		actual = actual->prev;
	while (actual && actual->id != 7)
	{
		if (actual->id >= 3 && actual->id <= 6)
			fd = file_chk_no_command(actual->next, actual->id, actual->base);
		if (fd > 0)
		{
			close(fd);
			fd = 0;
		}
		actual = actual->next;
	}
	return (0);
}