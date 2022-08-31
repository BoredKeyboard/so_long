/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/08 12:52:16 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 14:32:22 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> // read, ssize_t
#include <stdlib.h> // free, size_t, NULL

static char	*gnl_split(const char *s, char *dst)
{
	char	*newl;
	char	*begin;

	newl = ft_strchr(s, '\n');
	begin = ft_substr(s, 0, newl - s + 1);
	if (begin == NULL)
		return (NULL);
	ft_strcpy(dst, newl + 1);
	return (begin);
}

static void	*replace_value(void *p, void *value)
{
	void	**ptr;

	ptr = (void **)p;
	free(*ptr);
	*ptr = value;
	return (value);
}

static char	*split_join(char *line, char *buf)
{
	char	*ln_end;

	ln_end = gnl_split(buf, buf);
	if (ln_end == NULL)
	{
		free(line);
		return (NULL);
	}
	if (replace_value(&line, ft_strjoin(line, ln_end)) == NULL)
	{
		free(ln_end);
		return (NULL);
	}
	free(ln_end);
	return (line);
}

static char	*gnl_core(char *line, char *buf, ssize_t eof, int fd)
{
	while (!ft_strchr(buf, '\n') && eof > 0)
	{
		if (ft_strchr(buf, '\n') != NULL)
			return (split_join(line, buf));
		if (replace_value(&line, ft_strjoin(line, buf)) == NULL)
			return (NULL);
		eof = read(fd, buf, BUFFER_SIZE);
		if (eof < 0)
		{
			free(line);
			return (NULL);
		}
		buf[eof] = '\0';
	}
	if (ft_strchr(buf, '\n') == NULL)
		return (line);
	return (split_join(line, buf));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "";
	char		*line;
	ssize_t		eof;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (ft_strchr(buf, '\n') != NULL)
		return (gnl_split(buf, buf));
	line = ft_strjoin("", buf);
	if (line == NULL)
		return (NULL);
	eof = read(fd, buf, BUFFER_SIZE);
	if (line[0] == '\0' && eof <= 0)
	{
		free(line);
		return (NULL);
	}
	buf[eof] = '\0';
	return (gnl_core(line, buf, eof, fd));
}
