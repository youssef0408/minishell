/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:23:38 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 13:35:19 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_unset(t_command *info, t_cmd_parse *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_var_id(cmd->args[i]) || !ft_strcmp(cmd->args[i], "_"))
			ft_printf_fd("unset: %s: not a valid identifier\n", 2, cmd->args[i]);
		else
			remove_from_env(&info->env, cmd->args[i]);
		i++;
	}
}
