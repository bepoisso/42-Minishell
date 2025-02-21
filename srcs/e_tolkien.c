#include "../includes/minishell.h"

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
static int	**create_pipe(t_base *base)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = NULL;
	base->count_pipe = count_pipe(base);
	pipes = ft_calloc(base->count_pipe, sizeof(int *));
	while (i < base->count_pipe)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			return (free_n_tabint(pipes, i + 1), NULL);
		i++;
	}
	i = 0;
	while (i < base->count_pipe)
	{
		if (pipe(pipes[i]) == -1)
			return (free_n_tabint(pipes, base->count_pipe),
				perror("Error : Creating pipe\n"), NULL);
		i++;
	}
	return (pipes);
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

	base->pipes = create_pipe(base);
	base->path_list = extract_paths();
	base->count_forks = count_forks(base);
	actual_cmd = base->cmds;
	tok = base->token;
	while (tok)
	{
		/* if (tok->id >= 3 && tok->id <= 6)
			printf("") */
			//file_redir();
		if (tok && tok->id == 9)
			prepare_exec(actual_cmd, tok, base);
		tok = tok->next;
	}
	close_fds(-1, 1, 1, base);
	wait_rings(base);
	//free_cmd_list(base->cmds);
	//free_token_list(base->token);
	return (0);
}
