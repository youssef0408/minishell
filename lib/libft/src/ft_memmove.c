/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:58:17 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 01:50:23 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	const char	*lasts;
	char		*lastd;

	d = dst;
	s = src;
	if (!dst || !src)
		return (0);
	if (!n || dst == src)
		return (dst);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		lasts = s + (n - 1);
		lastd = d + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
