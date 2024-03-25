/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:02:07 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/25 01:03:46 by bplante          ###   ########.fr       */
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

int	wait_all(int *pids)
{
	int	i;
	int	exit_st;

	i = 0;
	while (pids[i] != EOINTA)
	{
		if (pids[i] == NO_CHILD)
			exit_st = 0;
		else
			waitpid(pids[i], &exit_st, 0);
		i++;
	}
	return (exit_st / 256);
}
