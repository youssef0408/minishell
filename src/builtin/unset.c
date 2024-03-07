/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:38 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/07 16:40:16 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_unset(t_command *cmd)
{
	int	idx;
	int	i;
	int	j;

	j = 1;
	while (cmd->parsed[0]->cmds[j])
	{
		idx = find_in_env(cmd->parsed[0]->cmds[j], cmd->env);
		if (idx != -1)
		{
			free(cmd->env[idx]);
			i = idx;
			while (cmd->env[i])
			{
				cmd->env[i] = cmd->env[i + 1];
				i++;
			}
			update_env(cmd, NULL);
		}
		j++;
	}
}
