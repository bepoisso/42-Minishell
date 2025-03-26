#include "../includes/minishell.h"

char	*add_in_command(t_base *base)
{
	char	*line;
	char	*hrdoc;
	int		fd;

	fd = open(HRDOC_FILE, O_RDONLY, 0644);
	hrdoc = get_next_line(fd);
	if (!hrdoc)
		return (close(fd), base->input);
	line = ft_strjoin(base->input, "\n");
	if (!line)
		return (close(fd), NULL);
	free_null((void **)&base->input);
	base->input = line;
	while (hrdoc)
	{
		line = ft_strjoin(base->input, hrdoc);
		if (!line)
			return (close(fd), NULL);
		free_null((void **)&hrdoc);
		free_null((void **)&base->input);
		base->input = line;
		hrdoc = get_next_line(fd);
	}
	close(fd);
	return (base->input);
}

static t_here	*init_hrdoc(void)
{
	t_here	*hrdoc;

	hrdoc = ft_calloc(1, sizeof(t_here));
	hrdoc->line = NULL;
	hrdoc->fd = open(HRDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hrdoc->fd < 0)
		return (NULL);
	hrdoc->line = strdup("");
	if (!hrdoc->line)
		return (close(hrdoc->fd), NULL);
	return (hrdoc);
}

static void	close_hrdoc(t_here *hrdoc)
{
	close(hrdoc->fd);
	free(hrdoc->line);
	free(hrdoc);
}

int	handle_hrdoc(t_token *tokens, t_base *base)
{
	t_here	*hrdoc;

	hrdoc = init_hrdoc();
	if (!hrdoc)
		return (-1);
	while (hrdoc->line && ft_strncmp(hrdoc->line, tokens->data,
			ft_strlen(tokens->data) + 1))
	{
		free_null((void **)&hrdoc->line);
		hrdoc->line = readline(BLUE">"RESET);
		if (!hrdoc->line)
			messages_heredeoc(base->hrdoc_size, tokens->data);
		else if (hrdoc->line[0] == '\0' || ft_strncmp(hrdoc->line, tokens->data
				, ft_strlen(tokens->data) + 1))
		{
			if (write(hrdoc->fd, hrdoc->line, ft_strlen(hrdoc->line)) < 0)
				return (free_null((void **)hrdoc->line), close(hrdoc->fd), -1);
			if (write(hrdoc->fd, "\n", 1) < 0)
				return (close(hrdoc->fd), -1);
			base->hrdoc_size += ft_strlen(hrdoc->line);
		}
	}
	close_hrdoc(hrdoc);
	return (0);
}

/* static int	handle_hrdoc(t_token *tokens, t_cmd *cmd, t_base *base)
{
	char	*line;
	int		fd;

	line = NULL;
	if (cmd->hrdoc)
		close(cmd->hrdoc);
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
	cmd->hrdoc = fd;
	close(fd);
	free_null((void **)&line);
	return (fd);
} */

int	filechk(t_token *token, int type, t_base *base, t_cmd *cmd)
{
	int		fd;

	(void)cmd;
	if (!token->data)
		return (ft_error("Minishell: syntax error near unexpected token\n", 1
				, base), -1);
	fd = 0;
	if (type == 3)
		fd = open(token->data, O_RDONLY, 0644);
	if (type == 5)
	{
		if (handle_hrdoc(token, base) < 0)
			return (-1);
		fd = open(HRDOC_FILE, O_RDONLY, 0644);
		base->input = add_in_command(base);
	}
	else if (type == 4)
		fd = open(token->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 6)
		fd = open(token->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && errno == EACCES)
		return (ft_error("Permission denied\n", 1, base), -1);
	if (fd == -1 && errno == ENOENT)
		return (ft_error("No such file or directory\n", 1, base), -1);
	return (fd);
}
