/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:33:01 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/18 16:09:27 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	exec_builtin(t_command *info, t_cmd_parse *cmd)
{
	info->exit_status = 0;
	if (!ft_strcmp(cmd->args[0], "pwd"))
		exec_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		change_dir(cmd, info);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export_exec(info, cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		exec_env(info, cmd);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		exec_exit(info, cmd);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		exec_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		exec_unset(info, cmd);
	else
		return (1);
	return (0);
}
