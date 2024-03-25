/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:41:40 by bplante           #+#    #+#             */
/*   Updated: 2024/03/25 00:49:00 by bplante          ###   ########.fr       */
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

void	handle_space_in_var(t_sv_info *svi, char *data)
{
	if (svi->i >= svi->exp->start && svi->i < svi->exp->start + svi->exp->len)
		svi->is_in_var = true;
	if (svi->has_char && svi->is_in_var && !svi->exp->is_quoted
		&& data[svi->i] == ' ')
	{
		svi->count++;
		svi->has_char = false;
	}
	else if (!svi->has_char && ((svi->is_in_var && !svi->exp->is_quoted
				&& data[svi->i] != ' ') || svi->exp->is_quoted))
		svi->has_char = true;
}

// TODO: need to modify this func. to conform to norms
int	count_split_var(t_list *expansions, char *data)
{
	t_sv_info	svi;

	if (!expansions)
		return (1);
	init_sv_info(&svi, expansions);
	svi.exp = (t_expansions *)expansions->content;
	while (data[svi.i] && expansions)
	{
		if (svi.is_in_var && !(svi.i >= svi.exp->start && svi.i < svi.exp->start
				+ svi.exp->len))
		{
			if (handle_variable_end(&svi.is_in_var, &expansions, &svi.exp))
				break ;
		}
		handle_space_in_var(&svi, data);
		svi.i++;
	}
	check_if_data_after_exp(&svi, data);
	return (svi.count);
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
