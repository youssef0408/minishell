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
#include "parser.h"

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

int	create_cmd_array(t_list *tokens, t_cmd_parse ***cmd_p)
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

bool	is_cmd_block_end(t_list *parsedin)
{
	if (!parsedin)
		return (true);
	if (((t_tkn *)parsedin->content)->data_type == META_C
		&& ((t_tkn *)parsedin->content)->data == PIPE)
		return (true);
	return (false);
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
	create_cmd_array(tokens, cmd_p);
	i = 0;
	while ((*cmd_p)[i])
	{
		fill_cmd_struct(tokens, **cmd_p, envp);
		i++;
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
