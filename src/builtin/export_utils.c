/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:53:40 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/25 00:45:29 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	process_export_with_assignment(t_command *info, t_cmd_parse *cmd,
		int index)
{
	char	*key;
	char	*value;

	key = get_key_from_assignment(cmd->args[index]);
	if (is_valid_var_id(key))
	{
		value = get_value_from_assignment(cmd->args[index], key);
		add_to_env(&info->env, key, value);
	}
	else
		handle_export_error(info, cmd, index);
	free(key);
}

void	process_export_without_assignment(t_command *info, t_cmd_parse *cmd,
		int index)
{
	if (!is_valid_var_id(cmd->args[index]))
		handle_export_error(info, cmd, index);
}

char	*get_key_from_assignment(char *arg)
{
	return (ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
}

char	*get_value_from_assignment(char *arg, char *key)
{
	return (ft_substr(arg, ft_strlen(key) + 1, (ft_strlen(arg) - ft_strlen(key)
				- 1)));
}
