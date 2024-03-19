/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 16:37:56 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	*create_pipe_array(t_cmd_parse **cmds)
{
	int	size;
	int	*fd_array;
	int	i;
	int	temp;

	size = get_cmd_count(cmds) * 2;
	fd_array = safe_calloc(size + 1, sizeof(int));
	fd_array[size] = EOINTA;
	fd_array[size - 1] = 1;
	i = 1;
	while (i < size - 1)
	{
		pipe(&fd_array[i]);
		temp = fd_array[i];
		fd_array[i] = fd_array[i + 1];
		fd_array[i + 1] = temp;
		i += 2;
	}
	return (fd_array);
}

int	*create_pid_array(t_cmd_parse **cmds)
{
	int	size;
	int	*pids;

	size = get_cmd_count(cmds);
	pids = safe_calloc(size + 1, sizeof(int));
	pids[size] = EOINTA;
	return (pids);
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
		{
			info->exit_status = 0;
		}
		else
		{
			if (get_cmd_path(info, cmds[pos]->args) == 0)
			{
				execve(cmds[pos]->args[0], cmds[pos]->args,
					env_list_to_envp(info->env));
				perror("minishell: ");
			}
			else
			{
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, cmds[pos]->args[0]);
				printf("\n");
				info->exit_status = 127;
			}
		}
		exit(info->exit_status);
	}
	info->pids[pos] = pid;
}

int	wait_all(int *pids)
{
	int	i;
	int	exit_st;

	i = 0;
	while (pids[i] != EOINTA)
	{
		waitpid(pids[i], &exit_st, 0);
		i++;
	}
	return (exit_st / 256);
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
