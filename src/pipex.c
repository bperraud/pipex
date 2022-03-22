/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:51 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 00:52:59 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipe_alone(int f1, int f2, char* arg)
{
	int	status;

	dup2(f1, STDIN_FILENO);
    dup2(f2, STDOUT_FILENO);

    char **paths = parsing(g_envp);				// all path
    char **cmd_arg = ft_split(arg, ' ');			// cmd 1 args { "ls", "-la", NULL }	
    
	int child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        exec(cmd_arg, paths);
	waitpid(child1, &status, 0); 	 // supervising the children	
}

void	pipex(int f1, int f2, char** argv, int index)
{
	int		end[2];
    int		status;
    pid_t	child1;
    pid_t	child2;

	char	**paths;
	char	**cmd1;
	char	**cmd2;

	paths = parsing(g_envp);				// all path
	cmd1 = ft_split(argv[index], ' ');			// cmd 1 args { "ls", "-la", NULL }	
	cmd2 = ft_split(argv[index+1], ' ');			// cmd 2 args
	if (!paths | !cmd1 | !cmd2)
		return (free_all(cmd1, cmd2, paths));

	pipe(end);  // a proteger

    child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, end, cmd1, paths);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, end, cmd2, paths);

    close(end[0]);         		     // this is the parent
    close(end[1]);        			 // doing nothing
    waitpid(child1, &status, 0); 	 // supervising the children
    waitpid(child2, &status, 0); 	 // while they finish their tasks
}

void	child_one(int f1, int end[2], char **cmd_arg, char **paths)
{
	if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		perror("dup issue\n");
		return ;
	}
	close(end[0]);
	exec(cmd_arg, paths);
	exit(EXIT_SUCCESS);
}

void	child_two(int f2, int end[2], char **cmd_arg, char **paths)
{
	if (dup2(end[0], STDIN_FILENO) < 0 || dup2(f2, STDOUT_FILENO) < 0)
	{
		perror("dup issue\n");
		return ;
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
			return (free(cmd));
		}
		execve(cmd, cmd_arg, g_envp); // if execve succeeds, it exits	
		free(cmd);
	}
}

void	free_all(char **cmd1, char **cmd2, char **path)
{
	free_tab(cmd1);
	free_tab(cmd2);
	free_tab(path);
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return ;
}
