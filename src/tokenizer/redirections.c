/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:15:33 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:56:24 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	join_str_to_tab(char **s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!*s1 || !s2)
	{
		free(*s1);
		return (EXIT_FAILURE);
	}
	if (!*s2)
		return (EXIT_SUCCESS);
	len1 = ft_strlen(*s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
	{
		free(*s1);
		*s1 = NULL;
		return (EXIT_FAILURE);
	}
	ft_strcpy(str, *s1);
	ft_strcpy(str + len1, s2);
	free(*s1);
	*s1 = str;
	return (EXIT_SUCCESS);
}


int	handle_output_redirection(t_list **tokens, t_command *cmd, t_list **ptr)
{
	if (!(*ptr)->next || !ft_strcmp((*ptr)->next->content, "<"))
		return (exit_tokenizer(cmd, tokens));
	if (!ft_strcmp((*ptr)->next->content, ">"))
	{
		if (join_str_to_tab(((char **)&(*ptr)->content), ">"))
			return (1);
		ft_lstdeletenode(tokens, (*ptr)->next, &void_del);
	}
	*ptr = (*ptr)->next;
	return (0);
}

int	handle_input_redirection(t_list **tokens, t_command *cmd, t_list **ptr)
{
	if (!(*ptr)->next || !ft_strcmp((*ptr)->next->content, ">"))
		return (exit_tokenizer(cmd, tokens));
	if (!ft_strcmp((*ptr)->next->content, "<"))
	{
		if (join_str_to_tab(((char **)&(*ptr)->content), "<"))
			return (1);
		ft_lstdeletenode(tokens, (*ptr)->next, &void_del);
	}
	*ptr = (*ptr)->next;
	return (0);
}

int	handle_redirection(t_list **tokens, t_command *cmd, t_list **ptr)
{
	if (ft_strcmp((*ptr)->content, "<"))
	{
		if (handle_input_redirection(tokens, cmd, ptr))
			return (1);
	}
	else
	{
		if (handle_output_redirection(tokens, cmd, ptr))
			return (1);
	}
	return (0);
}

char	**replace_redirection_operators(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (!ft_strcmp(table[i], "<"))
			table[i][0] = '<';
		else if (!ft_strcmp(table[i], ">"))
			table[i][0] = '>';
		else if (!ft_strcmp(table[i], "<<"))
		{
			table[i][0] = '<';
			table[i][1] = '<';
		}
		else if (!ft_strcmp(table[i], ">>"))
		{
			table[i][0] = '>';
			table[i][1] = '>';
		}
		i++;
	}
	return (table);
}
