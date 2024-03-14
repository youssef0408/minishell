/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/14 16:13:46 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	change_dir(t_cmd_parse *cmd, t_command *info)
{
	char	*home;
	char	*current_pwd;
	char	*tmp;

	current_pwd = get_pwd();
	home = get_value_with_key(info->env, "HOME");
	tmp = add_to_env(&info->env, "OLDPWD", current_pwd);
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
		cmd->args[1] = home;
	else if (!ft_strcmp(str, "-"))
		cmd->args[1] = ft_substr(tmp, 7, ft_strlen(tmp));
	else
	{
		if (!cmd->args[1])
			cmd->args[1] = home;
	}
	if (access(cmd->args[1], F_OK))
	{
		print_in_color(RED, "🚨cd: no such file or directory: ");
		print_in_color(RED, cmd->args[1]);
		printf("\n");
		cmd->exit_status = 1;
		return;
	}
	if (access(cmd->args[1], R_OK))
	{
		print_in_color(RED, "🚨cd: Permission denied\n");
		cmd->exit_status = 1;
		return ;
	}
	if (!cmd->args[1] || chdir(cmd->args[1]) != 0)
	{
		print_in_color(RED, "🚨cd: execution failed!");
		print_in_color(RED, cmd->args[1]);
		printf("\n");
		cmd->exit_status = 1;
	}
	else
	{
		add_to_env(&cmd->env, "PWD", get_pwd());
		add_to_env(&cmd->env, "OLDPWD", current_pwd);
	}
}
