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

void	child_one(int f1, int end[2], char **cmd_arg, char **paths)
{
	if (f1 < 0)
		exit(EXIT_SUCCESS);
	if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		free_tab(cmd_arg);
		free_tab(paths);
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
		free_tab(cmd_arg);
		free_tab(paths);
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
			free_tab(cmd_arg);
			free_tab(paths);
			return ;
		}
		execve(cmd, cmd_arg, g_envp);
		free(cmd);
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(128);
}
