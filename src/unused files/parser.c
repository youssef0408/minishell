/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:47:40 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/10 11:39:30 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile_preparation(t_list *tmp, t_list **head, char **str)
{
	tmp = tmp->next;
	if (tmp && ((t_token *)(tmp)->content)->type == ALPHA_T)
	{
		*str = ft_strdup(((t_token *)(tmp)->content)->value);
		*head = tmp;
		if (tmp)
			*head = tmp->next;
	}
}

void	outfile_preparation(t_list *tmp, t_list **head, char **str, t_cmd *cmd)
{
	tmp = tmp->next;
	if (tmp && ((t_token *)(tmp)->content)->type == ALPHA_T)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(((t_token *)(tmp)->content)->value);
		*head = tmp;
		if (tmp)
			*head = tmp->next;
	}
}

t_cmd	*command_redirection(t_list **head, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = *head;
	if (tmp && ((t_token *)(tmp)->content)->type == REDIR_IN_T)
		infile_preparation(tmp, head, &cmd->infile);
	else if (tmp && ((t_token *)(tmp)->content)->type == REDIR_OUT_T)
	{
		cmd->amend = false;
		outfile_preparation(tmp, head, &cmd->outfile, cmd);
	}
	else if (tmp && ((t_token *)(tmp)->content)->type == REDIR_AP_T)
	{
		cmd->amend = true;
		outfile_preparation(tmp, head, &cmd->outfile, cmd);
	}
	return (cmd);
}

t_cmd	*command_table(t_list **head, t_cmd *cmd)
{
	int		array_size;
	int		i;
	t_list	*tmp;

	tmp = *head;
	array_size = 0;
	i = 0;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		array_size++;
		tmp = tmp->next;
	}
	cmd->cmd_table = (char **)safe_calloc(array_size + 1, sizeof(char *));
	tmp = *head;
	while (tmp && ((t_token *)tmp->content)->type == ALPHA_T)
	{
		cmd->cmd_table[i] = ft_strdup(((t_token *)tmp->content)->value);
		i++;
		tmp = tmp->next;
	}
	cmd->cmd_table[i] = NULL;
	*head = tmp;
	return (cmd);
}

t_list	*parser(t_list *cmd_list, const t_list *token_list)
{
	t_cmd	*cmd;
	t_list	*tmp_token;

	tmp_token = (t_list *)token_list;
	while (tmp_token)
	{
		cmd = safe_calloc(1, sizeof(t_cmd));
		while (tmp_token)
		{
			if (((t_token *)tmp_token->content)->type == PIPE_T)
			{
				tmp_token = tmp_token->next;
				break ;
			}
			else if (((t_token *)tmp_token->content)->type == ALPHA_T)
				command_table(&tmp_token, cmd);
			else if (((t_token *)tmp_token->content)->type != HERE_DOC_T)
				command_redirection(&tmp_token, cmd);
		}
		if (cmd)
			ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	}
	return (cmd_list);
}
