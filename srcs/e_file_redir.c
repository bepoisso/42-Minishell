#include "../includes/minishell.h"


/** Modifier fonction filechk pour prendre en compte les >> et <<
 * dans ces deux cas l'ouverture est differente pour ecrire a partir de la fin
 * dans le cas de >> et lire jusqu'au delimiteur dans le cas << 
 * utiliser l'optin de open O_APPEND
 * 
 * exemple de commande casse couille a gerer :
 * cat < input.txt > outfile.txt
 * donc dans le cas un infile ou outfile apres, il faut aussi regarder si il 
 * y en a un autre apres car en l'etat je ne regarde que les commandes
 */
int	file_redir(t_token *tok, t_base *base)
{
	int	fd;

	if (tok->id == 3)
	{
		fd = filechk(tok->data, 1, base);
		if (fd < 0)
			return (1);
		//dup2()
	}
	else if (tok->id == 5)
	{
		fd = filechk(tok->data, 1, base);
		if (fd < 0)
			return (1);
	}
	else if (tok->id == 4)
	{
		fd = filechk(tok->data, 2, base);
		if (fd < 0)
			return (1);
	}
	else if (tok->id == 6)
	{
		fd = filechk(tok->data, 2, base);
		if (fd < 0)
			return (1);
	}
	return(0);
}
