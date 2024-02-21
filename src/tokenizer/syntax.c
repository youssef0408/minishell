/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:11:42 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:56:18 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

char **ft_tokenizer(char *str, t_command *cmd)
{
    t_list *tokens;

    if(quotes_are_not_closed(str, cmd))
        return(NULL);
    tokens = NULL;
    tokenize(str, cmd, &tokens);
    if(clean_tokens(&tokens, cmd))
        return(NULL);
    if(check_syntax_error(&tokens, cmd))
        return(NULL);
    return(command_table_creation(&tokens, cmd));
}

int	create_token(t_list **tokenlist,
				int *i, int *pos, char *str)
{
	char	*tmp;
	t_list	*node;

	tmp = ft_substr(str, *pos, *i - *pos);
	if (tmp == NULL)
		return (1);
	node = ft_lstnew(tmp);
	if (node == NULL)
		return (1);
	ft_lstadd_back(tokenlist, node);
	return (0);
}

int	split_tokens(t_list **tokenlist, int *i, int *pos, char *str)
{
	if (*i > *pos)
	{
		if (create_token(tokenlist, i, pos, str))
			return (1);
		*pos = *i;
	}
	*i = *i + 1;
	if (create_token(tokenlist, i, pos, str))
		return (1);
	*pos = *i;
	return (0);
}

void	tokenize(char *str, t_command *cmd, t_list **tokens)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += step_through_quote(str + i, str[i]);
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>')
		{
			if (split_tokens(tokens, &i, &pos, str))
				printf("need to free and exit here\n");
				// free_and_exit();//TODO:create free_and exit function
		}
		else
			i++;
	}
	if (i > pos)
	{
		if (create_token(tokens, &i, &pos, str))
			printf("need to free and exit here\n");
			// free_and_exit(); //TODO:create free_and exit function
	}
}