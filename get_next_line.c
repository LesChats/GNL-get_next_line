/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:32:17 by gcc               #+#    #+#             */
/*   Updated: 2020/11/25 09:09:56 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long int	get_newline(char *s)
{
	t_op		word;
	t_op		*sss;
	char * const	s_ptr = s;
	int		i;

	while ((t_op)s & 0b111)
		if (*s++ == '\n')
			return ((s - 1) - s_ptr);
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
					return ((s + i) - s_ptr);
				else if (!s[i])
					return (-1);
		}
	}
}

static char	*ft_nappend(char *dst, char *src, size_t src_len)
{
	char	*tmp;
	const size_t dst_len = ft_strlen(dst);

	if (!(tmp = (char *)malloc(dst_len + 1)))
		return (NULL);
	ft_memcpy(tmp, dst, dst_len);
	free(dst);
	if (!(dst = (char *)malloc(dst_len + src_len + 1)))
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(dst, tmp, dst_len);
	free(tmp);
	ft_memcpy(dst + dst_len, src, src_len);
	dst[dst_len + src_len] = 0;
	return (dst);
}

static int	read_line(int fd, char **line, char *sheet)
{
	int		readed;
	long int	a_nl;

	while ((readed = read(fd, sheet, BUFFER_SIZE)) > 0)
	{
		sheet[readed] = 0;
		if ((a_nl = get_newline(sheet)) != -1)
		{
			sheet[a_nl] = 0;
			if (!(*line = ft_nappend(*line, sheet, a_nl)))
				return (ERROR);
			ft_memcpy(sheet, sheet + a_nl + 1, readed - a_nl);
			return (SUCESS);
		}
		if (!(*line = ft_nappend(*line, sheet, readed + 1)))
			return (ERROR);
	}
	sheet[0] = 0;
	if (readed == -1)
	{
		free(*line);
		return (ERROR);
	}
	return (ENDFI);
}

int	get_next_line(int fd, char **line)
{
	static char	sheets[FOPEN_MAX][BUFFER_SIZE + 1];
	long int	a_nl;

	if (fd < 0 || fd > FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (ERROR);
	if (!(*line = (char *)malloc(1)))
		return (ERROR);
	**line = 0;
	if (sheets[fd][0] == 0)
		return (read_line(fd, line, sheets[fd]));
	if ((a_nl = get_newline(sheets[fd])) != -1)
	{
		free(*line);
		if (!(*line = (char *)(malloc(a_nl + 1))))
			return (ERROR);
		ft_memcpy(*line, sheets[fd], a_nl);
		(*line)[a_nl] = 0;
 		ft_strcpy(sheets[fd], sheets[fd] + a_nl + 1);
		return (SUCESS);
	}
	free(*line);
	if (!(*line = (char *)malloc(ft_strlen(sheets[fd]) + 1)))
		return (ERROR);
	ft_strcpy(*line, sheets[fd]);
	sheets[fd][0] = 0;
	return (read_line(fd, line, sheets[fd]));
}
