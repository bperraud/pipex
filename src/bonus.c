/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 03:47:33 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 03:47:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/get_next_line_bonus.h"

static void	pipex_alone(int f1, int f2, char *arg)
{
	int		child;
	char	**paths;
	char	**cmd_arg;

	paths = parsing(g_envp);
	cmd_arg = split_arg(arg, ' ');
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	child = fork();
	if (child == 0)
		exec(cmd_arg, paths);
}

static void	copy_file(int f1, int f2)
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

static size_t	find_index(char	*buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	return (i);
}

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