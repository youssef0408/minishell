/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:33:01 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/11 15:40:43 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	init_cmd(char *str_cmd, t_command *cmd)
{
	char	**tab_cmd;
	int		i;
	char	*tmp;

	tab_cmd = ft_split(str_cmd, ' ');
	if (!tab_cmd)
		return ;
	cmd->name = tab_cmd[0];
	cmd->exit_status = 0;
	cmd->option = "";
	cmd->option2 = "";
	cmd->cmd_str = str_cmd;
	if (!tab_cmd[1])
		return ;
	cmd->option = tab_cmd[1];


	
	i = 2;
	tmp = "";
	if (!tab_cmd[2])
		return ;
	while (tab_cmd[i])
	{
		if (tab_cmd[i])
			tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, tab_cmd[i]);
		i++;
	}
	cmd->option2 = tmp;
}

int	exec_builtin(t_command cmd, char **envp)
{
	int		i;
	char	*tmp;
	int		result;

	i = 0;
	if (!ft_strcmp(cmd.name, "pwd"))
		exec_pwd(cmd.option);
	else if (!ft_strcmp(cmd.name, "./minishell"))
	{
		open_and_handle_new_terminal(cmd);
		handle_exit_status(cmd);
		return 0;
	}
	else if (!ft_strcmp(cmd.name, "cd"))
	{
		change_dir(cmd.option, &cmd);
		handle_exit_status(cmd);
		return 0;
	}
	else if (!ft_strcmp(cmd.name, "export"))
	{
		export_exec(&cmd);
		handle_exit_status(cmd);
		return(0);	
	}
	else if (!ft_strcmp(cmd.name, "env"))
		{
			exec_env(&cmd);
			handle_exit_status(cmd);
			return(0);
		}
	else if (!ft_strcmp(cmd.name, "exit"))
		exec_exit(&cmd);
	else if (!ft_strcmp(cmd.name, "echo"))
		exec_echo(&cmd);
	else if (!ft_strcmp(cmd.name, "unset"))
		exec_unset(&cmd);
	else
		return (1);
	cmd.exit_status=0;
	handle_exit_status(cmd);
	return (0);
}
