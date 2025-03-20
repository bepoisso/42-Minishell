#include "../includes/minishell.h"

char	*error_message(char *str, ...)
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
	return (full_message);
}
