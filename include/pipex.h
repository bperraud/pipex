/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/24 02:11:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "fcntl.h"
# include "wait.h"
# include "errno.h"

# define FILE_NAME "filenameyouwontthinkabout"
# define READ 1
# define CREATE 0

extern	char **g_envp;

//main
void    start(int i, int argc, char **argv);
int		limiter(char *limiter);

//pipex
void	pipex(int f1, int f2, char** argv, int index);
void	pipex2(int f[2], char** paths, char **cmd1, char **cmd2);
void	pipex_alone(int f1, int f2, char* arg);

//process
void	exec(char **cmd, char **paths);
void	child_one(int f1, int end[2], char **cmd1, char **paths);
void	child_two(int f2, int end[2], char **cmd1, char **paths);
void	wait_proccess(pid_t child1, pid_t child2, int end[2]);

//files
char	**parsing(char **envp);
void	copy_file(int f1, int f2);
char	*create_path(char *path, char *arg);
int		open_file(char *file, int mode);

// utils
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	exit_error(char **cmd1, char **cmd2, char **path, char *error);
void	free_all(char **cmd1, char **cmd2, char **path);

#endif
