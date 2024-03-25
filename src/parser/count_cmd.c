/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:53:19 by bplante           #+#    #+#             */
/*   Updated: 2024/03/23 00:24:20 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_cmd_count(t_cmd_parse **cmd_p)
{
	int	i;

	i = 0;
	if (!cmd_p)
		return (0);
	while (cmd_p[i])
		i++;
	return (i);
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
