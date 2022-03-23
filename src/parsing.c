/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 15:10:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	**parsing(char **envp)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split = ft_split(str, ':');
	free(str);
	return (split);
}

char	*create_path(char *path, char *arg)
{
	char	*cmd;
	char	*temp;

	temp = ft_strjoin(path, "/");
	cmd = ft_strjoin(temp, arg);
	free(temp);
	return (cmd);
}

/*
	copy f1 content into f2
*/
void	copy_file(int f1, int f2)
{
	char	*str;

	if (f1 < 0 || f2 < 0)
		return ;
	str = get_next_line(f1);
	while (str)
	{
		write(f2, str, ft_strlen(str));
		free(str);
		str = get_next_line(f1);
	}
}
