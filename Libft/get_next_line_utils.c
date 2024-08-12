/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:39:57 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/16 18:23:38 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	l;

	l = 0;
	while (s && s[l])
		l++;
	return (l);
}

char	*ft_strchr_gnl(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	str = (char *)ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char			*str;
	unsigned int	i;

	str = malloc(size * count);
	if (str)
	{
		i = 0;
		while (i < (count * size))
		{
			str[i] = 0;
			i++;
		}
	}
	return (str);
}
