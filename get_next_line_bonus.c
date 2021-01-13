/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:50:50 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/10 20:39:38 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int		get_nl(const char *s, size_t n)
{
	t_op				long_word;
	const char *const	s_save = s;

	while (n >= 16)
	{
		long_word = *(t_op *)s ^ NL;
		if ((long_word - LOMAGIC) & ~long_word & HIMAGIC)
			break ;
		n -= 8;
		s += 8;
	}
	while (n--)
	{
		if (*s == '\n')
			return ((int)(s - s_save));
		++s;
	}
	return (-1);
}

static int		update_string(t_string *str, char *src, int n)
{
	char		*tmp;
	const int	wanted = n + str->len;

	if (str->size < wanted)
	{
		while (str->size < wanted)
			str->size <<= 1;
		tmp = str->s;
		if (!(str->s = (char *)malloc(str->size + 1)))
			return (0);
		ft_memcpy(str->s, tmp, str->len);
		free(tmp);
		*(str->addr) = str->s;
	}
	ft_memcpy(str->s + str->len, src, n);
	str->len = wanted;
	str->s[str->len] = 0;
	return (1);
}

static int		read_line(int fd, t_string *str, char *sheet)
{
	ssize_t		av_read;
	int			a_nl;

	while ((av_read = read(fd, sheet, BUFFER_SIZE)) > 0)
	{
		sheet[av_read] = 0;
		if ((a_nl = get_nl(sheet, av_read)) != -1)
		{
			if (!(update_string(str, sheet, a_nl)))
				return (ERROR);
			ft_memcpy(sheet, sheet + a_nl + 1, av_read - a_nl);
			return (SUCESS);
		}
		if (!(update_string(str, sheet, av_read)))
			return (ERROR);
	}
	*sheet = 0;
	if (av_read == -1)
	{
		free(str->s);
		*(str->addr) = NULL;
		return (ERROR);
	}
	return (ENDFI);
}

static int		initilize_string(t_string *string, char **line)
{
	if (!(*line = (char *)malloc(3)))
		return (0);
	**line = 0;
	string->addr = line;
	string->s = *line;
	string->len = 0;
	string->size = 2;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	sheets[OPEN_MAX][BUFFER_SIZE + 1];
	t_string	my_line;
	size_t		sheet_len;
	int			a_nl;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE < 1)
		return (ERROR);
	if (!(initilize_string(&my_line, line)))
		return (ERROR);
	if (sheets[fd][0] == 0)
		return (read_line(fd, &my_line, sheets[fd]));
	sheet_len = ft_strlen(sheets[fd]);
	if ((a_nl = get_nl(sheets[fd], sheet_len)) != -1)
	{
		if (!(update_string(&my_line, sheets[fd], a_nl)))
			return (ERROR);
		ft_memcpy(sheets[fd], sheets[fd] + a_nl + 1, sheet_len - a_nl);
		return (SUCESS);
	}
	if (!(update_string(&my_line, sheets[fd], ft_strlen(sheets[fd]))))
		return (ERROR);
	return (read_line(fd, &my_line, sheets[fd]));
}
