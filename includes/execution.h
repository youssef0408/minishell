/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 15:42:13 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd_array(t_command *info, t_cmd_parse **cmd);
void	open_redirections(t_cmd_parse *cmd, int *fds);
// int		exec_builtin(t_command info, char **envp);
// void		exec_pwd(char *info);
// void		exec_env(t_command *info);
// void		exec_echo(t_command *info);
// void	exec_non_builtin(t_command info, char **envp);
#endif
