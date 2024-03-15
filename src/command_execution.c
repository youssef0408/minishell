/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/14 23:28:26 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_cmd_path(t_command *info, char *cmd_name)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	paths = ft_split(get_value_with_key(info->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd_name);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_array((void **)paths, &free);
			return (path);
		}
		free(path);
		i++;
	}
	free_array((void **)paths, &free);
	return (NULL);
}

void	exec_cmd(t_command *info, t_cmd_parse **cmd)
{
	int		i;
	char	*old;
	char	**tmp;
	char	*cmd_path;
	pid_t	pid;

	if (get_cmd_count(cmd) == 1 && !exec_builtin(info, cmd[0]))
	{
	}
	else
	{
		// TODO: modifier la fonction exec_cmd au complet
		i = 0;
		pid = fork();
		if (pid == -1)
			printf(" fork failed\n");
		if (pid == 0)
		{
			// sleep(10);
			if (exec_builtin(info, cmd[0]))
			{
				tmp = cmd[0]->args;
				cmd_path = get_cmd_path(info, tmp[0]);
				if (cmd_path)
				{
					tmp[0] = cmd_path;
					execve(cmd_path, tmp, env_list_to_envp(info->env));
				}
				free(cmd_path);
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, tmp[0]);
				printf("\n");
			}
			exit(1);
		}
		waitpid(pid, NULL, 0);
	}
	// return (0);
}
