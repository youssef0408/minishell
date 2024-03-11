/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 03:09:08 by bplante           #+#    #+#             */
/*   Updated: 2024/03/11 17:16:24 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_array(void **arr, void (del)(void *))
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		(del)(arr[i]);
		i++;
	}
	free(arr);
}
