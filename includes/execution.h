/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:58:00 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd(t_command cmd, char **envp);
int		exec_builtin(t_command cmd, char **envp);
void		exec_pwd(char *cmd);
void		exec_env(t_command *cmd);
void		exec_echo(t_command cmd);
// void	exec_non_builtin(t_command cmd, char **envp);
#endif
