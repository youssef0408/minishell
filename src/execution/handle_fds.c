/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:14:35 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/24 15:43:49 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_irrelevant_fds(int *fds, int pos)
{
	int	i;

	i = 0;
	while (fds[i] != EOINTA)
	{
		if ((pos * 2 != i && pos * 2 + 1 != i) && fds[i] != -1)
			close(fds[i]);
		i++;
	}
}

void	close_non_std_fds(int *fds)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (fds[i] != EOINTA)
	{
		if (fds[i] > 2)
			close(fds[i]);
		i++;
	}
}
