#include "../includes/minishell.h"

/* char **env_cpy(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (ft_strslen(environ) + 1));
	while (environ[i])
	{
		if(ft_strncmp(environ[i], "SHLVL", 5) == 0)
			new_env[i] = shlvl_modifier(environ, i);
		else
			new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
} */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

char	*xtract_name(char *data)
{
	char	*name;
	int		size;

	size = 0;
	while (data && data[size] != '=')
		if (data[size])

	return (name);
}

void	env_cpy(t_var *)
{
	extern char	**environ;
	char		*data;
	t_var		*envir;
	t_var		*actual;
	int			size;
	int			i;

	size = ft_strslen(environ);
	envir = NULL;
	actual = NULL;
	if (size)
		envir = ft_calloc(1, sizeof(t_var *));
	i = 0;
	while (environ[i])
	{
		actual = ft_calloc(1, sizeof(t_var));
		if(ft_strncmp(environ[i], "SHLVL", 5) == 0)
			data = shlvl_modifier(environ, i);
		else
			data = ft_strdup(environ[i]);
		actual->content = data;
		actual->name = xtract_name(data);
		ft_lstadd_front(&envir, actual);
		i++;
	}
	return (new_env);
}


char **convert_envir(t_var *envir)
{

}