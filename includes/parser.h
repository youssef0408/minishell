/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:11 by bplante           #+#    #+#             */
/*   Updated: 2024/03/23 01:29:23 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "includes/minishell.h"

# define PIPE 0
# define R_HERE_DOC 1
# define R_IN_FILE 2
# define R_OUT_APPEND 3
# define R_OUT_TRUNC 4
# define R_AMBIGUOUS 5

typedef struct s_expansion
{
	const char		*value;
	bool			is_quoted;
	int				start;
	int				len;
	int				key_len;
}					t_expansions;

typedef struct s_redirection
{
	int				redirect_type;
	char			*str;
}					t_redirection;

typedef struct s_cmd_parse
{
	char			**args;
	t_redirection	**redirections;
}					t_cmd_parse;

typedef struct s_litteral_tracker
{
	int				is_lit;
	char			quote;
}					t_lt;

# define META_C 0
# define DATA 1

typedef struct s_key_value
{
	char			*key;
	char			*value;
}					t_key_value;

typedef struct s_token
{
	int				data_type;
	uint64_t		data;
	t_list			*expansions;
	char			*original;
}					t_tkn;

void				expand_vars(t_list *tokens);
void				tokenise(char *input, t_list **tokens);
int					load_vars_per_token(t_list *tokens, t_list *env);
int					extract_redirections(t_list *tokens, t_cmd_parse *cmd_p);
int					parse_input(char *input, t_cmd_parse ***input_parse,
						t_list *env);
// const char			*get_env(char **env, char *key);
bool				lit_track(char c, struct s_litteral_tracker *lt);
bool				is_cmd_block_end(t_list *parsedin);

int					count_split_var(t_list *expansions, char *data);
char				*ft_strndup(const char *src, int n);
int					syntax_errors(t_list *tokens);

void				free_cmd_parse(void *cmd_p);
void				free_token(void *tk);

int					get_cmd_count(t_cmd_parse **cmd_p);

int					count_cmd_blocks(t_list *tokens);
void				create_cmd_array(t_list *tokens, t_cmd_parse ***cmd_p);
bool				is_cmd_block_end(t_list *parsedin);
void				arg_splitter(t_tkn *tk, t_list **args);
void				*lst_to_array(t_list *args);
char				is_string_over(char *input);
int					count_var_space(char *str, t_list **expansions,
						bool *isquoted, int start);
int					count_arg_size(char *str, t_list **expansions,
						bool *isquoted, int start);
bool				lit_track(char c, struct s_litteral_tracker *lt);
char				is_string_over(char *input);
int					alloc_redirection_array(t_list *tokens, t_cmd_parse *cmd_p);
int					extract_redirections(t_list *tokens, t_cmd_parse *cmd_p);
int					find_meta_type(char *str, t_tkn *token);
int					count_spaces(const char *str);
int					store_meta(char *str, t_list **tokens);
int					count_data_len(char *str);
int					store_data(char *str, t_list **tokens);
int					count_redirect(t_list *tokens);
bool				handle_variable_end(bool *is_in_var, t_list **expansions,
						t_expansions **exp);
int					count_split_var(t_list *expansions, char *data);
int					store_redirection_info(t_tkn *tk, t_cmd_parse *cmd_p,
						int type, int i);
int					fill_redirection(t_list *tokens, t_cmd_parse *cmd_p);
void				expand(t_tkn *tk);
void				get_split_args(t_list *tokens, t_cmd_parse *cmd_p);
#endif
