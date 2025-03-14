

#include "../includes/minishell.h"


/**			CONSTRUCTION PLAN
 * 
 * for command :  cd new
 * 1 -> Backup pwd to change oldpwd inside env after all checks
 * 2 -> check nb of args :
 * 		if == 0 : Go to HOME
 * 		if == 1 : 
 * 			if new = - : Go to HOME
 * 			else : Go to New
 * 		if >  1 : Error bash: cd: too many arguments RETURN
 * 
 * 3 -> Change pwd to New
 * 		if no error :
 * 			Update env:
 * 				1 : oldpwd = backup PWD
 * 				2 : pwd = new
 * 		if error :
 * 			Print: Error bash: cd: geth: No such file or directory RETURN
 * 
 */

int	check_args(char **args, t_base *base)
{

}

int	updt_env(char *new, t_base *base)
{

}
 
void	builtin_cd(t_base *base, t_token *actual_tok)
{
	(void)base;
	(void)actual_tok;




}