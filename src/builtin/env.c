/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/20 13:28:20 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_shlvl(t_list **env)
{
	const char	*shlvl;

	shlvl = get_value_with_key(*env, "SHLVL");
	if (!shlvl)
		add_to_env(env, "SHLVL", ft_itoa(1));
	else
		add_to_env(env, "SHLVL", ft_itoa(ft_atoi(shlvl) + 1));
	add_to_env(env, "?", ft_itoa(0));
	return ;
}

void	exec_env(t_command *info, t_cmd_parse *cmd)
{
	t_list	*tmp;
	char	*kv;

	info->exit_status = 0;
	if (cmd->args[1])
	{
		ft_printf_fd("env: too many arguments\n", 2);
		info->exit_status = 1;
		return ;
	}
	tmp = info->env;
	while (tmp)
	{
		kv = join_key_value(tmp);
		printf("%s\n", kv);
		free(kv);
		tmp = tmp->next;
	}
}
