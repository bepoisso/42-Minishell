
#include "../includes/minishell.h"

/**
 * si export sans argument, afichage de env dans l'ordre ascii
 * declare -x COLORTERM="truecolor"
 * 
*/

/*static int	update_var(char *new_data, char ** env, int index)
{

	if (index >= 0)
	{
		free_null((void **)&env[index]);
		env[index] = ft_strjoin("PWD=",new_data);
		return (0);
	}
	else
	{
		env = add_var_in_env(env, new_data);
	}
	return (0);
}*/

int	namelen(char * arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*xtract_var_name(char *data)
{
	char	*name;
	int		i;

	i = 0;
	name = ft_calloc(namelen(data) + 1, sizeof(char));
	if (!name)
		return (ft_putstr_fd("Error: calloc", 2), NULL);
	while (data && data[i] && data[i] != '=')
	{
		name[i] = data[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static int	add_or_updt_var(t_token *tok, t_base *base)
{
	int		i;
	int		k;
	t_cmd	*act_cmd;
	char	*name;

	name = NULL;
	act_cmd = tok->cmd;
	k = 1;
	while (act_cmd->cmd && act_cmd->cmd[k])
	{
		name = xtract_var_name(act_cmd->cmd[k]);
		i = search_var_in_env(base->env, name);
		free_null((void **)&name);
		if (i >= 0)
		{
			free_null((void **)&base->env[i]);
			base->env[i] = ft_strdup(act_cmd->cmd[k]);
			if (!base->env[i])
				return (ft_putstr_fd("Error : strdup env\n", 2), -1);
		}
		else
			base->env = add_var_in_env(base->env, ft_strdup(act_cmd->cmd[k]));
		k++;
	}
	return (0);
}

/**
 * export sans argument affiche env dans ordre acsii en utilisant strcmp et un bubble sort ou quicksort
 * export A ajoute une variable A vide en env
 * export A="plop" ajoute une variable contenant Plop
 * ft_put_arraystr
*/
int	builtin_export(t_token *actual_tok)
{
	if (ft_strslen( actual_tok->cmd->cmd) > 1)
	{
		if (add_or_updt_var(actual_tok, actual_tok->base) != 0)
			return (1);
	}
	else
		put_xport(actual_tok->base->env);
	return(0);
}
