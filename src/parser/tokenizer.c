/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:34:09 by bplante           #+#    #+#             */
/*   Updated: 2024/03/11 17:56:34 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_spaces(const char *str)
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

int	find_meta_type(char *str, t_tkn *token)
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
	t_list	*new;
	int		i;
	t_tkn	*token;

	token = safe_calloc(1, sizeof(t_tkn));
	new = ft_lstnew((void *)token);
	if (!new)
		exit_prg_at_error("malloc failure");
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
		lit_track(str[i], &lt);
		i++;
	}
	return (i);
}

int	store_data(char *str, t_list **tokens)
{
	t_tkn	*token;
	t_list	*new;
	int		len;

	token = safe_calloc(1, sizeof(t_tkn));
	new = ft_lstnew((void *)token);
	if (!new)
		exit_prg_at_error("Malloc failure");
	token->data_type = DATA;
	len = count_data_len(str);
	token->data = (uint64_t)ft_strndup(str, len);
	if (!token->data)
		exit_prg_at_error("malloc failure");
	ft_lstadd_back(tokens, new);
	return (len);
}

void	tokenise(char *input, t_list **tokens)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			i += store_meta(&input[i], tokens);
		else if (input[i] != ' ')
			i += store_data(&input[i], tokens);
		i += count_spaces(&input[i]);
	}
}
