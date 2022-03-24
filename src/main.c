/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/24 04:18:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (-1);
	g_envp = envp;
	start(2, argc, argv);
	return (0);
}

void	start(int i, int argc, char **argv)
{
	int	f1;
	int	f2;
	int	f3;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		f1 = limiter(argv[2]);
		f2 = open_file(argv[argc - 1], READ);
		i += 1;
	}
	else
	{
		f1 = open_file(argv[1], READ);
		f2 = open_file(argv[argc - 1], CREATE);
	}
	pipex(f1, f2, argv, i);
	while (i < argc - 3)
	{
		i += 2;
		f3 = open_file(FILE_NAME, CREATE);
		f2 = open_file(argv[argc - 1], READ);
		copy_file(f2, f3);
		f3 = open_file(FILE_NAME, READ);
		f2 = open_file(argv[argc - 1], CREATE);
		if (argc % 2 == 0 && i == argc - 2)
			pipex_alone(f3, f2, argv[i]);
		else
			pipex(f3, f2, argv, i);
	}
	/*
	close(f1);
	close(f2);
	close(f3);
	*/
	// unlink(FILE_NAME);
}

size_t	find_index(char	*buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	return (i);
}

// note : créer un répertoire temp lors du makefile pour stocker le fichier temporaire
int	limiter(char *limiter)
{
	int		f1;
	char	buf[1000];
	size_t	n;

	f1 = open_file(FILE_NAME, CREATE);
	n = 0;
	while (n != ft_strlen(limiter) || ft_strncmp(buf, limiter, ft_strlen(limiter)) != 0)
	{
		write(STDIN_FILENO, "> ", 2);
		read(STDIN_FILENO, buf, sizeof(buf));
		n = find_index(buf);
		printf("n : %li\n", n);
		write(f1, buf, n + 1);
	}
	return (f1);
}
