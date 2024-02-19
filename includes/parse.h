/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:00:23 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/19 13:10:11 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "builtin.h"
# include "minishell.h"
# include <stdbool.h>

char	*parse_env(char *str);
char	*parse_env2(t_command cmd, char *str);
// void token_parser(const t_list *token_list);
// t_list *parser(t_list *cmd_list, const t_list *token_list);
// void lexer_error(int c, t_list *head, void (*del)(void *));

// void exec_leon(t_list *cmd_list);
// void update_cmd_list(t_list *cmd_list, char **envp);
// void process_fork(t_list *cmd_list, int lst_size);

void	syntax_error(t_command *cmd);
void	void_del(void *content);
int		exit_tokenizer(t_command *cmd, t_list **tokens);
int		check_syntax_error(t_list **tokens, t_command *cmd);
int		handle_redirection(t_list **tokens, t_command *cmd, t_list **ptr);
int		clean_tokens(t_list **tokens, t_command *cmd);

char	**replace_redirection_operators(char **table);
char	**command_table_creation(t_list **tokens, t_command *cmd);
bool	quotes_are_not_closed(char *str, t_command *cmd);
char	**ft_tokenizer(char *str, t_command *cmd);
int		handle_output_redirection(t_list **tokens, t_command *cmd,
			t_list **ptr);
int		handle_input_redirection(t_list **tokens, t_command *cmd, t_list **ptr);
int		handle_redirection(t_list **tokens, t_command *cmd, t_list **ptr);
int		step_through_quote(char *str, char quote);
int		create_token(t_list **tokenlist, int *i, int *pos, char *str);
int		split_tokens(t_list **tokenlist, int *i, int *pos, char *str);
void	tokenize(char *str, t_command *cmd, t_list **tokens);

#endif
