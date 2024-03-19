/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:41:40 by bplante           #+#    #+#             */
/*   Updated: 2024/03/19 17:01:38 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

	if (!expansions)
		return (1);
	i = 0;
	count = 0;
	has_char = false;
	is_in_var = false;
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
			has_char = true;
		i++;
	}
	if (has_char)
		count++;
	else if (!has_char && ((data[i] && data[i + 1]) || exp->is_quoted))
		count++;
	return (count);
}

int	store_redirection_info(t_tkn *tk, t_cmd_parse *cmd_p, int type, int i)
{
	int	count;

	count = 1;
	if (tk->data == R_HERE_DOC)
		cmd_p->redirections[i]->str = ft_strdup(tk->original);
	else
		count = count_split_var(tk->expansions, (char *)tk->data);
	cmd_p->redirections[i]->redirect_type = type;
	if (count != 1)
	{
		cmd_p->redirections[i]->redirect_type = R_AMBIGUOUS;
		cmd_p->redirections[i]->str = ft_strdup(tk->original);
	}
	else
		cmd_p->redirections[i]->str = ft_strdup((char *)tk->data);
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
		cmd_p->redirections = safe_calloc(sizeof(t_redirection *), count + 1);
		while (i < count)
		{
			cmd_p->redirections[i] = safe_calloc(sizeof(t_redirection), 1);
			i++;
		}
	}
	return (count);
}

int	extract_redirections(t_list *tokens, t_cmd_parse *cmd_p)
{
	int	temp;

	temp = alloc_redirection_array(tokens, cmd_p);
	if (temp > 0)
		fill_redirection(tokens, cmd_p);
	else if (temp == -1)
		return (-1);
	return (0);
}
