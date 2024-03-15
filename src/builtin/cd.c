/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/15 00:35:54 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_and_exec(const char *path, t_command *info)
{
	if (access(path, F_OK))
	{
		print_in_color(RED, "🚨cd: no such file or directory: ");
		print_in_color(RED, path);
		printf("\n");
		info->exit_status = 1;
		return ;
	}
	if (access(path, R_OK))
	{
		print_in_color(RED, "🚨cd: Permission denied\n");
		info->exit_status = 1;
		return ;
	}
	if (chdir(path) != 0)
	{
		print_in_color(RED, "🚨cd: execution failed!");
		print_in_color(RED, path);
		printf("\n");
		info->exit_status = 1;
		return ;
	}
	add_to_env(&info->env, "OLDPWD", ft_strdup(get_value_with_key(info->env,
				"PWD")));
	add_to_env(&info->env, "PWD", get_pwd());
}

void	change_dir(t_cmd_parse *cmd, t_command *info)
{
	const char	*home;
	char *temp;

	if (cmd->args[2])
	{
		printf("cd: too many arguments\n");
		info->exit_status = 1;
		return ;
	}
	home = get_value_with_key(info->env, "HOME");
	if (!cmd->args[1]) //|| !ft_strcmp(cmd->args[1], "~"))
		check_and_exec(home, info);
	else if (!ft_strcmp(cmd->args[1], "-"))
		check_and_exec(get_value_with_key(info->env, "OLDPWD"), info);
	else
		check_and_exec(cmd->args[1], info);
}
