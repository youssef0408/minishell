/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:53:19 by bplante           #+#    #+#             */
/*   Updated: 2024/03/18 16:49:21 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_cmd_count(t_cmd_parse **cmd_p)
{
	int	i;

	i = 0;
	if (!cmd_p)
		return (0);
	while (cmd_p[i])
		i++;
	return (i);
}
