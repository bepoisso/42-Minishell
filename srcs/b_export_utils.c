#include "../includes/minishell.h"

static void	put_error(t_base *base, char *name)
{
	ft_putstr_fd(RED"Minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier"RESET, 2);
	ft_putstr_fd("\n", 2);
	base->exit_code = 1;
}

int	check_xport_arg(char *cmd, char *name, t_base *base)
{
	int	i;

	i = 0;
	if (ft_isdigit(cmd[0]))
		return (put_error(base, name), 1);
	while (cmd[i] && cmd[i] != '=')
	{
		if (!is_ok(cmd[i]))
			return (put_error(base, name), 1);
		else
			base->exit_code = 0;
		i++;
	}
	return (base->exit_code);
}

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

static char	**dup_s_tab(char **stab)
{
	char		**new_env;
	int			i;

	i = 0;
	new_env = ft_calloc((ft_strslen(stab) + 1), sizeof(char *));
	while (stab[i])
	{
		new_env[i] = ft_strdup(stab[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	put_xport(char **env)
{
	int		i;
	char	*name;
	char	**sorted;

	i = 0;
	sorted = dup_s_tab(env);
	sort_strtab(sorted);
	while (sorted[i])
	{
		if (sorted[i][0] != '\0')
		{
			name = xtract_var_name(sorted[i]);
			if (search_data_in_env(env, name))
				ft_printf("declare -x %s=\"%s\"\n", name,
					search_data_in_env(env, name));
			else if (ft_strchr(sorted[i], '='))
				ft_printf("declare -x %s=""\n", name);
			else
				ft_printf("declare -x %s\n", name);
			free_null((void **)&name);
		}
		i++;
	}
	free_doubletab(&sorted);
}
