/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:18:31 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:54:37 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
int	step_through_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}