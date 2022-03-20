/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 03:41:55 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

	cmd = ft_strjoin(path, "/"); 	 // add "/" for each path + cmd1
	// free ici	
	cmd = ft_strjoin(cmd, arg); 	 // add "/" for each path + cmd1

	return (cmd);
}

void	copy_file(int f1, int f2)
{
	char	*str;

	str = ft_strdup(" ");
	while (!str)
	{
		free(str);
		str = get_next_line(f1);
		write(f2, str, ft_strlen(str));
	}
}
