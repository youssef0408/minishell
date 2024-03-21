/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/20 23:29:18 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd_array(t_command *info, t_cmd_parse **cmd);
void	open_redirections(t_cmd_parse *cmd, int *fds);
int		handle_ambiguous_redirect(t_cmd_parse *cmd, int *fds, int i);
int		handle_in_file(t_cmd_parse *cmd, int *fds, int i);
int		handle_out_append(t_cmd_parse *cmd, int *fds, int i);
int		handle_out_trunc(t_cmd_parse *cmd, int *fds, int i);
int		handle_other_redirection(t_cmd_parse *cmd, int *fds, int i);
void	manage_redirections(int *fds, t_cmd_parse **cmds);
#endif
