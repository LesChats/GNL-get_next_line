/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 08:41:44 by gcc               #+#    #+#             */
/*   Updated: 2021/01/10 16:15:00 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

# ifndef FOPEN_MAX
#  define FOPEN_MAX		200
# endif

/*
**	magic numbers
*/

# define HIMAGIC	0x8080808080808080L
# define LOMAGIC	0x0101010101010101L
# define NL			0xa0a0a0a0a0a0a0aL
# define OPSIZ		8

/*
**	return messages
*/

# define ERROR		-1
# define ENDFI		0
# define SUCESS		1

/*
**	type & structurs
*/

typedef struct	s_string
{
	char	**addr;
	char	*s;
	size_t		len;
	size_t		size;
}				t_string;

typedef unsigned long int	t_op;
typedef unsigned char		t_byte;

/*
**	get_next_line.c
*/

int				get_next_line(int fd, char **line);

/*
**	get_next_line_utils.c
*/

size_t			ft_strlen(const char *s);
void			ft_memcpy(char *dst, const char *src, size_t n);

#endif
