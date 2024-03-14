/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/14 16:56:47 by yothmani         ###   ########.fr       */
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

void	exec_cmd(t_command *info, t_cmd_parse **cmd)
{
	int		i;
	char	*old;
	char	**tmp;
	char	*cmd_path;
	pid_t	pid;


	if(get_cmd_count(cmd) == 1 && exec_builtin(info, cmd[0])) //TODO: modifier la fonction exec_cmd au complet
	i = 0;
	pid = fork();
	if (pid == -1)
		printf(" fork failed\n");
	if (pid == 0)
	{
		// sleep(10);
		if (exec_builtin(cmd, cmd.env))
		{
			tmp = cmd.parsed[0]->args;
			cmd_path = get_cmd_path(tmp[0], envp);
			if (!cmd_path || execve(cmd_path, tmp, cmd.env) == -1)
			{
				clean_table(tmp);
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, tmp[0]);
				printf("\n");
			}
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
	// return (0);
}
