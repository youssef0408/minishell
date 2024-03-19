/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:17:22 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 16:40:46 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_ambiguous_redirect(t_cmd_parse *cmd, int *fds, int i)
{
	printf("%s: ambiguous redirect\n", cmd->redirections[i]->str);
	fds[FD_IN] = -1;
	fds[FD_OUT] = -1;
}

void	handle_in_file(t_cmd_parse *cmd, int *fds, int i)
{
	if (fds[FD_IN] != NO_RED)
		close(fds[FD_IN]);
	fds[FD_IN] = open(cmd->redirections[i]->str, O_RDONLY);
	if (fds[FD_IN] == -1)
		printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
}

void	handle_out_append(t_cmd_parse *cmd, int *fds, int i)
{
	if (fds[FD_OUT] != NO_RED)
		close(fds[FD_OUT]);
	fds[FD_OUT] = open(cmd->redirections[i]->str, O_WRONLY | O_APPEND | O_CREAT,
			0644);
	if (fds[FD_OUT] == -1)
		printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
}

void	handle_out_trunc(t_cmd_parse *cmd, int *fds, int i)
{
	if (fds[FD_OUT] != NO_RED)
		close(fds[FD_OUT]);
	fds[FD_OUT] = open(cmd->redirections[i]->str, O_WRONLY | O_TRUNC | O_CREAT,
			0644);
	if (fds[FD_OUT] == -1)
		printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
}

void	handle_other_redirection(t_cmd_parse *cmd, int *fds, int i)
{
	if (fds[FD_IN] != NO_RED)
		close(fds[FD_IN]);
	fds[FD_IN] = here_doc(cmd->redirections[i]->str);
}

// TODO:CHECK NEW OPEN_REDIRECTION FUNC.
// TODO:RM OLD FUNC.

// void	open_redirections(t_cmd_parse *cmd, int *fds)
// {
// 	int	i;

// 	fds[FD_IN] = NO_RED;
// 	fds[FD_OUT] = NO_RED;
// 	if (!cmd->redirections)
// 		return ;
// 	i = 0;
// 	while (cmd->redirections[i])
// 	{
// 		if (cmd->redirections[i]->redirect_type == R_AMBIGUOUS)
// 		{
// 			printf("%s: ambiguous redirect\n", cmd->redirections[i]->str);
// 			fds[FD_IN] = -1;
// 			fds[FD_OUT] = -1;
// 			break ;
// 		}
// 		else if (cmd->redirections[i]->redirect_type == R_IN_FILE)
// 		{
// 			if (fds[FD_IN] != NO_RED)
// 				close(fds[FD_IN]);
// 			fds[FD_IN] = open(cmd->redirections[i]->str, O_RDONLY);
// 			if (fds[FD_IN] == -1)
// 			{
// 				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
// 				break ;
// 			}
// 		}
// 		else if (cmd->redirections[i]->redirect_type == R_OUT_APPEND)
// 		{
// 			if (fds[FD_OUT] != NO_RED)
// 				close(fds[FD_OUT]);
// 			fds[FD_OUT] = open(cmd->redirections[i]->str,
// 					O_WRONLY | O_APPEND | O_CREAT, 0644);
// 			if (fds[FD_OUT] == -1)
// 			{
// 				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
// 				break ;
// 			}
// 		}
// 		else if (cmd->redirections[i]->redirect_type == R_OUT_TRUNC)
// 		{
// 			if (fds[FD_OUT] != NO_RED)
// 				close(fds[FD_OUT]);
// 			fds[FD_OUT] = open(cmd->redirections[i]->str,
// 					O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 			if (fds[FD_OUT] == -1)
// 			{
// 				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
// 				break ;
// 			}
// 		}
// 		else
// 		{
// 			if (fds[FD_IN] != NO_RED)
// 				close(fds[FD_IN]);
// 			fds[FD_IN] = here_doc(cmd->redirections[i]->str);
// 		}
// 		i++;
// 	}
// }
