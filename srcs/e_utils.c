#include "../includes/minishell.h"

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
			i++;
	}
	return (i);
}

char	*ft_strnjoin(char *str, ...)
{
	char	*full_message;
	char	*va_tmp;
	char	*tmp;
	va_list	message_lst;

	full_message = NULL;
	va_tmp = NULL;
	tmp = NULL;
	va_start(message_lst, str);
	full_message = ft_strdup(str);
	if (!full_message)
		return (NULL);
	va_tmp = va_arg(message_lst, char *);
	while (va_tmp != NULL)
	{
		free_null((void **)&tmp);
		tmp = ft_strjoin(full_message, va_tmp);
		free_null((void **)&full_message);
		full_message = ft_strdup(tmp);
		va_tmp = va_arg(message_lst, char *);
	}
	free_null((void **)&tmp);
	va_end(message_lst);
	return (full_message);
}

char	*ft_strdup_protected(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (dest == NULL)
		return (dest);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
