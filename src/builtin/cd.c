/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 13:26:26 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_and_exec(const char *path, t_command *info)
{
	if (access(path, F_OK))
	{
		ft_printf_fd("cd: no such file or directory: %s\n", 2, path);
		info->exit_status = 1;
		return ;
	}
	if (access(path, R_OK))
	{
		ft_printf_fd( "🚨cd: Permission denied: %s\n", 2, path);
		info->exit_status = 1;
		return ;
	}
	if (chdir(path) != 0)
	{
		ft_printf_fd("🚨cd: execution failed!\n", 2);
		info->exit_status = 1;
		return ;
	}
	add_to_env(&info->env, "OLDPWD", ft_strdup(get_value_with_key(info->env,
				"PWD")));
	add_to_env(&info->env, "PWD", get_pwd());
}

void	oldpwd_not_set(t_command *info)
{
	ft_printf_fd("cd: OLDPWD not set\n", 2);
	info->exit_status = 1;
	return ;
}

void	change_dir(t_cmd_parse *cmd, t_command *info)
{
	const char	*home;
	const char	*path;

	if (cmd->args[2])
	{
		ft_printf_fd("cd: too many arguments\n", 2);
		info->exit_status = 1;
		return ;
	}
	home = get_value_with_key(info->env, "HOME");
	if (!cmd->args[1])
		check_and_exec(home, info);
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		path = get_value_with_key(info->env, "OLDPWD");
		if (!path)
		{
			oldpwd_not_set(info);
			return ;
		}
		check_and_exec(path, info);
		printf("%s\n", get_value_with_key(info->env, "PWD"));
	}
	else
		check_and_exec(cmd->args[1], info);
}
