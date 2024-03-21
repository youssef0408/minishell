/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:40 by bplante				#+#    #+#        */
/*   Updated: 2024/02/22 12:38:20 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

int	count_cmd_blocks(t_list *tokens)
{
	t_tkn	*tk;
	int		block_count;

	if (!tokens)
		return (1);
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

void	create_cmd_array(t_list *tokens, t_cmd_parse ***cmd_p)
{
	int	cmd_count;
	int	i;

	cmd_count = count_cmd_blocks(tokens);
	*cmd_p = (t_cmd_parse **)safe_calloc(sizeof(t_cmd_parse *), cmd_count + 1);
	i = 0;
	while (i < cmd_count)
	{
		(*cmd_p)[i] = safe_calloc(sizeof(t_cmd_parse), 1);
		i++;
	}
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

int	count_arg_size(char *str, t_list **expansions, bool *isquoted, int start)
{
	int				i;
	t_expansions	*exp;

	i = start;
	exp = (t_expansions *)(*expansions)->content;
	while (str[i])
	{
		if (i >= exp->start + exp->len)
		{
			*isquoted = true;
			*expansions = (*expansions)->next;
			if (*expansions)
				exp = (t_expansions *)(*expansions)->content;
			else
				return (i - start + ft_strlen(&str[i]));
		}
		if (i == exp->start && !exp->is_quoted)
			*isquoted = false;
		if (str[i] == ' ' && !(*isquoted))
			break ;
		i++;
	}
	return (i - start);
}

int	count_var_space(char *str, t_list **expansions, bool *isquoted, int start)
{
	int				i;
	t_expansions	*exp;

	i = start;
	exp = (t_expansions *)(*expansions)->content;
	while (str[i])
	{
		if ((!(*isquoted) && str[i] != ' ') || *isquoted)
			break ;
		if (i == exp->start && !exp->is_quoted)
			*isquoted = false;
		if (!(*isquoted) && i >= exp->start + exp->len)
		{
			*isquoted = true;
			*expansions = (*expansions)->next;
			if (*expansions)
				exp = (t_expansions *)(*expansions)->content;
		}
		i++;
	}
	return (i - start);
}

void	arg_splitter(t_tkn *tk, t_list **args)
{
	int		size;
	int		i;
	char	*str;
	t_list	*exp;
	bool	isquoted;

	i = 0;
	exp = tk->expansions;
	if (!exp)
	{
		str = ft_strdup((char *)tk->data);
		lst_auto_add_back(args, (void *)str);
		return ;
	}
	if (count_split_var(tk->expansions, (char *)tk->data) == 0)
		return ;
	isquoted = true;
	while (((char *)tk->data)[i])
	{
		i += count_var_space(((char *)tk->data), &exp, &isquoted, i);
		size = count_arg_size(((char *)tk->data), &exp, &isquoted, i);
		str = ft_strndup(&((char *)tk->data)[i], size);
		lst_auto_add_back(args, (void *)str);
		i += size;
	}
}

void	*lst_to_array(t_list *args)
{
	char	**array;
	int		i;
	int		size;

	size = ft_lstsize(args);
	array = safe_calloc(sizeof(char *), size + 1);
	i = 0;
	while (i < size)
	{
		array[i] = (char *)args->content;
		args = args->next;
		i++;
	}
	return ((void *)array);
}

void	get_split_args(t_list *tokens, t_cmd_parse *cmd_p)
{
	t_list	*args;
	bool	is_red_data;
	t_tkn	*tk;

	is_red_data = false;
	args = NULL;
	while (!is_cmd_block_end(tokens))
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == META_C)
			is_red_data = true;
		else if (is_red_data)
			is_red_data = false;
		else
			arg_splitter(tk, &args);
		tokens = tokens->next;
	}
	cmd_p->args = (char **)lst_to_array(args);
	ft_lstclear_nodes(&args);
}

void	fill_cmd_struct(t_list *tokens, t_cmd_parse *cmd_p)
{
	extract_redirections(tokens, cmd_p);
	get_split_args(tokens, cmd_p);
}

t_list	*get_to_next_cmd(t_list *tokens)
{
	t_tkn	*tk;

	while (tokens)
	{
		tk = (t_tkn *)tokens->content;
		if (tk->data_type == META_C && tk->data == PIPE)
			return (tokens->next);
		tokens = tokens->next;
	}
	return (tokens);
}

void	token_to_cmd(t_list *tokens, t_cmd_parse ***cmd_p)
{
	int	i;

	create_cmd_array(tokens, cmd_p);
	i = 0;
	while ((*cmd_p)[i])
	{
		fill_cmd_struct(tokens, (*cmd_p)[i]);
		tokens = get_to_next_cmd(tokens);
		i++;
	}
}

int	parse_input(char *input, t_cmd_parse ***input_parse, t_list *env)
{
	t_list	*tokens;

	*input_parse = NULL;
	if (is_string_over(input) != 0)
	{
		write(2, "Incomplete Input\n", 18);
		return (-1);
	}
	tokens = NULL;
	tokenise(input, &tokens);
	if (syntax_errors(tokens) != 0)
	{
		ft_lstclear(&tokens, &free_token);
		return (-1);
	}
	load_vars_per_token(tokens, env);
	expand_vars(tokens);
	token_to_cmd(tokens, input_parse);
	ft_lstclear(&tokens, &free_token);
	return (0);
}
