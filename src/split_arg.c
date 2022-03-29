/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:09:33 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 01:09:33 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	wordcount_arg(const char *str, char c)
{
	int	i;
	int	nbr_word;

	nbr_word = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str == 39)
		{
			i = ft_wordlen(str + 1, 39);
			str += 2;
		}
		else
			i = ft_wordlen(str, c);
		str += i;
		if (i)
			nbr_word++;
	}
	return (nbr_word);
}

char	**split_arg2(char const *s, char c, int i)
{
	char	**dest;
	int		nbr_word;
	int		word_len;

	nbr_word = wordcount_arg(s, c);
	dest = malloc((nbr_word + 1) * sizeof(char *));
	if (!dest)
		return (free_word(dest, 0));
	while (i < nbr_word)
	{
		while (*s && *s == c)
			s++;
		if (*s == 39)
			word_len = ft_wordlen(++s, 39);
		else
			word_len = ft_wordlen(s, c);
		dest[i] = malloc((word_len + 1) * sizeof(char));
		if (!dest[i])
			return (free_word(dest, i + 1));
		ft_strncpy(dest[i++], s, word_len);
		s += word_len;
	}
	dest[nbr_word] = NULL;
	return (dest);
}

char	**split_arg(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (split_arg2(s, c, 0));
}
