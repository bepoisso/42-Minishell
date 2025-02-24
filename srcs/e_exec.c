#include "../includes/minishell.h"

/**
 * @brief Extracts and formats PATH environment variable into an array of paths
 * 
 * This function gets the PATH environment variable, splits it into individual
 *  paths,
 * and adds a trailing slash to each path.
 * 
 * @return char** Array of paths with trailing slashes, NULL if:
 *                - PATH environment variable is not found
 *                - Memory allocation fails
 *                - Split operation fails
 * 
 * @note The returned array must be freed by the caller
 * @note Each path in the returned array ends with a '/' character
 */
char	**extract_paths(void)
{
	char	*env;
	char	**env_list;
	char	*env_listcpy;
	int		i;

	i = 0;
	env_list = NULL;
	env_listcpy = NULL;
	env = getenv("PATH");
	if (!env)
		return (NULL);
	env_list = ft_split(env, ':');
	if (!env_list)
		return (NULL);
	while (env_list[i])
	{
		env_listcpy = ft_strjoin(env_list[i], "/");
		if (!env_listcpy)
			return (free_doubletab(&env_list), NULL);
		free_null((void *)&env_list[i]);
		env_list[i] = env_listcpy;
		i++;
	}
	return (env_list);
}
