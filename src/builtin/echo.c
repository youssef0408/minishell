/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/14 13:41:15 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_echo(t_cmd_parse *cmd)
{
	char	*tmp;
	int i = 1;
	bool has_nl = true;
	if (!ft_strcmp(cmd->args[1], "-n"))
	{
		i++;
		has_nl = false;
	}
	while(cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if(cmd->args[i])
			printf(" ");
	}
	if(has_nl)
		printf("\n");
	}
