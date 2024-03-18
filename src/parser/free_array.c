/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 03:09:08 by bplante           #+#    #+#             */
/*   Updated: 2024/03/18 16:50:02 by yothmani         ###   ########.fr       */
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
