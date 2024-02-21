/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:40:38 by joe_jam           #+#    #+#             */
/*   Updated: 2024/02/21 13:56:42 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_echo(t_command cmd)
{
	char	*tmp;

	if (!ft_strcmp(cmd.option, "-n"))
		printf("%s", parse_env2(cmd, cmd.option2));
	else
	{
		tmp = ft_strjoin(parse_env2(cmd, cmd.option), parse_env2(cmd, cmd.option2));
		printf("%s\n", tmp);
		free(tmp);
	}

}
