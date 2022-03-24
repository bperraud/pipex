/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/25 00:39:41 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	if (argc < 5)
		return (-1);
	g_envp = envp;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		f1 = limiter(argv[2]);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		pipex(f1, f2, argv, 3);
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

void	multiple_cmd(int f2, int argc, char **argv)
{
	int	f3;
	int	i;

	i = 2;
	while (i < argc - 3)
	{
		i += 2;
		f3 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
		f2 = open_file(argv[argc - 1]);
		copy_file(f2, f3);
		f3 = open_file(FILE_NAME);
		f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (argc % 2 == 0 && i == argc - 2)
			pipex_alone(f3, f2, argv[i]);
		else
			pipex(f3, f2, argv, i);
	}
	close(f2);
	close(f3);
	unlink(FILE_NAME);
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
	size_t	len_limiter;

	len_limiter = ft_strlen(limiter);
	f1 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	n = 0;
	while (n != len_limiter || ft_strncmp(buf, limiter, len_limiter) != 0)
	{
		write(STDIN_FILENO, "> ", 2);
		read(STDIN_FILENO, buf, sizeof(buf));
		n = find_index(buf);
		write(f1, buf, n + 1);
	}
	close(f1);
	f1 = open_file(FILE_NAME);
	return (f1);
}
