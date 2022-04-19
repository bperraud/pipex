/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/19 19:50:13 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus.h"
#include "../include/pipex.h"
#include "../include/get_next_line_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	int fd[2];

	if (argc < 4)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0 && argc == 6)
	{
		f1 = limiter(argv[2]);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);

		//pipex(f1, f2, argv, 3);
		unlink(FILE_NAME);
	}
	else
	{
		fd[0] = open_file(argv[1]);
		fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		multiple_cmd(fd, argc, argv, envp);
	}
	close(f1);
	return (0);
}
