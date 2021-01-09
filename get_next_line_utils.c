* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcc <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 09:07:18 by gcc               #+#    #+#             */
/*   Updated: 2020/12/07 02:00:22 by gcc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

/*
** It seem's that my 'optimized strlen can lead, in some ciconstance, to
**	heap overflow... saddly, and for security reason I have to abandon it
**	and reaplace it by the must simple and ugly strlen... wait for it....
**size_t	ft_strlen(char *s)
**{
**	t_op	word;
**	t_op	*s_ptr;
**	int	i;
**	char * const cpy = s;
**
**	if (!s || !*s)
**		return (0);
**	while ((t_op)s & 0b111)
**		if (*s++ == 0)
**			return ((s - 1) - cpy);
**	s_ptr = (t_op *)s;
**	while (1)
**	{
**		word = *s_ptr;
**		if (((word - LOMAGIC) & ~word & HIMAGIC))
**		{
**			i = -1;
**			s = (char *)s_ptr;
**			while (++i < 8)
**				if (!s[i])
**					return ((s - cpy) + i);
**		}
**		++s_ptr;
**	}
**}
**
*/

size_t ft_strlen(const char * str)
{
	const char * const s_star = str;

	while (*str)
		++str;
	return ((size_t)(str - s_star));
}

int	free_return(t_string *str, int ans)
{
	free(str);
	return (ans);
}

static void	wordcpy(t_op dstp, t_op srcp, size_t n)
{
	t_op a0;
	t_op a1;

	if (n & 1)
	{
		((t_op *)dstp)[0] = ((t_op *)srcp)[0];
		if (n == 1)
			return ;
		srcp += OPSIZ;
		dstp += OPSIZ;
		--n;
	}
	while (n)
	{
		a0 = ((t_op *)srcp)[0];
		a1 = ((t_op *)srcp)[1];
		((t_op *)dstp)[0] = a0;
		((t_op *)dstp)[1] = a1;
		srcp += 16;
		dstp += 16;
		n -= 2;
	}
}

void	ft_memcpy(char *dst, const char *src, size_t n)
{
	t_op	dstp;
	t_op	srcp;
	t_byte	*dstd;
	t_byte	*srcd;

	dstp = (t_op)dst;
	srcp = (t_op)src;
	if (n >= 16)
	{
		wordcpy(dstp, srcp, n / OPSIZ);
		srcp += n & -OPSIZ;
		dstp += n & -OPSIZ;
		n %= OPSIZ;
	}		
	dstd = (t_byte *)dstp;
	srcd = (t_byte *)srcp;
	while (n--)
		*dstd++ = *srcd++;
}
