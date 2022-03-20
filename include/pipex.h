/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 02:46:01 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "stdio.h"


# include "stdlib.h"
# include "unistd.h"
# include "fcntl.h"
# include "wait.h"

extern	char **g_envp;

void	pipex(int f1, int f2, char** argv);
char	**parsing(char **envp);
void	free_all();

void	child_one(int f1, int end[2], char **cmd1, char **paths);
void	child_two(int f2, int end[2], char **cmd1, char **paths);


char	*create_path(char *path, char *arg);

#endif



