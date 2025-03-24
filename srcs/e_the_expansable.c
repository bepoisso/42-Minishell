#include "../includes/minishell.h"

/**
* typedef struct s_token
* {
* 	int				id;
* 	char			*data;
* 	struct s_cmd	*cmd;
* 	bool			literal;
* 	struct s_base	*base;
* 	struct s_token	*next;
* 	struct s_token	*prev;
* }	t_token;
* 
* typedef struct s_dollar
* {
* 	char	*name;
* 	char	*data;
* 	bool	literal;
* 	struct s_dollar *prev;
* 	struct s_dollar *next;
* }	t_dollar;
* 
* exemples:
* SAISIE : echo """'$USER'"""blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* ou
* SAISIE : echo "'$USER'"blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* AFFICHE : 'zeph'blablablablablabla$USERblablabla
* mais 
* 
* SAISIE : echo ""'$USER'""blablabla"$PLOP"blablabla'$USER'b""labla"bla"
* AFFICHE : $USERblablablablablabla$USERblablabla
* $USER '$USER' "$USER" "'$USER'" "'"$USER"'Je suis un argument"
* echo 'Bonjour '$USER' Je suis un argument de $USER pas "'$USER'"'
*/

static int	search_dol(const char *s, int i)
{
	if (!s)
		return (-2);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}
