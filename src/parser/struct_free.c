/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:27 by bplante           #+#    #+#             */
/*   Updated: 2024/03/11 17:23:11 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_cmd_parse(void *cmd)
{
	t_cmd_parse	*cmd_p;

	if (!cmd_p)
		return ;
	cmd_p = (t_cmd_parse *)cmd;
	if (cmd_p->cmds)
		free_array((void **)cmd_p->cmds, &free);
	if (cmd_p->redirections)
		free_array((void **)cmd_p->redirections, &free);
	free(cmd_p);
}

void	free_token(void *tk)
{
	t_tkn *token;

	if (!tk)
		return ;
	token = (t_tkn *)tk;
	if (token->data_type == DATA)
	{
		if (token->data)
			free((char *)token->data);
		if (token->original)
			free(token->original);
		ft_lstclear(&token->expansions, &free);
	}
	free(token);
}