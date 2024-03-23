/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/23 00:04:55 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_fds_if_invalid(int *fds, int pos)
{
	if (fds[pos * 2 + FD_IN] > 2)
		close(fds[pos * 2 + FD_IN]);
	if (fds[pos * 2 + FD_OUT] > 2)
		close(fds[pos * 2 + FD_OUT]);
}

void	exec_external_command(t_command *info, t_cmd_parse **cmds, int pos)
{
	if (get_cmd_path(info, cmds[pos]->args) == 0)
	{
		execve(cmds[pos]->args[0], cmds[pos]->args,
			env_list_to_envp(info->env));
		perror("minishell: ");
	}
	else
	{
		ft_printf_fd("command not found: %s\n", 2, cmds[pos]->args[0]);
		info->exit_status = 127;
	}
}

void	clear_and_free(t_command *info)
{
	rl_clear_history();
	ft_lstclear(&info->env, &free_key_value);
	free_array((void **)info->cmds, &free_cmd_parse);
	free_t_command(info);
}

void	create_child(t_command *info, t_cmd_parse **cmds, int pos)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("fork failed\n");
	if (pid == 0)
	{
		close_irrelevant_fds(info->fds, pos);
		dup2(info->fds[pos * 2 + FD_IN], 0);
		dup2(info->fds[pos * 2 + FD_OUT], 1);
		if (is_builtin(cmds[pos]->args[0]))
			exec_builtin(info, cmds[pos]);
		else if (!cmds[pos]->args[0])
			info->exit_status = 0;
		else if (info->fds[pos * 2 + FD_IN] == -1 || info->fds[pos * 2
				+ FD_OUT] == -1)
			close_fds_if_invalid(info->fds, pos);
		else
			exec_external_command(info, cmds, pos);
		close(info->fds[pos * 2 + FD_IN]);
		close(info->fds[pos * 2 + FD_OUT]);
		clear_and_free(info);
		exit(info->exit_status);
	}
	info->pids[pos] = pid;
}

void	exec_cmd_array(t_command *info, t_cmd_parse **cmds)
{
	int	i;

	if (get_cmd_count(cmds) == 1 && is_builtin(cmds[0]->args[0]))
		exec_single_builtin(info, cmds[0]);
	else
	{
		info->fds = create_pipe_array(cmds);
		info->pids = create_pid_array(cmds);
		manage_redirections(info->fds, cmds);
		info->is_running_cmds = true;
		i = 0;
		while (cmds[i])
		{
			create_child(info, cmds, i);
			i++;
		}
		close_non_std_fds(info->fds);
		info->exit_status = wait_all(info->pids);
		free(info->fds);
		free(info->pids);
	}
	handle_exit_status(info);
	info->is_running_cmds = false;
}
