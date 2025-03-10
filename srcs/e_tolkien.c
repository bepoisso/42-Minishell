#include "../includes/minishell.h"

/*FONCTION SAURON
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		>>		redir outfile append
7		|		pipe
8		$		variable
9		cmd		commande
10		args	commande args */

static int	cmd_before(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok->prev;
	while (actual && actual->id != 7)
	{
		if (actual->id == 9)
		{
			actual->cmd->output = fd;
		}
		actual = actual->prev;
	}
	return (0);
}

static int	cmd_after(t_token *tok, int fd)
{
	t_token	*actual;

	actual = tok->next;
	while (actual && actual->id != 7)
	{
		if (actual->id == 9)
		{
			actual->cmd->input = fd;
		}
		actual = actual->next;
	}
	return (0);
}

static void	create_redir(t_base *base)
{
	t_token	*actual;
	int		pipeline[2];

	actual = base->token;
	while (actual)
	{
		if (actual->id == 7)
		{
			if (pipe(pipeline) < 0)
				exit(1);
			cmd_before(actual, pipeline[1]);
			cmd_after(actual, pipeline[0]);
		}
		actual = actual->next;
	}
}

static void	handle_cmd(t_token *tok, t_base *base)
{
	t_token	*actual;
	t_cmd	*actual_cmd;

	actual = tok;
	actual_cmd = base->cmds;
	while (actual)
	{
		if (actual->id == 9)
		{
			actual->cmd = actual_cmd;
			actual->cmd->input = 0;
			actual->cmd->output = 1;
			actual->cmd->pid = 0;
			actual_cmd = actual_cmd->next;
		}
		else
			actual->cmd = NULL;
		actual = actual->next;
	}
}

/*Leak dans ft_spilt??
 ==37438== 269 (104 direct, 165 indirect) bytes in 1 blocks are definitely lost in loss record 31 of 80
==37438==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==37438==    by 0x10BCBA: ft_split (in /home/zeph/Documents/Project42/42-Minishell/minishell)
==37438==    by 0x109854: extract_paths (e_exec.c:31)
==37438==    by 0x10A29E: sauron (e_tolkien.c:102)
==37438==    by 0x10B3EE: main (p_main.c:38)
==37438== 
{
   <insert_a_suppression_name_here>
   Memcheck:Leak
   match-leak-kinds: definite
   fun:malloc
   fun:ft_split
   fun:extract_paths
   fun:sauron
   fun:main
} 
   
==37438== 165 bytes in 12 blocks are indirectly lost in loss record 28 of 80
==37438==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==37438==    by 0x10BB02: ft_strjoin (in /home/zeph/Documents/Project42/42-Minishell/minishell)
==37438==    by 0x109895: extract_paths (e_exec.c:36)
==37438==    by 0x10A29E: sauron (e_tolkien.c:102)
==37438==    by 0x10B3EE: main (p_main.c:38)
==37438== 
{
   <insert_a_suppression_name_here>
   Memcheck:Leak
   match-leak-kinds: indirect
   fun:malloc
   fun:ft_strjoin
   fun:extract_paths
   fun:sauron
   fun:main
}

==37438== 8 bytes in 1 blocks are definitely lost in loss record 3 of 80
==37438==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==37438==    by 0x10B1F8: parsing_cmd (p_cmd.c:94)
==37438==    by 0x10B3D2: main (p_main.c:31)
==37438== 
{
   <insert_a_suppression_name_here>
   Memcheck:Leak
   match-leak-kinds: definite
   fun:malloc
   fun:parsing_cmd
   fun:main
}


*/



int	sauron(t_base *base)
{
	t_token				*tok;
	/* struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, NULL); */
	tok = base->token;
	handle_cmd(tok, base);
	create_redir(base);
	base->count_forks = count_forks(base);
	base->path_list = extract_paths();
	while (tok)
	{
	/* 	if (tok->id == 8)
			handle_env(actual_cmd, tok, base); */
		if (tok->id == 9)
			prepare_exec(tok, base);
		tok = tok->next;
	}
	wait_rings(base);
	return (0);
}
