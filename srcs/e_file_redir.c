#include "../includes/minishell.h"

/** Modifier fonction filechk pour prendre en compte les >> et <<
 * dans ces deux cas l'ouverture est differente pour ecrire a partir de la fin
 * dans le cas de >> et lire jusqu'au delimiteur dans le cas << 
 * utiliser l'optin de open O_APPEND
 * 
 * exemple de commande casse couille a gerer :
 * cat < input.txt > GESTION OK
 * cat < input.txt > outfile.txt GESTION OK
 * donc dans le cas un infile ou outfile apres, il faut aussi regarder si il 
 * y en a un autre apres car en l'etat je ne regarde que les commandes
 */
int	file_redir(t_token *tok, t_base *base)
{
	int		fd;
	t_token	*tmp;

	tmp = tok;
	if (tmp->id == 3 || tmp->id == 5)
	{
		write(2,"redir in detected\n", 18);
		fd = filechk(tmp->next, tmp->id, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (tmp->id == 4 || tmp->id == 6)
	{
		write(2,"redir out detected\n", 19);
		fd = filechk(tmp->next, tmp->id, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

/* int	file_redir(t_token *tok, t_base *base)
{
	int	fd;
	int	fd;
	t_token	*tmp;

	tmp = tok;
	if (tmp->id == 3)
	{
		fd = filechk(tmp->next, 1, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
	}
	else if (tmp->id == 5)
	{
		fd = filechk(tmp->next, 1, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
	}
	if (tmp->id == 4)
	{
		fd = filechk(tmp->next, 2, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
	}
	else if (tmp->id == 6)
	{
		fd = filechk(tmp->next, 3, base);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
	}
	return(0);
} */
