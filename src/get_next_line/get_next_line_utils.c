/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/08 12:52:16 by mforstho      #+#    #+#                 */
/*   Updated: 2022/01/24 15:55:37 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc, size_t, NULL

void	ft_strcpy(char *dest, char *src)
{
	int	n;

	n = 0;
	while (src[n] != '\0')
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c2;
	char	*s2;

	i = 0;
	c2 = (char)c;
	s2 = (char *)s;
	if (c2 == '\0')
	{
		i = ft_strlen(s2);
		return (&s2[i]);
	}
	while (s2[i] != '\0')
	{
		if (s2[i] == c2)
			return (&s2[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*comb;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	comb = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (comb == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		comb[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		comb[i] = s2[j];
		i++;
		j++;
	}
	comb[i] = '\0';
	return (comb);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub[0] = '\0';
		return (sub);
	}
	while (s[i] != '\0' && j < len)
	{
		sub[j] = (char)s[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
