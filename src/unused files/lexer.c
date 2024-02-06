/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:37:22 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/10 09:24:40 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	meta_token(const char *str, int i, t_token *token)
{
	if (str[i] == '\0')
		return (i);
	else if (str[i] == PIPE)
		token->type = PIPE_T;
	else if (str[i] == REDIR_I)
	{
		if (str[i + 1] == REDIR_I)
		{
			token->type = HERE_DOC_T;
			return (2 + i);
		}
		token->type = REDIR_IN_T;
	}
	else if (str[i] == REDIR_O)
	{
		if (str[i + 1] == REDIR_O)
		{
			token->type = REDIR_AP_T;
			return (2 + i);
		}
		token->type = REDIR_OUT_T;
	}
	return (++i);
}

static int	alpha_token(const char *str, int i, t_token *token)
{
	int		j;
	int		flag;
	char	*copy;

	flag = 0;
	j = i;
	while (str[i] != '\0' && !is_white_space(str[i]) && !ft_strchr("'\"<>|",
			str[i]))
	{
		if (str[i] == '$')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		copy = ft_substr(str, j, i - j);
		token->value = parse_env(copy);
		free(copy);
	}
	else
		token->value = ft_substr(str, j, i - j);
	token->type = ALPHA_T;
	if (str[i] >= 33 && !ft_strchr("<>|", str[i]))
		token->append = true;
	return (i);
}

static int	get_token(const char *str, int i, t_token *token)
{
	int	j;

	if (is_white_space(str[i]))
	{
		while (is_white_space(str[i]))
			i++;
	}
	if (str[i] == '\0')
		return (i);
	if (ft_strchr("<>|", str[i]))
		return (meta_token(str, i, token));
	else if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
		return (quotes_parser(str, i + 1, token, str[i]));
	else
		return (alpha_token(str, i, token));
}

char	*token_amend(t_token *token, char *copy)
{
	char	*temp;

	if (token->type == ALPHA_T && token->append == true)
	{
		if (copy)
		{
			temp = ft_strjoin(copy, token->value);
			free(copy);
			free(token->value);
		}
		else
		{
			temp = ft_strdup(token->value);
			free(token->value);
		}
		return (temp);
	}
	else if (token->type == ALPHA_T && token->append == false && copy)
	{
		temp = token->value;
		token->value = ft_strjoin(copy, token->value);
		free(temp);
		free(copy);
	}
	return (NULL);
}

t_list	*tokenizer(const char *str, t_list *token_list)
{
	int		i;
	t_token	*token;
	char	*copy;

	i = 0;
	copy = NULL;
	while (i < ft_strlen(str))
	{
		token = safe_calloc(1, sizeof(t_token));
		i = get_token(str, i, token);
		temp_error(i, token_list, token);
		copy = token_amend(token, copy);
		if (copy && token->type == ALPHA_T && token->append == true)
			token->value = copy;
		if (token && token->type && token->append == false)
			ft_lstadd_back(&token_list, ft_lstnew((t_token *)token));
		else
			free(token);
	}
	free(copy);
	return (token_list);
}
