/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:50:09 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/23 01:30:26 by yothmani         ###   ########.fr       */
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
	// TODO:exec_exit:
	// free(info->fds);
	// free(info->pids);
	// TODO: check les deux free entrainent un message derreur suitent à executer exit de plus d'un shlvl
	//  minishell(6948,0x11acd4dc0) malloc: *** error for object 0x7f86ade04080: pointer being freed was not allocated
	// minishell(6948,0x11acd4dc0) malloc: *** set a breakpoint in malloc_error_break to debug
	// [1]    6948 abort      ./minishell
void	exec_exit(t_command *info, t_cmd_parse *cmd)
{
	info->exit_status = exit_value(cmd);
	close_non_std_fds(info->fds);
	ft_lstclear(&info->env, &free_key_value);
	free_array((void **)info->cmds, &free_cmd_parse);
	rl_clear_history();
	exit(info->exit_status);
}

void	handle_exit_status(t_command *info)
{
	add_to_env(&info->env, "?", ft_itoa(info->exit_status));
}
