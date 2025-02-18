#include "../includes/minishell.h"

//fonction qui va lire les tokens et lancer les fonction de redirection, execution....
void    start_exec(t_cmd *cmd)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	char    **cmd_path;

	cmd_path = NULL;
	cmd_path = extract_paths();
	if (!cmd_path)
		return ;
	cmd->path_cmd = check_cmd(cmd_path, cmd->cmd[0]);
	if (!cmd->path_cmd)
	{
		free_doubletab(&cmd_path);
		return ;
	}
	exec_cmd(cmd->path_cmd, cmd->cmd);
	free_null((void *)&cmd->path_cmd);
	free_doubletab(&cmd_path);
}