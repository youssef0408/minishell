/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:12:45 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/19 13:08:07 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    syntax_error(t_command *cmd)
{
    cmd->exit_status != 0;
    printf("syntax error near unexpected token\n");
}

void	void_del(void *content)
{
	free(content);
}

int     exit_tokenizer(t_command *cmd, t_list **tokens)
{
    syntax_error(cmd);
    ft_lstclear(tokens, &void_del);
    return(1);
}

int clean_tokens(t_list **tokens, t_command *cmd)
{
    t_list *ptr;

    ptr = *tokens;
    while(ptr)
    {
        if(ft_strcmp(ptr->content, " "))
        {
            ft_lstdeletenode(tokens, ptr, &void_del);
            ptr = *tokens;
        }
        else if (!ft_strcmp(ptr->content, "|"))
        {
            if(!ptr->next || !ft_strcmp(ptr->next->content, "|"))
                return(exit_tokenizer(cmd, tokens));
        }
        else if(!ft_strcmp(ptr->content, "<") || !ft_strcmp(ptr->content, ">"))
        {
            if(handle_redirection(tokens, cmd, &ptr))
                return(1);
        }
        else
            ptr = ptr->next;
    }   
    return(0);
}

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
	return (0);
}
