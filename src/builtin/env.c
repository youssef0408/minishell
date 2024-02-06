/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/05 14:20:54 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_in_env(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], key, ft_strlen(key)))
			return (i);
		i++;
	}
	return (-1);
}

void	open_and_handle_new_terminal(t_command cmd)
{
	int		idx;
	char	*old;

	idx = find_in_env("SHLVL", cmd.env);
	old = ft_substr(cmd.env[idx], 6, ft_strlen(cmd.env[idx]));
	cmd.env[idx] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(old) + 1));
	execve("minishell", NULL, cmd.env);
}

void	exec_env(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->exit_status = 0;
	if(ft_strcmp(cmd->option, ""))
	{
		print_in_color(RED, "🚨env: too many arguments\n");
		cmd->exit_status = 1;
		return;
	}
	while (cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
}

void	update_env(t_command *cmd, char *new_var)
{
	size_t	i;

	i = 0;
	while (cmd->env[i] != NULL)
		i++;
	cmd->env[i] = new_var;
	i++;
	cmd->env[i] = NULL;
}
