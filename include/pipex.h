/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/25 02:42:51 by bperraud         ###   ########.fr       */
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

//# define FILE_NAME "temp/file"
# define FILE_NAME "filename"

extern char	**g_envp;

//main
void	multiple_cmd(int f2, int argc, char **argv);
int		limiter(char *limiter);

//pipex
void	pipex(int f1, int f2, char **argv, int index);
void	pipex2(int f[2], char **paths, char **cmd1, char **cmd2);
void	pipex_alone(int f1, int f2, char *arg);

//process
void	exec(char **cmd, char **paths);
void	child_one(int f1, int end[2], char **cmd1, char **paths);
void	child_two(int f2, int end[2], char **cmd1, char **paths);

//files
char	**parsing(char **envp);
void	copy_file(int f1, int f2);
char	*create_path(char *path, char *arg);
int		open_file(char *file);

// utils
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	exit_error(char **cmd1, char **cmd2, char **path);
void	free_all(char **cmd1, char **cmd2, char **path);
void	free_tab(char **tab);

#endif
