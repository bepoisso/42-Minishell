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
	t_token	*actual;

	actual = tok;
	if (actual->id == 3 || actual->id == 5)
	{
		fd = filechk(actual->next, actual->id, base);
		if (fd < 0)
			return (1);
	}
	if (actual->id == 4 || actual->id == 6)
	{
		fd = filechk(actual->next, actual->id, base);
		if (fd < 0)
			return (1);
	}
	return (0);
}
