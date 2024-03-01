/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:43:07 by bplante           #+#    #+#             */
/*   Updated: 2024/02/27 19:16:54 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_strndup(char *src, int n)
{
	if (n == 0)
		return (NULL);
	char *new = ft_calloc(n + 1, sizeof(char));
	if (!new)
		return (NULL);
	int i = 0;
	while (i < n && src[i])
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}