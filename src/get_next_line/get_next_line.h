/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/08 13:55:40 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/03 16:47:48 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h> // OPEN_MAX
# include <sys/select.h> // FD_SETSIZE
# include <stddef.h> // size_t

# include "../../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX FD_SETSIZE
# endif

void	ft_strcpy(char *dest, char *src);
// size_t	ft_strlen(const char *c);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_substr(char const *s, size_t start, size_t len);

char	*get_next_line(int fd);

#endif
