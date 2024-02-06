/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:11:42 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/06 11:40:47 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax_error(t_list **tokens, t_command *cmd)
{
	t_list	*ptr;

	ptr = *tokens;
	while (ptr)
	{
		if (!ft_strcmp(ptr->content, "<<"))
		{
			if (!ptr->next || !ft_strcmp(ptr->next->content, "<")
				|| !ft_strcmp(ptr->next->content, ">"))
				return (exit_tokenizer(cmd, tokens));
		}
		if (!ft_strcmp(ptr->content, ">>"))
		{
			if (!ptr->next || !ft_strcmp(ptr->next->content, "<")
				|| ft_strcmp(ptr->next->content, ">"))
				return (exit_tokenizer(cmd, tokens));
		}
		ptr = ptr->next;
	}
	return (0)
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

char **command_table_creation(t_list **tokens, t_command *cmd)
{
    int i;
    int count;
    char **table;
    t_list *tmp;
    
    count = ft_lstsize(*tokens);
    table = malloc((count + 1) * sizeof(char *));
    if(!table)
        clean_table(table);//TODO: free and exit
    tmp = *tokens;
    i = 0;
    while(tmp)
    {
        table[i] = ft_strdup(tmp->content);
        if(!table[i])
            clean_table(table);//TODO: free and exit
        i++;
        tmp = tmp->next;
    }
    table[i] = NULL;
    ft_lstclear(tokens, &void_del);
    return(replace_redirection_operators(table));
}
bool quotes_are_not_closed(char *str, t_command *cmd)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] != '\0' && str[i] != quote)
				i++;
			if (str[i] == '\0')
			{
				cmd->exit_status = 1;
				printf("Quotes are not closed!\n");
				return (true);
			}
		}
		i++;
	}
	return (false);
}

char **ft_tokenizer(char *str, t_command *cmd)
{
    t_list *tokens;

    if(quotes_are_not_closed(str, cmd))
        return(NULL);
    tokens = NULL;
    tokenize(str, cmd, &tokens); //TODO:implement this function
    if(clean_tokens(&tokens, cmd)) //TODO:implement this function
        return(NULL);
    if(check_syntax_error(&tokens, cmd))
        return(NULL);
    return(command_table_creation(&tokens, cmd));
}

int handle_output_redirection(t_list **tokens, t_command *cmd, t_list **ptr)
{
	if(!(*ptr)->next || !ft_strcmp((*ptr)->next->content, "<"))
		return(exit_tokenizer(cmd, tokens));
	if(!ft_strcmp((*ptr)->next->content, ">"))
	{
		if(ft_strjoin(((char **)&(*ptr)->content), ">"))
			return(1);
		ft_lstdeletenode(tokens, (*ptr)->next, &void_del); 
	}
	*ptr = (*ptr)->next;
	return(0);
}
int handle_input_redirection(t_list **tokens, t_command *cmd, t_list **ptr)
{
	if(!(*ptr)->next || !ft_strcmp((*ptr)->next->content, ">"))
		return(exit_tokenizer(cmd, tokens));
	if(!ft_strcmp((*ptr)->next->content, "<"))
	{
		if(ft_strjoin(((char **)&(*ptr)->content), "<"))
			return(1);
		ft_lstdeletenode(tokens, (*ptr)->next, &void_del); 
	}
	*ptr = (*ptr)->next;
	return(0);
}