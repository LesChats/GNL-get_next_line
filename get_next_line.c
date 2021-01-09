/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:37:13 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/08 16:37:29 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long int	get_nl(const char *s, size_t n)
{
	t_op				long_word;
	const char * const	s_save = s;

	while (n >= 16)
	{
		long_word = *(t_op *)s ^ NL;
		if ((long_word - LOMAGIC) & ~long_word & HIMAGIC))
			break ;
		n -= 8;
		s += 8;
	}
	while (n--)
	{
		if (*s == '\n')
			return ((long int)(s - s_save));
		++s;
	}
	return (-1);
}

static int	update_string(t_string *str, char *src, size_t n)
{
	char *tmp;

	if (n > str->space)
	{
		str->space <<= 1;
		tmp = str->s;
		if (!(str->s = (char *)malloc(str->space + 1))) 
			return (0);
		ft_memcpy(str->s, tmp, str->len);
		free(tmp);
		*(str->line) = str->s;
		str->space -= str->len;
	}
	str->space -= n;
	ft_memcpy(str->s + str->len, src, n);
	str->len += n;
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
	//string->up = 1;
	return (string);
}

int		get_next_line(int fd, char **line)
{
	static char	sheets[FOPEN_MAX][BUFFER_SIZE + 1];
	size_t		sheet_len;
	long int	a_nl;
	t_string	*my_line;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (ERROR);
	if (!(my_line = initilize_string(line)))
		return (ERROR);
	if (sheets[fd][0] == 0)
		return (read_line(fd, my_line, sheets[fd]));
	sheet_len = ft_strlen(sheets[fd]);
	if ((a_nl = get_nl(sheets[fd], sheet_len)) != -1)
	{
		if (!(update_string(my_line, sheets[fd], a_nl)))
			return (free_return(my_line, ERROR));
 		ft_memcpy(sheets[fd], sheets[fd] + a_nl + 1, sheet_len);
		return (free_return(my_line, SUCESS));
	}
	if (!(update_string(my_line, sheets[fd], ft_strlen(sheets[fd]))))
		return (free_return(my_line, ERROR));
	sheets[fd][0] = 0;
		return (read_line(fd, my_line, sheets[fd]));
}
