#include "../includes/minishell.h"

static void	sort_strtab(char **strtab)
{
	char	*tmp;
	int		i;
	int		last_i;


	tmp = NULL;
	i = 0;
	last_i = ft_strslen(strtab) - 1;
	while (i < last_i)
	{
		if (ft_strncmp(strtab[i], strtab[i + 1], namelen(strtab[i])) > 0)
		{
			tmp = strtab[i];
			strtab[i] = strtab[i + 1];
			strtab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	put_xport(char **env)
{
	int		i;
	char	*name;
	char	**sorted;

	i = 0;
	sorted = ft_calloc(ft_strslen(env) + 1, sizeof(char *));
	while (env[i])
	{
		sorted[i] = ft_strdup(env[i]);
		i++;
	}
	sorted[i] = NULL;
	i = 0;
	sort_strtab(sorted);
	while (sorted[i])
	{
		name = xtract_var_name(sorted[i]);
		if(search_data_in_env(env,name))
			ft_printf("declare -x %s=\"%s\"\n", name, search_data_in_env(env,name));
		else
			ft_printf("declare -x %s\n", name);
		free_null((void **)&name);
		i++;
	}
	free_doubletab(&sorted);
}
