/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/21 17:38:28 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	**parsing(char **envp)
{
	int		i;
	//char	**cmd_args;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	return (ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':'));
}

char	*create_path(char *path, char *arg)
{
	char	*cmd;
	char	*temp;

	temp = ft_strjoin(path, "/"); 	 // add "/" for each path + cmd1
	cmd = ft_strjoin(temp, arg); 	 // add "/" for each path + cmd1
	free(temp);
	return (cmd);
}

void	copy_file(int f1, int f2)
{
	char	*str;

	str = get_next_line(f1);
	while (str)
	{
		write(f2, str, ft_strlen(str));
		free(str);
		str = get_next_line(f1);
	}
}


void	delete_file(char *file, char **envp)
{
	char	**paths;
	int		i;
	char	*cmd;
	pid_t	child;

	child = fork();
    if (child < 0)
         return (perror("Fork: "));

	//char	**cmd_arg = { "rm", file, NULL};  
     
	if (child == 0)
    {
		paths = parsing(envp);
		i = -1;
		while (paths[++i])
		{
            printf("cmdpaths : %s\n", paths[i]);    

			cmd = create_path(paths[i], "rm");
            char	*cmd_arg[] =  {cmd, file, NULL}; 

            printf("cmd : %s\n", cmd);
            perror("child\n");
			execve(cmd, cmd_arg, envp);
			free(cmd);
		}
        exit(EXIT_FAILURE);	
	}
}
