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
#define R_ERROR 5

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

struct				s_litteral_tracker
{
	int				is_lit;
	char			quote;
};

#define META_C 0
#define DATA 1

struct				s_token
{
	int				data_type;
	uint64_t		data;
};

bool	is_litteral(char c, struct s_litteral_tracker *lt)
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
		is_litteral(input[i], &lt);
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

int	count_spaces(char *str)
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

int	find_meta_type(char *str, struct s_token *token)
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
	t_list			*new;
	int				i;
	struct s_token	*token;

	token = ft_calloc(1, sizeof(struct s_token));
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
		is_litteral(str[i], &lt);
		i++;
	}
	return (i);
}

int	store_data(char *str, t_list **tokens)
{
	struct s_token	*token;
	t_list			*new;
	int				len;

	token = ft_calloc(1, sizeof(struct s_token));
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
	struct s_token	*token;

	if (!tk)
		return ;
	token = (struct s_token *)tk;
	if (token->data_type == DATA)
	{
		if (token->data)
			free((void *)token->data);
	}
	free(token);
}

int	count_cmd_blocks(t_list *parsed_in)
{
	struct s_token	*tk;
	int				block_count;

	if (!parsed_in)
		return (0);
	block_count = 1;
	while (parsed_in->next)
	{
		tk = (struct s_token *)parsed_in->content;
		if (tk->data_type == META_C && tk->data == PIPE)
			block_count++;
		parsed_in = parsed_in->next;
	}
	return (block_count);
}

int	create_cmd_parse_array(t_list *parsed_in, t_cmd_parse ***cmd_p)
{
	int	cmd_count;
	int	i;

	cmd_count = count_cmd_blocks(parsed_in);
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
	struct s_token	*tk;

	tk = (struct s_token *)token;
	if (tk->data_type == META_C && tk->data != PIPE)
		return (true);
	return (false);
}

bool	is_pipe(void *token)
{
	struct s_token	*tk;

	tk = (struct s_token *)token;
	if (tk->data_type == META_C && tk->data == PIPE)
		return (true);
	return (false);
}

int	count_redirect(t_list *parsed_in)
{
	struct s_token	*tk;
	int				count;

	count = 0;
	while (parsed_in)
	{
		tk = (struct s_token *)parsed_in->content;
		if (tk->data_type == META_C && tk->data == PIPE)
			break ;
		if (tk->data_type == META_C && tk->data != PIPE)
			count++;
		parsed_in = parsed_in->next;
	}
	return (count);
}

int	store_redirection_info(t_list *parsed_in, t_cmd_parse *cmd_p, int type,
		int i)
{
	struct s_token	*tk;

	tk = (struct s_token *)parsed_in->content;
	cmd_p->redirections[i]->redirect_type = type;
	cmd_p->redirections[i]->str = ft_strdup((char *)tk->data);
	// TODO check alloc return value
	return (0);
}

int	fill_redirection(t_list *parsed_in, t_cmd_parse *cmd_p)
{
	struct s_token	*tk;
	int				red_type;
	int				count;

	count = 0;
	red_type = 0;
	while (parsed_in)
	{
		tk = (struct s_token *)parsed_in->content;
		if (tk->data_type == META_C)
		{
			if (tk->data == PIPE)
				break ;
			else
				red_type = ((struct s_token *)parsed_in->content)->data;
		}
		else if (red_type)
		{
			store_redirection_info(parsed_in, cmd_p, red_type, count);
			red_type = 0;
			count++;
		}
		parsed_in = parsed_in->next;
	}
	return (0);
}

int	alloc_redirection_array(t_list *parsed_in, t_cmd_parse *cmd_p)
{
	int	count;
	int	i;

	count = count_redirect(parsed_in);
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

int	get_redirections(t_list *parsed_in, t_cmd_parse *cmd_p)
{
	int	temp;

	temp = alloc_redirection_array(parsed_in, cmd_p);
	if (temp > 0)
		fill_redirection(parsed_in, cmd_p);
	else if (temp == -1)
		return (-1);
	return (0);
}

int	fill_cmd_struct(t_list *parsed_in, t_cmd_parse *cmd_p, char **envp)
{
	
	get_redirections(parsed_in, cmd_p);
	
}

int	token_to_cmd(t_list *parsed_in, t_cmd_parse ***cmd_p, char **envp)
{
	int		i;
	t_list	*list_start;

	list_start = parsed_in;
	create_cmd_parse_array(parsed_in, cmd_p);
	i = 0;
	while (*cmd_p[i])
	{
		fill_cmd_struct(parsed_in, **cmd_p, envp);
		i++;
	}
}

int	parse_input(char *input, t_cmd_parse ***input_parse, char **envp)
{
	t_list *tokens;
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
	token_to_cmd(tokens, input_parse, envp);
}