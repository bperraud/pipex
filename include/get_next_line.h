/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 03:35:52 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/20 03:37:52 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#ifndef GET_NEXT_LINE_H
//# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

#  define OPEN_MAX 255		// a changer 

# include <stdlib.h>
# include <limits.h>
# include "pipex.h"

char	*get_next_line(int fd);
char	*true_gnl(int fd);
char	*true_gnl_2(long ret, char *line, char *buff, char *temp);
void	*ft_memchr(const void *s, int c, long n);
char	*ft_strncpy_gnl(char *dest, const char *src, long n);
char	**ft_split_gnl(char const *s, const char c);
char	*end_of_line(char *line, char *buff);

#endif
