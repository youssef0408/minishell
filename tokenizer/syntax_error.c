/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:12:45 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/05 15:31:59 by yothmani         ###   ########.fr       */
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