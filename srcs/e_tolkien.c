#include "../includes/minishell.h"

/**----------------------------------------------------------------------------
 * sauron veille sur ses precieux anneaux
 * je gere seulement les pipes....desole je n'avance pas bien vite :p
 * mais, il y a un mais, je pense les gerer bien car il n'y a aucune
 *  fuite memoire, et tous les fd sont ferme...il y en a un petit paquet
 *  pourtant.
 * j'ai demade au chat de me faire un jolie main, il a bien assure, donc en 
 * theorie, il te suffit dans ton main, d'invoquer Sauron et hop
 * je m'occuperai des redir le weekend prochain, ou en rentrant
 *---------------------------------------------------------------------------*/
/**
 * @brief Counts the number of pipes in the token list and updates the pipe
 *  indices.
 *
 * This function iterates through the linked list of tokens in the base
 *  structure,
 * counts the number of tokens with an ID of 7 (representing pipes),
 *  and updates
 * the pipe index for each pipe token. The total count of pipes is stored
 *  in the base structure.
 *
 * @param base Pointer to the base structure containing the token list and
 *  pipe count.
 * @return The total number of pipes found in the token list.
 */
static int	count_pipe(t_base *base)
{
	t_token	*tokencpy;

	base->count_pipe = 0;
	tokencpy = base->token;
	while (tokencpy)
	{
		if (tokencpy->id == 7)
		{
			tokencpy->index_pipe = base->count_pipe;
			base->count_pipe++;
		}
		tokencpy = tokencpy->next;
	}
	return (base->count_pipe);
}

/*FONCTION SAURON
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		>>		redir outfile append
7		|		pipe
8		$		variable
9		cmd		commande
10		args	commande args */
/**
 * @brief Creates an array of pipes for inter-process communication.
 *
 * This function allocates memory for an array of pipes based on the number of
 * pipes required, which is determined by the count_pipe function. Each pipe
 * is represented as an array of two integers. The function initializes each
 * pipe and handles any errors that occur during the allocation or creation
 * process.
 *
 * @param base A pointer to the t_base structure which contains the necessary
 *             information for pipe creation, including the number of pipes.
 *
 * @return A pointer to the array of pipes on success, or NULL on failure.
 *         In case of failure, the function also frees any allocated memory
 *         and prints an error message.
 */
static void	create_pipe(t_base *base)
{
	int	i;

	i = 0;
	base->count_pipe = count_pipe(base);
	base->pipes = ft_calloc(base->count_pipe, sizeof(int *));
	while (i < base->count_pipe)
	{
		base->pipes[i] = ft_calloc(2, sizeof(int));
		if (!base->pipes[i])
		{
			free_n_tabint(base->pipes, i + 1);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < base->count_pipe)
	{
		if (pipe(base->pipes[i]) == -1)
		{
			free_n_tabint(base->pipes, base->count_pipe);
			perror("Error : Creating pipe\n");
			return ;
		}
		i++;
	}
}

//A AJOUTER DANS LE PARSER
/**if (base->token->id == 7)
*si la commande commence par un | rien ne se fait A AJOUTER AU PARSING
*		return (free_exec(base), 
ft_error("bash: syntax error near unexpected token `|'", 2, base), 1);
message a afficher dans ce cas
*/
int	sauron(t_base *base)
{
	t_cmd	*actual_cmd;
	t_token	*tok;

	create_pipe(base);
	base->path_list = extract_paths();
	base->count_forks = count_forks(base);
	actual_cmd = base->cmds;
	tok = base->token;
	while (tok)
	{
		/* if (tok->id == 8)
			handle_env(actual_cmd, tok, base); */
		if (tok && tok->id == 9)
			prepare_exec(actual_cmd, tok, base);
		tok = tok->next;
	}
	close_fds(-1, 1, 1, base);
	wait_rings(base);
	return (0);
}
