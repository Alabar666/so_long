/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:43:57 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/16 18:22:18 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *backup)
{
	int		bytes_read;
	char	*buffer;

	buffer = ft_calloc_gnl(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!(ft_strchr_gnl(backup, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		if (!buffer)
			return (NULL);
		backup = ft_strjoin_gnl(backup, buffer);
	}
	free(buffer);
	return (backup);
}

char	*get_line(char *backup)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
		line = ft_calloc_gnl(sizeof(char), (i + 1));
	else
		line = ft_calloc_gnl(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && (backup[i] != '\n'))
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next(char *backup)
{
	unsigned int	i;
	int				next_i;
	char			*next;

	i = 0;
	while (backup[i] && (backup[i] != '\n'))
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	next = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(backup) - i + 1));
	if (!next)
	{
		free(next);
		return (NULL);
	}
	++i;
	next_i = 0;
	while (backup[i])
		next[next_i++] = backup[i++];
	next[next_i] = '\0';
	free(backup);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	backup = read_line(fd, backup);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = get_next(backup);
	return (line);
}
