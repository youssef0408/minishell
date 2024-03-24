/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:25:02 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/24 15:43:45 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	redirect_stdin(int new_stdin)
{
	int	old_stdin;

	old_stdin = dup(STDIN_FILENO);
	dup2(new_stdin, STDIN_FILENO);
	close(new_stdin);
	return (old_stdin);
}

int	redirect_stdout(int new_stdout)
{
	int	old_stdout;

	old_stdout = dup(STDOUT_FILENO);
	dup2(new_stdout, STDOUT_FILENO);
	close(new_stdout);
	return (old_stdout);
}

// Fonction pour restaurer stdin
void	restore_stdin(int old_stdin)
{
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
}

// Fonction pour restaurer stdout
void	restore_stdout(int old_stdout)
{
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
}

void	exec_single_builtin(t_command *info, t_cmd_parse *cmd)
{
	int	fds[2];
	int	old_std_out;
	int	old_std_in;

	old_std_in = -1;
	old_std_out = -1;
	open_redirections(cmd, fds);
	if (fds[FD_IN] == -1 || fds[FD_OUT] == -1)
	{
		info->exit_status = 1;
		return ;
	}
	if (fds[FD_IN] != NO_RED)
		old_std_in = redirect_stdin(fds[FD_IN]);
	if (fds[FD_OUT] != NO_RED)
		old_std_out = redirect_stdout(fds[FD_OUT]);
	exec_builtin(info, cmd);
	if (fds[FD_IN] != NO_RED)
		restore_stdin(old_std_in);
	if (fds[FD_OUT] != NO_RED)
		restore_stdout(old_std_out);
}
