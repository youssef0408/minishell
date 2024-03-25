/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:51:49 by bplante           #+#    #+#             */
/*   Updated: 2024/03/25 12:55:59 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_empty_cmd(t_cmd_parse **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->redirections || cmds[i]->args[0])
			return (false);
		i++;
	}
	return (true);
}
