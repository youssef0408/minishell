/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:20 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/17 12:43:24 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "includes/minishell.h"

void	exec_cmd_array(t_command *info, t_cmd_parse **cmd);
// int		exec_builtin(t_command cmd, char **envp);
// void		exec_pwd(char *cmd);
// void		exec_env(t_command *cmd);
// void		exec_echo(t_command *cmd);
// void	exec_non_builtin(t_command cmd, char **envp);
#endif
