/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/11 15:40:50 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_echo(t_command *cmd)
{
	char	*tmp;
	int i = 1;
	bool has_nl = true;
	if (!ft_strcmp(cmd->parsed[0]->cmds[i], "-n"))
	{
		i++;
		has_nl = false;
	}
	while(cmd->parsed[0]->cmds[i])
	{
		printf("%s", cmd->parsed[0]->cmds[i]);
		i++;
		if(cmd->parsed[0]->cmds[i])
			printf(" ");
	}
	if(has_nl)
		printf("\n");
	}


// void	exec_echo(t_command cmd)
// {
// 	char	*tmp;

// 	if (!ft_strcmp(cmd.option, "-n"))
// 		printf("%s", parse_env2(cmd, cmd.option2));
// 	else
// 	{
// 		tmp = ft_strjoin(parse_env2(cmd, cmd.option), parse_env2(cmd, cmd.option2));
// 		printf("%s\n", tmp);
// 		free(tmp);
// 	}

// }
