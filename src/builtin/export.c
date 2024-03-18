/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:57:48 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/18 17:57:59 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	print_declare_env(t_list *env)
{
	int		i;
	char	*kv;

	i = 0;
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
	print_in_color(RED, "export: '");
	print_in_color(RED, cmd->args[i]);
	print_in_color(RED, "' :not a valid identifier\n");
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
