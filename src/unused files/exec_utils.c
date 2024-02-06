/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:08:54 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/31 13:16:25 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**envp_path_creation_leon(char **envp)
{
	char	*temp;
	char	**envp_path;
	int		i;

	temp = NULL;
	envp_path = NULL;
	while (envp && ft_strncmp(*envp, "PATH", 4) != 0)
		envp++;
	envp_path = ft_split(*envp + 5, ':');
	i = -1;
	while (envp_path[++i] != NULL)
	{
		temp = ft_strjoin(envp_path[i], "/");
		if (temp)
		{
			free(envp_path[i]);
			envp_path[i] = temp;
		}
	}
	envp_path[i] = NULL;
	return (envp_path);
}

static int	path_verification(char **envp_path, t_cmd *cmd)
{
	int		i;
	char	*str;

	if (cmd == NULL || cmd->cmd_table[0] == NULL)
		return (1);
	i = 0;
	while (envp_path[i] != NULL)
	{
		if (envp_path[i] != NULL)
		{
			str = ft_strjoin(envp_path[i], cmd->cmd_table[0]);
			if (str == NULL)
				return (1);
			if (access(str, F_OK | X_OK) == 0)
			{
				free(cmd->cmd_table[0]);
				cmd->cmd_table[0] = str;
				return (0);
			}
			free(str);
		}
		i++;
	}
	return (1);
}
// Ou Est-ce que command env est mis a jour ?
void	update_cmd_list(t_list *cmd_list, char **envp)
{
	char	**envp_path;
	t_cmd	*cmd;

	envp_path = envp_path_creation_leon(envp);// Changer envp;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (cmd && cmd->cmd_table)
		{
			if (path_verification(envp_path, cmd) == 0)
			{
			}
			else
				printf("Command not found: %s\n", cmd->cmd_table[0]);
		}
		cmd_list = cmd_list->next;
	}
	free_array((void **)envp_path);
}

void	close_pipes(int lst_size, int **pipes)
{
	int	j;

	j = 0;
	while (j < lst_size)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

int	**pipes_creation(int lst_size)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)safe_calloc(lst_size + 1, sizeof(int *));
	while (i < lst_size)
	{
		pipes[i] = (int *)safe_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}
