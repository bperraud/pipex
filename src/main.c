/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/24 01:05:38 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	if (argc < 5)
		return (-1);
	g_envp = envp;
	main2(i, argc, argv);
	return (0);
}

void	main2(int i, int argc, char **argv)
{
	int	f1;
	int	f2;
	int	f3;

	f1 = open_file(argv[1], READ);
	f2 = open_file(argv[argc - 1], CREATE);
	pipex(f1, f2, argv, i);
	while (i < argc - 3)
	{
		i += 2;
		f3 = open_file(FILE_NAME, CREATE);
		f2 = open_file(argv[argc - 1], READ);
		copy_file(f2, f3);
		f2 = open_file(argv[argc - 1], CREATE);
		f3 = open_file(FILE_NAME, READ);
		if ((argc % 2 == 0) && (i == argc - 2))
			pipex_alone(f3, f2, argv[i]);
		else
			pipex(f3, f2, argv, i);
	}
	close(f1);
	close(f2);
	close(f3);
	unlink(FILE_NAME);
}
