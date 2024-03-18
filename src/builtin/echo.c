/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/18 15:17:20 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_echo(t_cmd_parse *info)
{
	char	*tmp;
	int i = 1;
	bool has_nl = true;
	if (info->args[1] && !ft_strcmp(info->args[1], "-n"))
	{
		i++;
		has_nl = false;
	}
	while(info->args[i])
	{
		printf("%s", info->args[i]);
		i++;
		if(info->args[i])
			printf(" ");
	}
	if(has_nl)
		printf("\n");
	}
