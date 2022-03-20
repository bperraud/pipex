/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:38:08 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 02:26:51 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char **g_envp;

int main(int argc, char **argv, char **envp)
{
    int		f1;
    int		f2;

    printf("%i\n", argc);

	g_envp = envp;
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (f1 < 0 || f2 < 0)
        return (-1);
    pipex(f1, f2, argv);
    return (0);
}
