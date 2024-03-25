/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:19:11 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/19 16:31:03 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_valid_path(t_command *info, char *cmd_name)
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

int	get_cmd_path(t_command *info, char **args)
{
	char	*temp;

	if (ft_strchr(args[0], '/'))
		return (0);
	temp = get_valid_path(info, args[0]);
	if (!temp)
		return (1);
	free(args[0]);
	args[0] = temp;
	return (0);
}
