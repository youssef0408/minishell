/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:38:06 by bplante           #+#    #+#             */
/*   Updated: 2024/03/18 16:54:14 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// create expantion struct and and add if its quote or not, add start if isnt
int	store_value_from_env(char *str, t_list *env, t_tkn *tk, int start)
{
	int				i;
	char			*key;
	const char		*value;
	t_list			*new;
	t_expansions	*expansion;

	i = 0;
	if (str[i] == '?')
		i = 1;
	else
	{
		while (ft_isalnum(str[i]))
			i++;
	}
	if (i == 0)
		return (0);
	key = ft_strndup(str, i);
	value = get_value_with_key(env, key);
	if (!value)
		value = ft_strdup("");
	expansion = safe_calloc(sizeof(t_expansions), 1);
	expansion->value = value;
	expansion->start = start;
	expansion->len = ft_strlen(value);
	expansion->key_len = ft_strlen(key);
	new = ft_lstnew((void *)expansion);
	if (!new)
		exit_prg_at_error("malloc failure");
	ft_lstadd_back(&tk->expansions, new);
	free(key);
	return (i);
}

// create expantion struct and and add if its quote or not, add start if isnt
// int store_value_from_env(char *strstart
int	check_and_fetch(t_tkn *token, t_list *env)
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
			i += store_value_from_env(&data[i + 1], env, token, i);
		}
		lit_track(data[i], &lt);
		i++;
	}
	return (0);
}

int	load_vars_per_token(t_list *tokens, t_list *env)
{
	while (tokens)
	{
		if (((t_tkn *)tokens->content)->data_type == DATA)
		{
			check_and_fetch((t_tkn *)tokens->content, env);
		}
		tokens = tokens->next;
	}
	return (0);
}
