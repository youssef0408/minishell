/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/16 16:49:35 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	exit_value(t_command *cmd)
{
	int	res;

	if (ft_strcmp(cmd->option2, ""))
	{
		printf("exit: too many arguments\n");
		res = 1;
	}
	else if (cmd->option)
	{
		if (is_numeral(cmd->option))
		{
			res = ft_atoi(cmd->option);
			res = 0;
			if (res < 0)
				res = 256;
			res = res + res % 256;
		}
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->option);
			res = 255;
		}
	}
	return (res);
}

void	exec_exit(t_command *cmd)
{
	int	result;
	int	i;

	cmd->exit_status = exit_value(cmd);
	handle_exit_status(*cmd);
	exit(cmd->exit_status);
}

void	handle_exit_status(t_command cmd)
{
	int		idx;
	char	*old;
	char	*new_var;

	idx = find_in_env("?", cmd.env);
	if (idx != -1)
	{
		old = ft_substr(cmd.env[idx], 2, ft_strlen(cmd.env[idx]));
		cmd.env[idx] = ft_strjoin("?=", ft_itoa(cmd.exit_status));
		free(old);
	}
	else
	{
		new_var = ft_strjoin("?=", ft_itoa(cmd.exit_status));
		update_env(&cmd, new_var);
	}
}
