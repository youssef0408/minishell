/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:43:37 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/14 16:52:23 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "includes/minishell.h"

typedef struct s_command
{
	int			exit_status;
	t_list		*env;
	t_cmd_parse	**parsed;
	t_list		list;
}				t_command;

void			init_cmd(char *str_cmd, t_command *cmd);
void			change_dir(t_cmd_parse *cmd, t_command *info);
char			*get_pwd(void);
char			**split_with_delimiter(char *s, char c);
void			set_shlvl(t_list **env);
void			handle_exit_status(t_command *info);
void			export_exec(t_command *info, t_cmd_parse *cmd);
void			exec_unset(t_command *info, t_cmd_parse *cmd);
bool			is_valid_var_id(char *id);
void			exec_pwd(t_cmd_parse *cmd);
void			exec_env(t_command *info, t_cmd_parse *cmd);
void			exec_exit(t_command *info, t_cmd_parse *cmd);
void			exec_echo(t_cmd_parse *cmd);
int				exec_builtin(t_command *info, t_cmd_parse *cmd);

#endif
