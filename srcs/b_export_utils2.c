#include "../includes/minishell.h"

int	is_ok(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	namelen(char *arg)
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

int	search_equal(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-2);
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
