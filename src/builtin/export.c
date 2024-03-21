/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:57:48 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/20 13:29:07 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	print_declare_env(t_list *env)
{
	char	*kv;

	while (env)
	{
		kv = join_key_value(env);
		printf("declare -x %s\n", kv);
		env = env->next;
		free(kv);
	}
}

bool	is_valid_var_id(char *id)
{
	int	i;

	if (!id)
		return (false);
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (false);
	i = 1;
	while (id[i])
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	handle_export_error(t_command *info, t_cmd_parse *cmd, int i)
{
	ft_printf_fd("export: '%s': not a valid identifier\n", 2, cmd->args[i]);
	info->exit_status = 1;
}

void	export_exec(t_command *info, t_cmd_parse *cmd)
{
	int	i;

	info->exit_status = 0;
	if (!cmd->args[1])
	{
		print_declare_env(info->env);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
			process_export_with_assignment(info, cmd, i);
		else
			process_export_without_assignment(info, cmd, i);
		i++;
	}
}
