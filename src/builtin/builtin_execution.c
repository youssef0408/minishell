/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:33:01 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/18 15:20:38 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	init_cmd(char *str_cmd, t_command *cmd)
// {
// 	char	**tab_cmd;
// 	int		i;
// 	char	*tmp;

// 	tab_cmd = ft_split(str_cmd, ' ');
// 	if (!tab_cmd)
// 		return ;
// 	cmd->name = tab_cmd[0];
// 	cmd->exit_status = 0;
// 	cmd->option = "";
// 	cmd->option2 = "";
// 	cmd->cmd_str = str_cmd;
// 	if (!tab_cmd[1])
// 		return ;
// 	cmd->option = tab_cmd[1];

// 	i = 2;
// 	tmp = "";
// 	if (!tab_cmd[2])
// 		return ;
// 	while (tab_cmd[i])
// 	{
// 		if (tab_cmd[i])
// 			tmp = ft_strjoin(tmp, " ");
// 		tmp = ft_strjoin(tmp, tab_cmd[i]);
// 		i++;
// 	}
// 	cmd->option2 = tmp;
// }

// TODO: Proper exit status management with the builtins
int	exec_builtin(t_command *info, t_cmd_parse *cmd)
{
	int		i;
	char	*tmp;
	int		result;

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
