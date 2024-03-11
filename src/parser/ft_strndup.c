/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:43:07 by bplante           #+#    #+#             */
/*   Updated: 2024/03/11 17:51:11 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*new;
	int		i;

	if (n == 0)
		return (NULL);
	new = safe_calloc(n + 1, sizeof(char));
	i = 0;
	while (i < n && src[i])
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}
