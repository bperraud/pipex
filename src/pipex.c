/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:51 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 17:20:19 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_alone(int f1, int f2, char* arg)
{
	int	status;
	int	child;
	char **paths;
	char **cmd_arg;

	paths = parsing(g_envp);				// all path
	cmd_arg = ft_split(arg, ' ');			// cmd 1 args { "ls", "-la", NULL }	
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	child = fork();
    if (child < 0)
		return (perror("Fork: "));
    if (child == 0)
		exec(cmd_arg, paths);	
	waitpid(child, &status, 0); 	 // supervising the children	
}

void	pipex(int f1, int f2, char** argv, int index)
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;

	paths = parsing(g_envp);				// all path
	cmd1 = ft_split(argv[index], ' ');			// cmd 1 args { "ls", "-la", NULL }	
	cmd2 = ft_split(argv[index+1], ' ');			// cmd 2 args
	if (!paths | !cmd1 | !cmd2)
		return (free_all(cmd1, cmd2, paths));
	pipex2(f1, f2, paths, cmd1, cmd2);
}

void	wait_proccess(pid_t child1, pid_t child2, int end[2])
{
	int	status;

	close(end[0]);         		     // this is the parent
    close(end[1]);        			 // doing nothing
    waitpid(child1, &status, 0); 	 // supervising the children
    waitpid(child2, &status, 0); 	 // while they finish their tasks
}

void	pipex2(int f1, int f2, char** paths, char **cmd1, char **cmd2)
{
	int		end[2];
    pid_t	child1;
    pid_t	child2;

	if (pipe(end) == -1)
		exit_error(cmd1, cmd2, paths, "Pipe: ");
    child1 = fork();
    if (child1 < 0)
		exit_error(cmd1, cmd2, paths, "Fork: ");
    if (child1 == 0)
		child_one(f1, end, cmd1, paths);
    child2 = fork();
    if (child2 < 0)
		exit_error(cmd1, cmd2, paths, "Fork: ");
    if (child2 == 0)
		child_two(f2, end, cmd2, paths);
	free_all(cmd1, cmd2, paths);
	wait_proccess(child1, child2, end);
}

void	child_one(int f1, int end[2], char **cmd_arg, char **paths)
{

	if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		perror("Dup: ");
		exit(EXIT_FAILURE);
	}
	close(end[0]);
	exec(cmd_arg, paths);
	exit(EXIT_SUCCESS);
}

void	child_two(int f2, int end[2], char **cmd_arg, char **paths)
{
	if (dup2(end[0], STDIN_FILENO) < 0 || dup2(f2, STDOUT_FILENO) < 0)
	{
		perror("Dup: ");
		exit(EXIT_FAILURE);
	}
	close(end[1]);
	exec(cmd_arg, paths);
	exit(EXIT_SUCCESS);
}

void	exec(char **cmd_arg, char **paths)
{
	int 	i;
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
		execve(cmd, cmd_arg, g_envp); // if execve succeeds, it exits	
		free(cmd);
	}
	ft_putstr_fd("-bash: ", 2);
	ft_putstr_fd(cmd_arg[0], 2);
	ft_putstr_fd(":  command not found\n", 2);
}
