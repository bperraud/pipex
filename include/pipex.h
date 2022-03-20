/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 22:05:34 by bperraud         ###   ########.fr       */
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

void	pipex(int f1, int f2, char** argv, int index);
char	**parsing(char **envp);
void	free_all();

void	child_one(int f1, int end[2], char **cmd1, char **paths);
void	child_two(int f2, int end[2], char **cmd1, char **paths);

char	*create_path(char *path, char *arg);


//files
void	copy_file(int f1, int f2);

// utils
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

#endif



