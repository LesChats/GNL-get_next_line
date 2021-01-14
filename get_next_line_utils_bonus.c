/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:50:11 by abaudot           #+#    #+#             */
/*   Updated: 2021/01/14 22:07:40 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(const char *str)
{
	const char *const s_star = str;

	while (*str)
		++str;
	return ((size_t)(str - s_star));
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

void		ft_memcpy(char *dst, const char *src, size_t n)
{
	t_op	dstp;
	t_op	srcp;
	t_byte	*dstd;
	t_byte	*srcd;

	dstp = (t_op)dst;
	srcp = (t_op)src;
	if (n >= 16)
	{
		wordcpy(dstp, srcp, n >> 3);
		srcp += n & -OPSIZ;
		dstp += n & -OPSIZ;
		n %= OPSIZ;
	}
	dstd = (t_byte *)dstp;
	srcd = (t_byte *)srcp;
	while (n--)
		*dstd++ = *srcd++;
}
