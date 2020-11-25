/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 08:41:44 by gcc               #+#    #+#             */
/*   Updated: 2020/11/25 07:33:05 by gcc              ###   ########.fr       */
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

/*
**	magic numbers
*/

# define HIMAGIC	0x8080808080808080L
# define LOMAGIC	0x0101010101010101L
# define NL		0xa0a0a0a0a0a0a0aL

/*
**	return messages
*/

# define ERROR		-1
# define ENDFI		0
# define SUCESS		1

typedef unsigned long int	t_op;
typedef unsigned char		t_byte;
# define OPSIZ	sizeof(t_op)

/*
**	get_next_line.c
*/

int				get_next_line(int fd, char **line);

/*
**	get_next_line_utils.c
*/

size_t	ft_strlen(char *s);
void	ft_strcpy(char *dst, char *src);
void	ft_memcpy(char *dst, char *src, size_t n);

#endif

