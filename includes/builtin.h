/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:43:37 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:58:24 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft/includes/libft.h"
# include "includes/minishell.h"

typedef struct s_command
{
	char	*name;
	char	*option;
	char	*option2;
	char	**env;
	char	*cmd_str;
	char	*old_pwd;
	char	*pwd;
	int		exit_status;
	char 	**cmd_table;
    int 	fd_input;
    int 	fd_output;
    char 	*outfile;
    char 	*infile;
	t_list	list;
}			t_command;

void		exec_exit(t_command *cmd);
void		parse_cmd(char *str_cmd, t_command *cmd);
void		change_dir(char *str, t_command *cmd);
char		*get_pwd(void);
char		**split_with_delimiter(char *s, char c);
void		open_and_handle_new_terminal(t_command cmd);
int			find_in_env(char *key, char **envp);
void		handle_exit_status(t_command cmd);
void		update_env(t_command *cmd, char *new_var);
void		export_exec(t_command *cmd);
void		exec_unset(t_command *cmd);
#endif
