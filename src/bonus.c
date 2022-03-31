/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/31 02:23:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus.h"
#include "../include/pipex.h"
#include "../include/get_next_line_bonus.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	if (argc < 5)
		return (-1);
	g_envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0 && argc == 6)
	{
		f1 = limiter(argv[2]);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		pipex(f1, f2, argv, 3);
		unlink(FILE_NAME);
	}
	else
	{
		f1 = open_file(argv[1]);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		pipex(f1, f2, argv, 2);
		multiple_cmd(f2, argc, argv);
	}
	close(f1);
	return (0);
}
