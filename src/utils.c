/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:21:30 by bperraud          #+#    #+#             */
/*   Updated: 2022/03/30 03:28:27 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	dest = malloc(((ft_strlen(s1)) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_strncpy(dest, s1, ft_strlen(s1)));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (!n)
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start < ft_strlen(s))
	{
		substr = malloc((len + 1) * sizeof(char));
		if (!substr)
			return (NULL);
		s += start;
		while (i < len)
		{
			substr[i] = s[i];
			i++;
		}
		substr[i] = '\0';
		return (substr);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strncpy(str, s1, lens1);
	ft_strncpy(str + lens1, s2, ft_strlen(s2));
	return (str);
}
