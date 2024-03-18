/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:57:48 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/18 15:20:22 by yothmani         ###   ########.fr       */
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

void	export_exec(t_command *info, t_cmd_parse *cmd)
{
	char	**tmp;
	int		i;
	char	*value;
	char	*key;

	i = 1;
	info->exit_status = 0;
	if (!cmd->args[1])
		return (print_declare_env(info->env));
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			key = ft_substr(cmd->args[i], 0, ft_strchr(cmd->args[i], '=')
					- cmd->args[i]);
			if (is_valid_var_id(key))
			{
				value = ft_substr(cmd->args[i], ft_strlen(key) + 1,
						(ft_strlen(cmd->args[i]) - ft_strlen(key) - 1));
				add_to_env(&info->env, key, value);
			}
			else
			{
				print_in_color(RED, "not a valid identifier\n");
				info->exit_status = 1;
			}
			free(key);
		}
		else
		{
			if (!is_valid_var_id(cmd->args[i]))
			{
				print_in_color(RED, "not a valid identifier\n");
				info->exit_status = 1;
			}
		}
		i++;
	}
}
