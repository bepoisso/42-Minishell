
#include "../includes/minishell.h"

/**
 * si export sans argument, afichage de env dans l'ordre ascii
 * declare -x COLORTERM="truecolor"
 * 
 */

/* 
char	*change_value(char **env, char **old_data, char *new_data)
{
	int		i;
	char	*temp;
	char	*data;

	i = ft_strlen(name) + 1;
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	data = search_data_in_env(env, "OLDPWD")
		if (data)

	*old_data -= i;
	free_null((void **)old_data);
	*old_data = ft_strjoin(temp, new_data);
	free_null((void **)&temp);
	return (NULL);
}

/**
 * 
 * 
 * export sans argument affiche env dans ordre acsii en utilisant strcmp et un bubble sort ou quicksort
 * export A ajoute une variable A vide en env
 * export A="plop" ajoute une variable contenant Plop
 * 
 */
void	builtin_export(t_token *actual_tok)
{
	(void)actual_tok;
}