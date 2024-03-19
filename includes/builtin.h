/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:43:37 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 16:51:33 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "includes/minishell.h"

typedef struct s_command
{
	int		exit_status;
	t_list	*env;
	int		*pids;
	int		*fds;
	bool	is_running_cmds;
}			t_command;

void		change_dir(t_cmd_parse *cmd, t_command *info);
char		*get_pwd(void);
void		set_shlvl(t_list **env);
void		handle_exit_status(t_command *info);
void		exec_unset(t_command *info, t_cmd_parse *cmd);
bool		is_valid_var_id(char *id);
void		exec_pwd(t_cmd_parse *cmd);
void		exec_env(t_command *info, t_cmd_parse *cmd);
void		exec_exit(t_command *info, t_cmd_parse *cmd);
void		exec_echo(t_cmd_parse *cmd);
int			exec_builtin(t_command *info, t_cmd_parse *cmd);
void		handle_export_error(t_command *info, t_cmd_parse *cmd, int i);
void		export_exec(t_command *info, t_cmd_parse *cmd);
void		process_export_with_assignment(t_command *info, t_cmd_parse *cmd,
				int index);
void		process_export_without_assignment(t_command *info, t_cmd_parse *cmd,
				int index);
char		*get_key_from_assignment(char *arg);
char		*get_value_from_assignment(char *arg, char *key);
bool		is_builtin(char *name);
void		exec_single_builtin(t_command *info, t_cmd_parse *cmd);

#endif
