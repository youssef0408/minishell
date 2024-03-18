/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:38 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/18 15:20:27 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_unset(t_command *info, t_cmd_parse *cmd)
{
	int	idx;
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_var_id(cmd->args[i]) || !ft_strcmp(cmd->args[i], "_"))
			printf("unset: %s: not a valid identifier\n", cmd->args[i]);
		else
			remove_from_env(&info->env, cmd->args[i]);
		i++;
	}
}
