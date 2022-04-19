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

#include "../include/bonus.h"
#include "../include/pipex.h"
#include "../include/get_next_line_bonus.h"

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

int	limiter(char *limiter)
{
	int		f1;
	size_t	len_limiter;
	char	*buf;

	len_limiter = ft_strlen(limiter);
	f1 = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buf = get_next_line(1);
		if (buf && (ft_strlen(buf) - 1 != len_limiter || ft_strncmp(buf, limiter, len_limiter) != 0))
			write(f1, buf, ft_strlen(buf));
		else
			break ;
	}
	close(f1);
	f1 = open_file(FILE_NAME);
	return (f1);
}

void	pipex_alone(int input_file, int output_file, char *arg, char**envp)
{
	int		child;
	char	**paths;
	char	**cmd_arg;
	int		pipe_fd[2];
	int		status;

	paths = parsing(envp);
	cmd_arg = split_arg(arg, ' ');
	if (pipe(pipe_fd) < 0)
	{
		exit_error(NULL, NULL, cmd_arg); // verifier cette ligne
	}
	child = fork();

	if (!child)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec(cmd_arg, paths, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(-1, &status, 0);
	}
}

void	multiple_cmd(int fd[2], int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;

	fd_in = fd[0];
	fd_out = fd[1];
	/*
	pipex_alone(argv[2], envp);
	*/

	dup2(fd_in, 0);			// sans ça : lit sur l'entrée standart
	close(fd_in);			// toujours fermé l'entrée du pipe

	pipex_alone(fd_in, fd_out, argv[2], envp);

	while (++i < argc - 2)
		pipex_alone(fd_in, fd_out, argv[i], envp);

	dup2(fd_out, 1);
	close(fd_out);

	char	**paths;
	char	**cmd_arg;

	paths = parsing(envp);
	cmd_arg = split_arg(argv[argc - 2], ' ');	// derniere commande

	if (!fork())
		exec(cmd_arg, paths, envp);

	unlink(FILE_NAME);
}
