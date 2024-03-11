/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:08 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	exec_cmd(t_command cmd, char **envp)
{
	int		i;
	char	*old;
	char	**tmp;
	char	*cmd_path;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == -1)
		printf(" fork failed\n");
	if (pid == 0)
	{
		// sleep(10);
		if (exec_builtin(cmd, cmd.env))
		{
			tmp = cmd.parsed[0]->cmds;
			cmd_path = get_cmd_path(tmp[0], envp);
			if (!cmd_path || execve(cmd_path, tmp, cmd.env) == -1)
			{
				clean_table(tmp);
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, tmp[0]);
				printf("\n");
			}
		}
	}
	else
	{
		// if (exec_builtin(cmd, cmd.env))
		// {
		// 	tmp = cmd.parsed[0]->cmds;
		// 	printf("2=====>%s\n", tmp[0]);
		// 	cmd_path = get_cmd_path(tmp[0], envp);
		// 	if (!cmd_path || execve(cmd_path, tmp, cmd.env) == -1)
		// 	{
		// 		clean_table(tmp);
		// 		print_in_color(RED, "🚨command not found:  ");
		// 		print_in_color(RED, cmd.name);
		// 		printf("\n");
		// 	}
		// }
	}
	waitpid(pid, NULL, 0);
	// return (0);
}
