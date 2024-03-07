/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:40:06 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 13:55:58 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// TODO: check all of the pipe handlers

char	*get_path(char *str, t_command *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	path = cmd->env[find_in_env("PATH=", cmd->env)];
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, str);
		free(part_path);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			free(path);
			path = NULL;
		}
		i++;
	}
	clean_table(paths);
	return (path);
}

void	child_exec(t_command *cmd)
{
	char	**args;
	char	*path;

	args = cmd->cmd_table;
	path = args[0];
	if (strchr(path, '/') == NULL)
	{
		get_path(path, cmd);
		if (cmd->cmd_table == NULL || cmd->cmd_table[0] == NULL)
		{
			printf("%s: %s\n", "command not found:", args[0]);
			// free_struct(cmd); // TODO: implementer la fonction
			exit(127);
		}
	}
	if (execve(path, args, cmd->env) == -1)
	{
		printf("%s: %s\n", "command not found:", args[0]);
		// free_struct(cmd); // TODO: implementer la fonction
		_exit(127);
	}
}

int	child_pipe(t_list *cmdlist, t_command *cmd)
{
	if ((dup2(((t_command *)cmdlist->content)->fd_input, STDIN_FILENO)) == -1)
	{
		printf("%s\n", strerror(errno));
		// free_struct(cmd); // TODO: implementer la fonction
		exit(1);
	}
	close(((t_command *)cmdlist->content)->fd_input);
	if ((dup2(((t_command *)cmdlist->content)->fd_output, STDOUT_FILENO)) == -1)
	{
		if (errno != EBADF)
		{
			printf("%s\n", strerror(errno));
			// free_struct(cmd); // TODO: implementer la fonction
			exit(1);
		}
	}
	close(((t_command *)cmdlist->content)->fd_output);
	return (0);
}
