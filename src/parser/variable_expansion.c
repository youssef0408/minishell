/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:29:23 by bplante           #+#    #+#             */
/*   Updated: 2024/03/06 13:50:00 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_printed(char *str, struct s_litteral_tracker *lt)
{
	int	temp;

	temp = lt->is_lit;
	lit_track(str[0], lt);
	if (temp == 2)
		return (true);
	if (lt->is_lit == 1 && lt->quote == str[0])
		return (false);
	if (lt->is_lit == 0 && (str[0] == '\'' || str[0] == '\"'))
		return (false);
	if (str[0] == '\\' && ((lt->is_lit == 1 && lt->quote == 0)
			|| (lt->is_lit == 2 && str[1] == '\"' || str[1] == '$'
				|| str[1] == '\\')))
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

void	remove_quoted_expansions(t_list **expansions)
{
	t_list			*lst_p;
	t_expansions	*exp;
	t_list			*temp;

	lst_p = *expansions;
	while (lst_p)
	{
		temp = lst_p->next;
		exp = (t_expansions *)lst_p->content;
		if (exp->is_quoted)
			ft_lstdeletenode(expansions, lst_p, &free);
		lst_p = temp;
	}
}

// TODO remove quoted expansions from list
int	expand(t_tkn *tk)
{
	int	count;

	tk->original = (char *)tk->data;
	count = count_new_data_size((char *)tk->data, tk->expansions);
	tk->data = (uint64_t)ft_calloc(sizeof(char), count + 1);
	fill_new_data((char *)tk->data, tk->original, tk->expansions);
	remove_quoted_expansions(&tk->expansions);
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
