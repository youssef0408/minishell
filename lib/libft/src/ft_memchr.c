/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:20:58 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 01:48:25 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		i;

	if (!s)
		return (NULL);
	str = s;
	i = 0;
	while (n > i)
	{
		if (str[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (0);
}
