/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:34:09 by bplante           #+#    #+#             */
/*   Updated: 2024/03/07 13:13:47 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

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

	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (-1);
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (-1);
	}
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

	token = ft_calloc(1, sizeof(t_tkn));
	if (!token)
		return (-1);
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (-1);
	}
	token->data_type = DATA;
	len = count_data_len(str);
	token->data = (uint64_t)ft_strndup(str, len);
	if (!token->data)
	{
		free(token);
		free(new);
		return (-1);
	}
	ft_lstadd_back(tokens, new);
	return (len);
}

int	tokenise(char *input, t_list **tokens)
{
	int	i;
	int	temp;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			temp = store_meta(&input[i], tokens);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		else if (input[i] != ' ')
		{
			temp = store_data(&input[i], tokens);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		i += count_spaces(&input[i]);
	}
	return (0);
}
