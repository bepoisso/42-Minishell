#include "../includes/minishell.h"

char	*add_in_history(t_token *tokens, char *line)
{
	t_token	*actual;
	char 	*cmd;
	char	*tmp;

	actual = tokens;
	cmd = NULL;
	tmp = ft_strdup(actual->data);
	while (actual->prev)
		actual = actual->prev;
	while (actual->next)
	{
		free_null((void **)&cmd);
		cmd = ft_strjoin(tmp, actual->data);
		free(tmp);
		actual = actual->next;
	}
	free_null((void **)&cmd);
//A terminer avec l'ajout du fichier temporaire
	cmd = ft_strjoin(tmp, actual->data);
}


static int handle_hrdoc(t_token *tokens, t_cmd *cmd)
{
	char	*line;
	int		fd;
	int		hrdoc_size;

	line = NULL;
	hrdoc_size = 0;
	if (cmd->hrdoc)
		close(cmd->hrdoc);
	fd = open(HRDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	line = strdup(" ");
	if (!line)
		return(-1);
	while (line[0] && ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
	{
		free_null((void **)&line);
		line = readline(BLUE">"RESET);
		if (line[0] == '\0')
		{
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			ft_putnbr_fd(hrdoc_size, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(tokens->data, 2);
			ft_putstr_fd("\n", 2);
		}

		if (ft_strncmp(line, tokens->data, ft_strlen(tokens->data) + 1))
		{
			if (write(fd, line, ft_strlen(line)) < 0)
				return(free_null((void **)line), close(fd), -1);
			if (write(fd, "\n", 1) < 0)
				return(close(fd), -1);
			hrdoc_size += ft_strlen(line);
		}
	}
	cmd->hrdoc = fd;
	//add_history(add_in_history);
	free_null((void **)&line);
	close(fd);
	return (fd);
}

/**
 * Gestion des erreurs a faire, renvoyer un numero de fd utnique a chaque defaut
 * les messages voint etre gere par une fonction externe, depuis le processus
 * parent
 * 
 * print_error recois le massage, la commande en cause et la base
 */
int	filechk(t_token *token, int type, t_base *base, t_cmd *cmd)
{
	int		fd;
	char	*file;

	if (token)
		file = token->data;
	else
		return (ft_error("bash: syntax error near unexpected token\n", 1, base)
			, -1);
	fd = 0;
	if (type == 3)
		fd = open(file, O_RDONLY);
	if (type == 5)
	{
		if(handle_hrdoc(token, cmd) < 0)
			return (-1);
		fd = open(HRDOC_FILE, O_RDONLY);
	}
	else if (type == 4)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 6)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && errno == EACCES)
		return (ft_error("Permission denied\n", 1, base), -1);
	if (fd == -1 && errno == ENOENT)
		return (ft_error("No such file or directory\n", 1, base), -1);
	return (fd);
}

