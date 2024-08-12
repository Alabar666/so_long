/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:02:56 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/05/16 19:42:14 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <stdlib.h>
** SYNOPSIS: memory allocation
**
** DESCRIPTION:
** 		The calloc() function contiguously allocates enough space for count
**	objects that are size bytes of memory each and returns a pointer to the
**	allocated memory. The allocated memory is filled with bytes of value
**	zero.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*str;
	unsigned int	i;

	str = malloc(size * count);
	if (str)
	{
		i = 0;
		while (i < count * size)
		{
			str[i] = (unsigned char)0;
			i++;
		}
	}
	return (str);
}
