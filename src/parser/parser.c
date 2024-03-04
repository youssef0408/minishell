/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:40 by bplante				#+#    #+#             */
/*   Updated: 2024/02/22 12:38:20 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#define PIPE 0
#define R_HERE_DOC 1
#define R_IN_FILE 2
#define R_OUT_APPEND 3
#define R_OUT_TRUNC 4
#define R_AMBIGUOUS 5

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

#define META_C 0
#define DATA 1

typedef struct s_token
{
	int				data_type;
	uint64_t		data;
	t_list			*expansions;
	char			*original;
}					t_tkn;

const char	*get_env(char **env, char *key)
{
	int		i;
	int		j;
	char	*sub_str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub_str = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub_str, key) == 0)
		{
			free(sub_str);
			return (&env[i][j] + 1);
		}
		free(sub_str);
		i++;
	}
	return (NULL);
}

bool	lit_track(char c, struct s_litteral_tracker *lt)
{
	if (c == '\\' && ((lt->quote == 0 && lt->is_lit == 0) || (lt->quote == '\"'
				&& lt->is_lit == 1)))
	{
		lt->is_lit++;
		return (false);
	}
	else if (lt->is_lit == 0 && (c == '\'' || c == '\"') && lt->quote == 0)
	{
		lt->quote = c;
		lt->is_lit++;
		return (false);
	}
	else if (lt->is_lit == 1 && c == lt->quote)
	{
		lt->is_lit--;
		lt->quote = 0;
		return (false);
	}
	else if (lt->is_lit == 2 || (lt->is_lit == 1 && lt->quote == 0))
		lt->is_lit--;
	else if (lt->is_lit == 0)
		return (false);
	return (true);
}

// TODO check if string ends with non-litteral pipe
char	is_string_over(char *input)
{
	struct s_litteral_tracker	lt;
	int							i;

	lt.is_lit = 0;
	lt.quote = 0;
	i = 0;
	while (input[i])
	{
		lit_track(input[i], &lt);
		i++;
	}
	if (lt.is_lit >= 1)
	{
		if (lt.quote != 0)
			return (lt.quote);
		else
			return ('\\');
	}
	return (0);
}

int	count_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

int	find_meta_type(char *str, t_tkn *token)
{
	if (str[0] == '|')
	{
		token->data = PIPE;
		return (1);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			token->data = R_HERE_DOC;
			return (2);
		}
		token->data = R_IN_FILE;
		return (1);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
		{
			token->data = R_OUT_APPEND;
			return (2);
		}
		token->data = R_OUT_TRUNC;
		return (1);
	}
}

int	store_meta(char *str, t_list **tokens)
{
	t_list	*new;
	int		i;
	t_tkn	*token;

	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (-1);
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (-1);
	}
	token->data_type = META_C;
	i = find_meta_type(str, token);
	ft_lstadd_back(tokens, new);
	return (i);
}

int	count_data_len(char *str)
{
	int							i;
	struct s_litteral_tracker	lt;

	lt.is_lit = 0;
	lt.quote = 0;
	i = 0;
	while (((!lt.is_lit && !(str[i] == ' ' || str[i] == '|' || str[i] == '<'
					|| str[i] == '>')) || lt.is_lit > 0) && str[i])
	{
		lit_track(str[i], &lt);
		i++;
	}
	return (i);
}

int	store_data(char *str, t_list **tokens)
{
	t_tkn	*token;
	t_list	*new;
	int		len;

	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (-1);
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (-1);
	}
	token->data_type = DATA;
	len = count_data_len(str);
	token->data = (uint64_t)ft_strndup(str, len);
	if (!token->data)
	{
		free(token);
		free(new);
		return (-1);
	}
	ft_lstadd_back(tokens, new);
	return (len);
}

int	tokenise(char *input, t_list **tokens)
{
	int	i;
	int	temp;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			temp = store_meta(&input[i], tokens);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		else if (input[i] != ' ')
		{
			temp = store_data(&input[i], tokens);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		i += count_spaces(&input[i]);
	}
	return (0);
}

void	free_token(void *tk)
{
	t_tkn	*token;

	if (!tk)
		return ;
	token = (t_tkn *)tk;
	if (token->data_type == DATA)
	{
		if (token->data)
			free((void *)token->data);
	}
	free(token);
}

int	count_cmd_blocks(t_list *tokens)
{
	t_tkn	*tk;
	int		block_count;

	if (!tokens)
		return (0);
	block_count = 1;
	while (tokens->next)
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == META_C && tk->data == PIPE)
			block_count++;
		tokens = tokens->next;
	}
	return (block_count);
}

int	create_cmd_parse_array(t_list *tokens, t_cmd_parse ***cmd_p)
{
	int	cmd_count;
	int	i;

	cmd_count = count_cmd_blocks(tokens);
	if (cmd_count == 0)
	{
		**cmd_p = NULL;
		return (0);
	}
	*cmd_p = (t_cmd_parse **)ft_calloc(sizeof(t_cmd_parse *), cmd_count + 1);
	if (!*cmd_p)
		return (-1);
	i = 0;
	while (i < cmd_count)
	{
		*cmd_p[i] = ft_calloc(sizeof(t_cmd_parse), 1);
		// TODO check malloc return value
		return (i++);
	}
	return (0);
}

bool	is_redirection(void *token)
{
	t_tkn	*tk;

	tk = (t_tkn *)token;
	if (tk->data_type == META_C && tk->data != PIPE)
		return (true);
	return (false);
}

bool	is_pipe(void *token)
{
	t_tkn	*tk;

	tk = (t_tkn *)token;
	if (tk->data_type == META_C && tk->data == PIPE)
		return (true);
	return (false);
}

bool	is_cmd_block_end(t_list *parsedin)
{
	if (!parsedin)
		return (true);
	if (((t_tkn *)parsedin->content)->data_type == META_C
		&& ((t_tkn *)parsedin->content)->data == PIPE)
		return (true);
	return (false);
}

int	count_redirect(t_list *tokens)
{
	t_tkn	*tk;
	int		count;

	count = 0;
	while (!is_cmd_block_end(tokens))
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == META_C && tk->data == PIPE)
			break ;
		if (tk->data_type == META_C && tk->data != PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	count_split_var(t_list *expansions, char *data)
{
	int				i;
	bool			has_char;
	t_expansions	*exp;
	bool			is_in_var;
	int				count;

	count = 0;
	has_char = false;
	is_in_var = false;
	if (!expansions)
		return (1);
	i = 0;
	exp = (t_expansions *)expansions->content;
	while (data[i] && expansions)
	{
		if (is_in_var && !(i >= exp->start && i < exp->start + exp->len))
		{
			is_in_var = false;
			expansions = expansions->next;
			if (expansions)
				exp = (t_expansions *)expansions->content;
			else
				break ;
		}
		if (i >= exp->start && i < exp->start + exp->len)
			is_in_var = true;
		if (has_char && is_in_var && !exp->is_quoted && data[i] == ' ')
		{
			count++;
			has_char = false;
		}
		else if (!has_char && ((is_in_var && !exp->is_quoted && data[i] != ' ')
				|| exp->is_quoted))
		{
			has_char = true;
		}
		i++;
	}
	if (has_char)
		count++;
	else if (!has_char && data[i + 1] != 0)
		count++;
	return (count);
}

int	store_redirection_info(t_tkn *tk, t_cmd_parse *cmd_p, int type, int i)
{
	int	count;

	count = 1;
	if (tk->data != R_HERE_DOC)
		count = count_split_var(tk->expansions, (char *)tk->data);
	cmd_p->redirections[i]->redirect_type = type;
	if (count != 1)
	{
		cmd_p->redirections[i]->redirect_type = R_AMBIGUOUS;
		cmd_p->redirections[i]->str = ft_strdup(tk->original);
	}
	cmd_p->redirections[i]->str = ft_strdup((char *)tk->data);
	// TODO check alloc return value
	return (0);
}

int	fill_redirection(t_list *tokens, t_cmd_parse *cmd_p)
{
	t_tkn	*tk;
	int		red_type;
	int		count;

	count = 0;
	red_type = 0;
	while (!is_cmd_block_end(tokens))
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == META_C)
			red_type = ((t_tkn *)tokens->content)->data;
		else if (red_type)
		{
			store_redirection_info((t_tkn *)tokens->content, cmd_p, red_type,
				count);
			red_type = 0;
			count++;
		}
		tokens = tokens->next;
	}
	return (0);
}

int	alloc_redirection_array(t_list *tokens, t_cmd_parse *cmd_p)
{
	int	count;
	int	i;

	count = count_redirect(tokens);
	if (count)
	{
		i = 0;
		cmd_p->redirections = ft_calloc(sizeof(t_redirection *), count + 1);
		while (i < count)
		{
			cmd_p->redirections[i] = ft_calloc(sizeof(t_redirection), 1);
			// TODO check alloc return value
			i++;
		}
	}
	return (count);
}

int	get_redirections(t_list *tokens, t_cmd_parse *cmd_p)
{
	int	temp;

	temp = alloc_redirection_array(tokens, cmd_p);
	if (temp > 0)
		fill_redirection(tokens, cmd_p);
	else if (temp == -1)
		return (-1);
	return (0);
}

int	fill_cmd_struct(t_list *tokens, t_cmd_parse *cmd_p, char **envp)
{
	get_redirections(tokens, cmd_p);
}

int	token_to_cmd(t_list *tokens, t_cmd_parse ***cmd_p, char **envp)
{
	int		i;
	t_list	*list_start;

	list_start = tokens;
	create_cmd_parse_array(tokens, cmd_p);
	i = 0;
	while ((*cmd_p)[i])
	{
		fill_cmd_struct(tokens, **cmd_p, envp);
		i++;
	}
}

// create expantion struct and and add if its quote or not, add start if isnt
int	store_value_from_env(char *str, char **envp, t_tkn *tk, int start)
{
	int				i;
	char			*key;
	const char		*value;
	t_list			*new;
	t_expansions	*expansion;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	key = ft_strndup(str, i);
	value = get_env(envp, key);
	if (!value)
		value = ft_strdup("");
	expansion = ft_calloc(sizeof(t_expansions), 1);
	// TODO verify alloc return value
	expansion->value = value;
	expansion->start = start;
	expansion->len = ft_strlen(value);
	expansion->key_len = ft_strlen(key);
	new = ft_lstnew((void *)expansion);
	ft_lstadd_back(&tk->expansions, new);
	free(key);
	return (i);
}
// create expantion struct and and add if its quote or not, add start if isnt
// int store_value_from_env(char *strstart
int	check_and_fetch(t_tkn *token, char **envp)
{
	char						*data;
	struct s_litteral_tracker	lt;
	int							i;

	lt.is_lit = 0;
	lt.quote = 0;
	data = (char *)token->data;
	i = 0;
	while (data[i])
	{
		if (data[i] == '$' && (lt.is_lit == 0 || (lt.quote == '\"'
					&& lt.is_lit == 1)))
		{
			i += store_value_from_env(&data[i + 1], envp, token, i);
		}
		lit_track(data[i], &lt);
		i++;
	}
	return (0);
}

int	load_vars_per_token(t_list *tokens, char **envp)
{
	while (tokens)
	{
		if (((t_tkn *)tokens->content)->data_type == DATA)
		{
			check_and_fetch((t_tkn *)tokens->content, envp);
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	is_printed(char *str, struct s_litteral_tracker *lt)
{
	lit_track(str[0], lt);
	if (lt->is_lit == 1 && lt->quote == str[0])
		return (false);
	if (lt->is_lit == 0 && (str[0] == '\'' || str[0] == '\"'))
		return (false);
	if (str[0] == '\\' && ((lt->is_lit == 0) || (lt->is_lit == 1
				&& str[1] == '\"' || str[1] == '$' || str[1] == '\\')))
		return (false);
	return (true);
}

int	count_new_data_size(char *str, t_list *expansions)
{
	struct s_litteral_tracker	lt;
	int							i;
	int							count;

	lt.is_lit = 0;
	lt.quote = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && (lt.is_lit == 0 || (lt.quote == '\"'
					&& lt.is_lit == 1)))
		{
			((t_expansions *)expansions->content)->is_quoted = lt.is_lit;
			((t_expansions *)expansions->content)->start = count;
			count += ((t_expansions *)expansions->content)->len;
			i += ((t_expansions *)expansions->content)->key_len;
			expansions = expansions->next;
		}
		else if (is_printed(&str[i], &lt))
			count++;
		i++;
	}
	return (count);
}

int	fill_new_data(char *new_string, char *original, t_list *expansions)
{
	struct s_litteral_tracker	lt;
	int							i;
	int							j;

	j = 0;
	i = 0;
	lt.is_lit = 0;
	lt.quote = 0;
	while (original[j])
	{
		if (original[j] == '$' && (lt.is_lit == 0 || (lt.quote == '\"'
					&& lt.is_lit == 1)))
		{
			ft_strcpy(&new_string[i],
				((t_expansions *)expansions->content)->value);
			j += ((t_expansions *)expansions->content)->key_len;
			i += ((t_expansions *)expansions->content)->len;
			expansions = expansions->next;
		}
		else if (is_printed(&original[j], &lt))
			new_string[i++] = original[j];
		j++;
	}
}

int	expand(t_tkn *tk)
{
	int	count;

	tk->original = (char *)tk->data;
	count = count_new_data_size((char *)tk->data, tk->expansions);
	tk->data = (uint64_t)ft_calloc(sizeof(char), count + 1);
	fill_new_data((char *)tk->data, tk->original, tk->expansions);
}

int	expand_vars(t_list *tokens)
{
	t_tkn	*tk;

	while (tokens)
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == DATA)
			expand(tk);
		tokens = tokens->next;
	}
}

int	parse_input(char *input, t_cmd_parse ***input_parse, char **envp)
{
	t_list	*tokens;

	if (is_string_over(input) != 0)
	{
		// TODO print error message
		return (-1);
	}
	tokens = NULL;
	if (tokenise(input, &tokens) == -1)
	{
		ft_lstclear(&tokens, &free_token);
		return (-1);
	}
	// TODO check for syntax error (token that needs data after has token instead)
	load_vars_per_token(tokens, envp);
	expand_vars(tokens);
	token_to_cmd(tokens, input_parse, envp);
}
