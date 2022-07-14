/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:23:22 by mforstho      #+#    #+#                 */
/*   Updated: 2021/11/11 12:44:22 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Converts ascii to integer

#include "libft.h"

// Used to determine if the result should be positive, negative or 0
static int	isminus(const char *str)
{
	int	i;
	int	j;
	int	k;
	int	c;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			j++;
		if (str[i] == '+')
			k++;
		if (str[i] >= '0' && str[i] <= '9')
			break ;
		i++;
	}
	c = j + k;
	if (j == 1 && c == 1)
		return (-1);
	else if ((k == 1 && c == 1) || c == 0)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+' || str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		o = o * 10;
		o = o + str[i] - '0';
		i++;
	}
	o = o * isminus(str);
	return (o);
}

// 	2147483640 + 8 = 2147483648 (overflows) = -2147483648
// 	-2147483648 * -1 = 2147483648 (overflows) = -2147483648
