/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:11 by bplante           #+#    #+#             */
/*   Updated: 2024/03/07 13:22:17 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "includes/minishell.h"
# include <stdbool.h>

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
	char			**cmds;
	t_redirection	**redirections;
}					t_cmd_parse;

typedef struct s_litteral_tracker
{
	int				is_lit;
	char			quote;
}					t_lt;

# define META_C 0
# define DATA 1

typedef struct s_token
{
	int				data_type;
	uint64_t		data;
	t_list			*expansions;
	char			*original;
}					t_tkn;

int					expand_vars(t_list *tokens);
int					tokenise(char *input, t_list **tokens);
int					load_vars_per_token(t_list *tokens, char **envp);
int					extract_redirections(t_list *tokens, t_cmd_parse *cmd_p);
int					expand_vars(t_list *tokens);
int					parse_input(char *input, t_cmd_parse ***input_parse,
						char **envp);
const char			*get_env(char **env, char *key);
bool				lit_track(char c, struct s_litteral_tracker *lt);
bool				is_cmd_block_end(t_list *parsedin);

int					count_split_var(t_list *expansions, char *data);
char				*ft_strndup(char *src, int n);
int					ft_strcmp(char *s1, char *s2);

#endif
