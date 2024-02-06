/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:40:06 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/06 11:24:21 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *str, t_command *cmd)
{
	char	**paths_tab;
	char	*path;
	char	*tmp;
	int		i;

	path = cmd->env[find_in_env("PATH=", cmd->env)];
	if (!path)
		return (NULL);
	paths_tab = ft_split(path + 5, ':');
	i = 0;
	path = NULL;
	while (paths_tab[i])
	{
		paths_tab[i] = ft_strjoin(paths[i], "/");
	}
}

char	*get_path(char *str, t_command *cmd)
{
	char **paths;
	char *path;
	int i;
	char *part_path;

	i = 0;
	path = cmd->env[find_in_env("PATH=", cmd->env)];
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
    path = NULL;
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
        else
    		free(path);
		i++;
	}
	clean_table(paths);
	return (NULL);
}
