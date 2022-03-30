/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:51 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 03:39:34 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_alone(int f1, int f2, char *arg)
{
	int		child;
	char	**paths;
	char	**cmd_arg;

	paths = parsing(g_envp);
	cmd_arg = split_arg(arg, ' ');
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	child = fork();
	if (child == 0)
		exec(cmd_arg, paths);
}

void	pipex(int f1, int f2, char **argv, int index)
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	int		f[2];

	f[0] = f1;
	f[1] = f2;
	paths = parsing(g_envp);
	cmd1 = split_arg(argv[index], ' ');
	cmd2 = split_arg(argv[index + 1], ' ');
	if (!paths | !cmd1 | !cmd2)
		return (free_all(cmd1, cmd2, paths));
	pipex2(f, paths, cmd1, cmd2);
}

void	pipex2(int f[2], char **paths, char **cmd1, char **cmd2)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(end) == -1)
		exit_error(cmd1, cmd2, paths);
	child1 = fork();
	if (child1 < 0)
		exit_error(cmd1, cmd2, paths);
	if (child1 == 0)
		child_one(f[0], end, cmd1, paths);
	waitpid(child1, &status, 0);
	child2 = fork();
	if (child2 < 0)
		exit_error(cmd1, cmd2, paths);
	if (child2 == 0)
		child_two(f[1], end, cmd2, paths);
	free_all(cmd1, cmd2, paths);
	close(end[0]);
	close(end[1]);
	//waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
