/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/17 19:13:23 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(char *str, t_command *cmd)
{
	char	*home;
	char	*current_pwd;
	char	*tmp;

	cmd->exit_status = 0;
	tmp = cmd->env[find_in_env("OLDPWD", cmd->env)];
	current_pwd = get_pwd();
	home = getenv("HOME");
	if (!str || !ft_strcmp(str, "") || !ft_strcmp(str, "~"))
		str = home;
	else if (!ft_strcmp(str, "-"))
		str = ft_substr(tmp, 7, ft_strlen(tmp));
	else
	{
		str = parse_env2(*cmd, str);
		if (!str || !ft_strcmp(str, ""))
			str = home;
	}
	if (access(str, F_OK))
	{
		print_in_color(RED, "🚨cd: no such file or directory: ");
		print_in_color(RED, str);
		printf("\n");
		cmd->exit_status = 1;
		return;
	}
	if (access(str, R_OK))
	{
		print_in_color(RED, "🚨cd: Permission denied\n");
		cmd->exit_status = 1;
		return ;
	}
	if (!str || !ft_strcmp(str, " ") || chdir(str) != 0)
	{
		print_in_color(RED, "🚨cd: execution failed!");
		print_in_color(RED, str);
		printf("\n");
		cmd->exit_status = 1;
	}
	else
	{
		cmd->env[find_in_env("PWD", cmd->env)] = ft_strjoin("PWD=", get_pwd());
		cmd->env[find_in_env("OLDPWD", cmd->env)] = ft_strjoin("OLDPWD=",
				current_pwd);
	}
}
