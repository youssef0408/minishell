/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 16:53:02 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd_array(t_command *info, t_cmd_parse **cmd);
void	open_redirections(t_cmd_parse *cmd, int *fds);
void	handle_ambiguous_redirect(t_cmd_parse *cmd, int *fds, int i);
void	handle_in_file(t_cmd_parse *cmd, int *fds, int i);
void	handle_out_append(t_cmd_parse *cmd, int *fds, int i);
void	handle_out_trunc(t_cmd_parse *cmd, int *fds, int i);
void	handle_other_redirection(t_cmd_parse *cmd, int *fds, int i);
void	manage_redirections(int *fds, t_cmd_parse **cmds);
#endif
