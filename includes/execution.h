/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/25 12:39:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd_array(t_command *info, t_cmd_parse **cmd);
void	open_redirections(t_cmd_parse *cmd, int *fds);
int		ambiguous_redirect(t_cmd_parse *cmd, int *fds, int i);
int		handle_in_file(t_cmd_parse *cmd, int *fds, int i);
int		handle_out_append(t_cmd_parse *cmd, int *fds, int i);
int		handle_out_trunc(t_cmd_parse *cmd, int *fds, int i);
int		handle_other_redirection(t_cmd_parse *cmd, int *fds, int i);
void	manage_redirections(int *fds, t_cmd_parse **cmds);
int		*create_pipe_array(t_cmd_parse **cmds);
int		*create_pid_array(t_cmd_parse **cmds);
int		wait_all(int *pids);
void	free_key_value(void *key_value);
char	*join_key_value(t_list *node);
char	*get_key(const char *str);
t_list	*convert_envp(char **envp);
t_list	*get_kv_node(t_list *env, const char *key);
#endif
