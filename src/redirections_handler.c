/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:33:55 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/23 01:03:43 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	here_doc(char *del)
{
	int		fd_pipe[2];
	char	*line;
	char	*temp;

	if (pipe(fd_pipe))
		return (-1);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(line, "\n");
		write(fd_pipe[1], temp, ft_strlen(temp));
		free(line);
		free(temp);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

void	open_redirections(t_cmd_parse *cmd, int *fds)
{
	int	i;

	fds[FD_IN] = NO_RED;
	fds[FD_OUT] = NO_RED;
	if (!cmd->redirections)
		return ;
	i = 0;
	while (cmd->redirections[i])
	{
		if (cmd->redirections[i]->redirect_type == R_AMBIGUOUS
			&& handle_ambiguous_redirect(cmd, fds, i) != 0)
			break ;
		else if (cmd->redirections[i]->redirect_type == R_IN_FILE
			&& handle_in_file(cmd, fds, i) != 0)
			break ;
		else if (cmd->redirections[i]->redirect_type == R_OUT_APPEND
			&& handle_out_append(cmd, fds, i) != 0)
			break ;
		else if (cmd->redirections[i]->redirect_type == R_OUT_TRUNC
			&& handle_out_trunc(cmd, fds, i) != 0)
			break ;
		else if (handle_other_redirection(cmd, fds, i) != 0)
			break ;
		i++;
	}
}

void	manage_redirections(int *fds, t_cmd_parse **cmds)
{
	int	io[2];
	int	i;

	i = 0;
	while (cmds[i])
	{
		open_redirections(cmds[i], io);
		if (io[FD_IN] != NO_RED)
		{
			if (fds[i * 2 + FD_IN != 0])
				close(fds[i * 2 + FD_IN]);
			fds[i * 2 + FD_IN] = io[FD_IN];
		}
		if (io[FD_OUT] != NO_RED)
		{
			if (fds[i * 2 + FD_OUT] != 1)
				close(fds[i * 2 + FD_OUT]);
			fds[i * 2 + FD_OUT] = io[FD_OUT];
		}
		i++;
	}
}

int	alloc_redirection_array(t_list *tokens, t_cmd_parse *cmd_p)
{
	int	count;
	int	i;

	count = count_redirect(tokens);
	if (count)
	{
		i = 0;
		cmd_p->redirections = safe_calloc(sizeof(t_redirection *), count + 1);
		while (i < count)
		{
			cmd_p->redirections[i] = safe_calloc(sizeof(t_redirection), 1);
			i++;
		}
	}
	return (count);
}

int	extract_redirections(t_list *tokens, t_cmd_parse *cmd_p)
{
	int	temp;

	temp = alloc_redirection_array(tokens, cmd_p);
	if (temp > 0)
		fill_redirection(tokens, cmd_p);
	else if (temp == -1)
		return (-1);
	return (0);
}
