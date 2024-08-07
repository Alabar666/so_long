/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:49:30 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/04/29 21:24:03 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: create new list
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns a new element. The variable
**	’content’ is initialized with the value of the parameter ’content’. The
**	variable ’next’ is initialized to NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstn;

	lstn = malloc(sizeof(t_list));
	if (!lstn)
		return (NULL);
	lstn->content = content;
	lstn->next = NULL;
	return (lstn);
}
