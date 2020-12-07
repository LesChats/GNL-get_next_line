/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:32:17 by gcc               #+#    #+#             */
/*   Updated: 2020/12/07 03:05:08 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long int	get_nl(char *s)
{
	t_op		word;
	t_op		*sss;
	char * const	save = s;
	int		i;

	while ((t_op)s & 0b111)
		if (*s++ == '\n')
			return ((s - 1) - save);
		else if (*(s - 1) == '\0')
			return (-1);
	sss = (t_op *)s;
	while (1)
	{
		word = *sss++;
		if (((word - LOMAGIC) & (~word) & HIMAGIC) ||
		(((word ^ NL) - LOMAGIC) & ~(word ^ NL) & HIMAGIC))
		{	
			s = (char *)(sss - 1);
			i = -1;
			while (++i < 8)
				if (s[i] == '\n')
					return ((s + i) - save);
				else if (!s[i])
					return (-1);
		}
	}
}

static int	update_string(t_string *str, char *src, size_t n)
{
	char *tmp;

	if (n > str->space)
	{
		if (!(tmp = (char *)malloc(str->len)))
			return (0);
		ft_memcpy(tmp, str->s, str->len);
		free(str->s);
		str->space = BUFFER_SIZE << str->up++;
		if (!(str->s = (char *)malloc(str->space + 1))) 
		{
			free(tmp);
			return (0);
		}
		ft_memcpy(str->s, tmp, str->len);
		str->space -= str->len;
		*(str->line) = str->s;
		free(tmp);
	}
	ft_memcpy(str->s + str->len, src, n);
	str->len += n;
	str->space -= n;
	str->s[str->len] = 0;
	return (1);
}

static int	read_line(int fd, t_string *str, char *sheet)
{
	ssize_t		av_read;
	long int	a_nl;
	
	while ((av_read = read(fd, sheet, BUFFER_SIZE)) > 0)
	{
		sheet[av_read] = 0;
		if ((a_nl = get_nl(sheet)) != -1)
		{
			sheet[a_nl] = 0;
			if (!(update_string(str, sheet, a_nl)))
				return (free_return(str, ERROR));
			ft_memcpy(sheet, sheet + a_nl + 1, av_read - a_nl);
			return (free_return(str, SUCESS));
		}
		if (!(update_string(str, sheet, av_read))) 
			return (free_return(str, ERROR));
	}
	*sheet = 0;
	if (av_read == -1)
	{
		free(str->s);
		return (free_return(str, ERROR));
	}
	return (free_return(str, ENDFI));
}

static t_string	*initilize_string(char **line)
{
	t_string *string;

	if (!(string = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	if (!(*line = (char *)malloc(BUFFER_SIZE + 1)))
		return (NULL);
	**line = 0;
	string->line = line;
	string->s = *line;
	string->len = 0;
	string->space = BUFFER_SIZE;
	string->up = 1;
	return (string);
}

int		get_next_line(int fd, char **line)
{
	static char	sheets[FOPEN_MAX][BUFFER_SIZE + 1];
	long int	a_nl;
	t_string	*my_line;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (ERROR);
	if (!(my_line = initilize_string(line)))
		return (ERROR);
	if (sheets[fd][0] == 0)
		return (read_line(fd, my_line, sheets[fd]));
	if ((a_nl = get_nl(sheets[fd])) != -1)
	{
		if (!(update_string(my_line, sheets[fd], a_nl)))
			return (free_return(my_line, ERROR));
 		ft_strcpy(sheets[fd], sheets[fd] + a_nl + 1);
		return (free_return(my_line, SUCESS));
	}
	if (!(update_string(my_line, sheets[fd], ft_strlen(sheets[fd]))))
		return (free_return(my_line, ERROR));
	sheets[fd][0] = 0;
	return (read_line(fd, my_line, sheets[fd]));
}
