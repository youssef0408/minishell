/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/07 14:25:04 by bplante          ###   ########.fr       */
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
