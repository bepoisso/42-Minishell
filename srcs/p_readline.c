#include "../includes/minishell.h"

char	*generate_prompt_base(void)
{
	char	*temp;
	char	*result;
	char	*temp2;

	temp = ft_strjoin(YELLOW_BOLD"╭─ "VIOLET_BOLD, "minishell "YELLOW_BOLD);
	result = ft_strdup(temp);
	free(temp);
	temp = ft_strdup(YELLOW_BOLD"► ");
	temp2 = ft_strdup(result);
	free(result);
	result = ft_strjoin(temp2, temp);
	free(temp);
	free(temp2);
	return (result);
}

char	*append_path_and_user(char *result, char **env, t_base *base)
{
	char	path[PATH_MAX];
	char	*temp;
	char	*temp2;
	char	*user;

	getcwd(path, sizeof(path));
	user = search_env_var("USER", env, base);
	temp = ft_strjoin(path, " ["VIOLET_BOLD);
	temp2 = ft_strdup(result);
	free(result);
	result = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	temp = ft_strjoin(user, YELLOW_BOLD"] 🤏🐚\n");
	temp2 = ft_strdup(result);
	free(result);
	result = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	free(user);
	return (result);
}

char	*minitext_rl(char **env, t_base *base)
{
	char	*result;
	char	*temp;
	char	*temp2;

	result = generate_prompt_base();
	result = append_path_and_user(result, env, base);
	temp = ft_strjoin("╰─", VIOLET_BOLD"➤ "RESET);
	temp2 = ft_strdup(result);
	free(result);
	result = ft_strjoin(temp2, temp);
	free(temp2);
	free(temp);
	return (result);
}
