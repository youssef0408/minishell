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

void	expand_vars(t_list *tokens)
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
