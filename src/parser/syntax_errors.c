/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:32:28 by bplante           #+#    #+#             */
/*   Updated: 2024/03/11 15:33:23 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	write_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

int	syntax_error_message(t_tkn *tk)
{
	write_error("minishell: unexpected syntax error near token ");
	if (!tk)
		write_error("'newline'");
	else if (tk->data == PIPE)
		write_error("'|'");
	else if (tk->data == R_IN_FILE)
		write_error("'<'");
	else if (tk->data == R_OUT_TRUNC)
		write_error("'>'");
	else if (tk->data == R_OUT_APPEND)
		write_error("'>>'");
	else if (tk->data == R_HERE_DOC)
		write_error("'<<'");
	write_error("\n");
	return (-1);
}

int	syntax_errors(t_list *tokens)
{
	bool	need_data;
	bool	need_cmd;
	t_tkn	*tk;

	need_data = false;
	need_cmd = false;
	while (tokens)
	{
		tk = (t_tkn *)tokens->content;
		if (need_data && tk->data_type != DATA)
			return (syntax_error_message(tk));
		else if (need_cmd && (tk->data_type == META_C && tk->data == PIPE))
			return (syntax_error_message(tk));
		if (tk->data_type == META_C)
		{
			if (tk->data == PIPE)
				need_cmd = true;
			else
				need_data = true;
		}
		else
			need_data = false;
		if ((tk->data_type == META_C && tk->data != PIPE)
			|| tk->data_type == DATA)
			need_cmd = false;
		tokens = tokens->next;
	}
	if (need_data || need_cmd)
		return (syntax_error_message(NULL));
	return (0);
}
