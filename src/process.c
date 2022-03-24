/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:58:18 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/24 00:58:18 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	wait_proccess(pid_t child1, pid_t child2, int end[2])
{
	int	status;

	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

void	child_one(int f1, int end[2], char **cmd_arg, char **paths)
{
	if (f1 < 0)
		exit(EXIT_SUCCESS);
	if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		perror("Dup: ");
		exit(EXIT_FAILURE);
	}
	close(end[0]);
	exec(cmd_arg, paths);
}

void	child_two(int f2, int end[2], char **cmd_arg, char **paths)
{
	if (f2 < 0)
		exit(EXIT_SUCCESS);
	if (dup2(end[0], STDIN_FILENO) < 0 || dup2(f2, STDOUT_FILENO) < 0)
	{
		perror("Dup: ");
		exit(EXIT_FAILURE);
	}
	close(end[1]);
	exec(cmd_arg, paths);
}

void	exec(char **cmd_arg, char **paths)
{
	int		i;
	char	*cmd;

	i = -1;
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd_arg[0]);
		if (!cmd)
		{
			perror("cannot allocate memory\n");
			return ;
		}
		execve(cmd, cmd_arg, g_envp);
		free(cmd);
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
