/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:27 by bplante           #+#    #+#             */
/*   Updated: 2024/03/22 22:54:37 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_t_command(t_command *info)
{
	if (info->cmds)
		free_array((void **)info->cmds, &free_cmd_parse);
	if (info->fds)
		free(info->fds);
	if (info->pids)
		free(info->pids);
	ft_lstclear(&info->env, &free_key_value);
}

void	free_redirections(void *redirection)
{
	t_redirection	*red;

	if (!redirection)
		return ;
	red = (t_redirection *)redirection;
	if (red->str)
		free(red->str);
	free(red);
}

void	free_cmd_parse(void *info)
{
	t_cmd_parse	*cmd_p;

	cmd_p = (t_cmd_parse *)info;
	if (!cmd_p)
		return ;
	if (cmd_p->args)
		free_array((void **)cmd_p->args, &free);
	if (cmd_p->redirections)
		free_array((void **)cmd_p->redirections, &free_redirections);
	free(cmd_p);
}

void	free_token(void *tk)
{
	t_tkn	*token;

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
