/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:38 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/17 16:14:01 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_unset(t_command *cmd)
{
	int idx;
	int i;
    
	idx = find_in_env(cmd->option, cmd->env);
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
}
