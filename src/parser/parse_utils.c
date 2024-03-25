/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:26:53 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/23 01:27:42 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
