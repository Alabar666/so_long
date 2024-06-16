/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:30:43 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/05/05 17:54:38 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: split string, with specified character as delimiter, into an array
**			of strings
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns an array of strings obtained by
**	splitting 's' using the character 'c' as a delimiter. The array must be
**	ended by a NULL pointer.
*/

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	unsigned int	count;
	unsigned int	flag;
	unsigned int	i;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			flag = 0;
		}
		else if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		i++;
	}
	return (count);
}

static char	**ft_free(char **strs)
{
	unsigned int	i;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	return (NULL);
}

static char	**ft_fill(char const *s, char c, char **res)
{
	unsigned int	i;
	size_t			word;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		if (!ft_strchr(s, c))
			word = ft_strlen(s);
		else
			word = ft_strchr(s, c) - s;
		res[i] = ft_substr(s, 0, word);
		if (!res[i])
		{
			ft_free(res);
			return (0);
		}
		i++;
		s += word;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_fill(s, c, res);
	return (res);
}
