#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include "../includes/minishell.h"
 int	what_before(t_token *act_tok, t_base *base, int i);
 int	what_after(t_token *act_tok, t_base *base, int i);/**
 * Struct for the token
 * j'ai ajoute index_pipe ca va m'aider a gerer naviguer dans le tableau de
 * pipes, comme ca qund je navigue dans la liste et que j'arrive sur un pipe,
 *  je sais comment le gerer avec le tableau de pipes
*/

void test_what_before()
{
	t_token token1 = { .id = 3, .prev = NULL };
	t_token token2 = { .id = 4, .prev = &token1 };
	t_token token3 = { .id = 7, .prev = &token2 };
	t_base base;
	int pipes[2][2];
	base.pipes = malloc(sizeof(int *) * 2);
	base.pipes[0] = malloc(sizeof(int) * 2);
	base.pipes[1] = malloc(sizeof(int) * 2);
	base.pipes_index = 0;
	base.count_pipe = 2;

	pipe(base.pipes[0]);
	pipe(base.pipes[1]);

	int result = what_before(&token3, &base, 1);
	assert(result == 1);

	close(base.pipes[0][0]);
	close(base.pipes[0][1]);
	close(base.pipes[1][0]);
	close(base.pipes[1][1]);
}

void test_what_after()
{
	t_token token1 = { .id = 3, .next = NULL };
	t_token token2 = { .id = 4, .next = &token1 };
	t_token token3 = { .id = 7, .next = &token2 };
	t_base base;
	int pipes[2][2];
	base.pipes = malloc(sizeof(int *) * 2);
	base.pipes[0] = malloc(sizeof(int) * 2);
	base.pipes[1] = malloc(sizeof(int) * 2);
	base.pipes_index = 0;
	base.count_pipe = 2;

	pipe(base.pipes[0]);
	pipe(base.pipes[1]);

	int result = what_after(&token3, &base, 1);
	assert(result == 1);

	close(base.pipes[0][0]);
	close(base.pipes[0][1]);
	close(base.pipes[1][0]);
	close(base.pipes[1][1]);
}

void test_close_fds()
{
	t_base base;
	int pipes[2][2];
	base.pipes = malloc(sizeof(int *) * 2);
	base.pipes[0] = malloc(sizeof(int) * 2);
	base.pipes[1] = malloc(sizeof(int) * 2);
	base.pipes_index = 0;
	base.count_pipe = 2;

	pipe(base.pipes[0]);
	pipe(base.pipes[1]);

	close_fds(-1, 1, 1, &base);

	assert(close(base.pipes[0][0]) == -1);
	assert(close(base.pipes[0][1]) == -1);
	assert(close(base.pipes[1][0]) == -1);
	assert(close(base.pipes[1][1]) == -1);
}

void test_prepare_exec()
{
	t_token token = { .id = 3, .prev = NULL, .next = NULL };
	t_cmd cmd;
	t_base base;
	int pipes[2][2];
	base.pipes = malloc(sizeof(int *) * 2);
	base.pipes[0] = malloc(sizeof(int) * 2);
	base.pipes[1] = malloc(sizeof(int) * 2);
	base.pipes_index = 0;
	base.count_pipe = 2;

	pipe(base.pipes[0]);
	pipe(base.pipes[1]);

	int result = prepare_exec(&cmd, &token, &base);
	assert(result == 0);

	close(base.pipes[0][0]);
	close(base.pipes[0][1]);
	close(base.pipes[1][0]);
	close(base.pipes[1][1]);
}

int main()
{
	test_what_before();
	test_what_after();
	test_close_fds();
	test_prepare_exec();

	printf("All tests passed!\n");
	return 0;
}