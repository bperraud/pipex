/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:59:45 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/23 00:59:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	exit_error(char **cmd1, char **cmd2, char **path, char *error)
{
	free_all(cmd1, cmd2, path);
	perror(error);
	exit(EXIT_FAILURE);
}


void	free_all(char **cmd1, char **cmd2, char **path)
{
	free_tab(cmd1);
	free_tab(cmd2);
	free_tab(path);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
