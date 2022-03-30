/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 04:04:20 by bperraud         ###   ########.fr       */
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

extern char	**g_envp;

//pipex
void	pipex(int f1, int f2, char **argv, int index);
void	pipex2(int f[2], char **paths, char **cmd1, char **cmd2);

//process
void	exec(char **cmd, char **paths);
void	child_one(int f1, int end[2], char **cmd1, char **paths);
void	child_two(int f2, int end[2], char **cmd1, char **paths);

//files
char	**parsing(char **envp);
char	*create_path(char *path, char *arg);

// utils
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	exit_error(char **cmd1, char **cmd2, char **path);
void	free_all(char **cmd1, char **cmd2, char **path);
void	free_tab(char **tab);

//split
char	**ft_split(char const *s, char c);
char	**split_arg(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
void	*free_word(char **dest, int nbr_word);
int		ft_wordcount(const char *str, char c);
int		ft_wordlen(const char *str, char c);

#endif
