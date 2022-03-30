/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:00:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 16:00:43 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	if (argc != 5)
		return (-1);
	g_envp = envp;
	f1 = open_file(argv[1]);
	f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipex(f1, f2, argv, 2);
	close(f1);
	close(f2);
	return (0);
}
