#include "../includes/minishell.h"

int	should_skip_update(char *cmd, char *name, t_base *base)
{
	int	i;

	if (check_xport_arg(cmd, name, base))
	{
		return (1);
	}
	i = search_var_in_env(base->env, name);
	if (i > 0 && search_equal(cmd) < 0)
	{
		return (1);
	}
	return (0);
}

int	update_existing_var(char *cmd, char *name, t_base *base)
{
	int	i;

	i = search_var_in_env(base->env, name);
	if (i >= 0)
	{
		free_null((void **)&base->env[i]);
		base->env[i] = ft_strdup(cmd);
		if (!base->env[i])
		{
			ft_putstr_fd("Error : strdup env\n", 2);
			return (-1);
		}
		return (0);
	}
	return (-1);
}

int	add_new_var(char *cmd, t_base *base)
{
	char	*duplicated_data;

	duplicated_data = ft_strdup(cmd);
	if (!duplicated_data)
	{
		ft_putstr_fd("Error : strdup env\n", 2);
		return (-1);
	}
	base->env = add_var_in_env(base->env, duplicated_data);
	return (0);
}

static int	add_or_updt_var(t_token *tok, t_base *base, int k)
{
	t_cmd	*act_cmd;
	char	*name;

	name = NULL;
	act_cmd = tok->cmd;
	while (act_cmd->cmd && act_cmd->cmd[k])
	{
		free_null((void **)&name);
		name = xtract_var_name(act_cmd->cmd[k]);
		if (should_skip_update(act_cmd->cmd[k], name, base))
		{
			k++;
			continue ;
		}
		if (update_existing_var(act_cmd->cmd[k], name, base) == 0)
		{
			k++;
			continue ;
		}
		if (add_new_var(act_cmd->cmd[k], base) != 0)
			return (-1);
		k++;
	}
	free_null((void **)&name);
	return (0);
}
// static int	add_or_updt_var(t_token *tok, t_base *base, int k)
// {
// 	int		i;
// 	t_cmd	*act_cmd;
// 	char	*name;

// 	name = NULL;
// 	act_cmd = tok->cmd;
// 	while (act_cmd->cmd && act_cmd->cmd[k])
// 	{
// 		free_null((void **)&name);
// 		name = xtract_var_name(act_cmd->cmd[k]);
// 		if (check_xport_arg(act_cmd->cmd[k], name, base))
// 		{
// 			k++;
// 			continue ;
// 		}
// 		i = search_var_in_env(base->env, name);
// 		if (i > 0 && search_equal(act_cmd->cmd[k]) < 0)
// 		{
// 			k++;
// 			continue ;
// 		}
// 		if (i >= 0)
// 		{
// 			free_null((void **)&base->env[i]);
// 			base->env[i] = ft_strdup(act_cmd->cmd[k]);
// 			if (!base->env[i])
// 				return (ft_putstr_fd("Error : strdup env\n", 2), -1);
// 		}
// 		else
// 			base->env = add_var_in_env(base->env, ft_strdup(act_cmd->cmd[k]));
// 		k++;
// 	}
// 	free_null((void **)&name);
// 	return (0);
// }

int	builtin_export(t_token *actual_tok)
{
	if (actual_tok->base->cmds->prev || actual_tok->base->cmds->next)
		return (0);
	if (ft_strslen(actual_tok->cmd->cmd) > 1)
	{
		if (add_or_updt_var(actual_tok, actual_tok->base, 1) != 0)
			return (1);
	}
	else
		put_xport(actual_tok->base->env);
	return (0);
}
