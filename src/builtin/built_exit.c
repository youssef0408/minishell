/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/14 23:20:44 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_numeral(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exit_value(t_cmd_parse *cmd)
{
	int	res;

	if (!cmd->args[2])
	{
		printf("exit: too many arguments\n");
		res = 1;
	}
	else if (cmd->args[1])
	{
		if (is_numeral(cmd->args[1]))
		{
			res = ft_atoi(cmd->args[1]);
			res = 0;
			if (res < 0)
				res = 256;
			res = res + res % 256;
		}
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->args[1]);
			res = 255;
		}
	}
	else
	{
		res = 0;
		printf("exit\n");
	}
	return (res);
}

void	exec_exit(t_command *info, t_cmd_parse *cmd)
{
	info->exit_status = exit_value(cmd);
	//free_and_exit(info->exit_status); //TODO: implement this func
}

void	handle_exit_status(t_command *info)
{
	add_to_env(&info->env, "?", ft_itoa(info->exit_status));
}
