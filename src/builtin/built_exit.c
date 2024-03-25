/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/25 14:38:48 by bplante          ###   ########.fr       */
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

int	exit_val_if_args_provided(t_cmd_parse *cmd)
{
	int	res;

	if (is_numeral(cmd->args[1]))
	{
		res = ft_atoi(cmd->args[1]);
		res = res % 256;
		if (res < 0)
			res = 256 + res;
		if (cmd->args[2])
		{
			ft_printf_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	else
	{
		ft_printf_fd("exit: %s: numeric argument required\n", 2, cmd->args[1]);
		res = 255;
	}
	return (res);
}

int	exit_value(t_cmd_parse *cmd)
{
	int	res;

	if (cmd->args[1])
		res = exit_val_if_args_provided(cmd);
	else
		res = 0;
	return (res);
}

void	exec_exit(t_command *info, t_cmd_parse *cmd)
{
	info->exit_status = exit_value(cmd);
	close_non_std_fds(info->fds);
	free_t_command(info);
	rl_clear_history();
	printf("exit\n");
	exit(info->exit_status);
}

void	handle_exit_status(t_command *info)
{
	add_to_env(&info->env, "?", ft_itoa(info->exit_status));
}
