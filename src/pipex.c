/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:51 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/21 17:08:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		return (free_all());


	printf("cmd 1 :%s\n", cmd1[0]);		
	printf("cmd 2 :%s\n", cmd2[0]);	
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

void	child_one(int f1, int end[2], char **cmd1, char **paths)
{
	int 	i;
	char	*cmd;

	//if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)			// we want f1 to be execve() input and end[1] to be execve() stdout
		//return (free_all());

	dup2(f1, STDIN_FILENO); 		// we want f1 to be execve() input
	dup2(end[1], STDOUT_FILENO); 	// we want end[1] to be execve() stdout	
	close(end[0]);
	close(f1);
	
	i = -1;
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd1[0]);
		if (!cmd)
			return (free_all());			 // perror("Error"); <- add perror to debug
		execve(cmd, cmd1, g_envp);
		perror("1 ");
		/*
		if (execve(cmd, cmd1, g_envp) > 0) // if execve succeeds, it exits	
		{
			perror("fonctionne");
			free(cmd);
			free_all(cmd); 
			break;
		}	
		*/
		free(cmd);					// if execve fails, we free and we try a new path
	}
	exit(EXIT_FAILURE);
}


void	child_two(int f2, int end[2], char **cmd2, char **paths)
{
	int		status;
	int 	i;
	char	*cmd;
	// dup2 close stdin, f1 becomes the new stdin
	
	//if (dup2(f1, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)			// we want f1 to be execve() input and end[1] to be execve() stdout
		//return (free_all());

	dup2(f2, STDOUT_FILENO); 				// we want f2 to be execve() stdout	
	dup2(end[0], STDIN_FILENO); 			// we want end[1] to be execve() input
	close(end[1]);
	close(f2);

	i = -1;
	while (paths[++i])
	{
		cmd = create_path(paths[i], cmd2[0]);
		if (!cmd)
			return (free_all());			 // perror("Error"); <- add perror to debug

		execve(cmd, cmd2, g_envp);

		perror("2 ");
		free(cmd);					// if execve fails, we free and we try a new path
	}
}


void	free_all()
{
	return ;
}
