/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/12 20:46:23 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
/*
**                              HEADERS
*/
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>//open
# include <stddef.h>
# include <stdio.h>//error
# include <string.h>//strerror
# include <unistd.h>//read, write
# include <stdlib.h>//malloc,free, exit + rand
/*
**                              BUFFERS
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 4242
# endif
/*
**                              KEY CODES
*/
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307

#define SZ 40 //img size
/*
**                              C
*/
/*
**                              FUNCTION PROTOTYPES
*/
char	*get_next_line(int fd);
char	*read_line(int fd, char *backup);
char	*get_line(char *backup);
char	*get_next(char *backup);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);

#endif