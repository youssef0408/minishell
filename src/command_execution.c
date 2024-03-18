/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/18 16:55:40 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#define FD_IN 0
#define FD_OUT 1
#define NO_RED -2
#define EOINTA -3

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

bool	is_builtin(char *name)
{
	char	*builtins[8];
	int		i;

	if (!name)
		return (false);
	builtins[0] = "echo";
	builtins[1] = "env";
	builtins[2] = "cd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "exit";
	builtins[6] = "pwd";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], name) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	here_doc(char *del)
{
	int		fd_pipe[2];
	char	*line;
	char	*temp;

	pipe(fd_pipe);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(line, "\n");
		write(fd_pipe[1], temp, ft_strlen(temp));
		free(line);
		free(temp);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

void	open_redirections(t_cmd_parse *cmd, int *fds)
{
	int	i;

	fds[FD_IN] = NO_RED;
	fds[FD_OUT] = NO_RED;
	if (!cmd->redirections)
		return ;
	i = 0;
	while (cmd->redirections[i])
	{
		if (cmd->redirections[i]->redirect_type == R_AMBIGUOUS)
		{
			printf("%s: ambiguous redirect\n", cmd->redirections[i]->str);
			fds[FD_IN] = -1;
			fds[FD_OUT] = -1;
			break ;
		}
		else if (cmd->redirections[i]->redirect_type == R_IN_FILE)
		{
			if (fds[FD_IN] != NO_RED)
				close(fds[FD_IN]);
			fds[FD_IN] = open(cmd->redirections[i]->str, O_RDONLY);
			if (fds[FD_IN] == -1)
			{
				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
				break ;
			}
		}
		else if (cmd->redirections[i]->redirect_type == R_OUT_APPEND)
		{
			if (fds[FD_OUT] != NO_RED)
				close(fds[FD_OUT]);
			fds[FD_OUT] = open(cmd->redirections[i]->str,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fds[FD_OUT] == -1)
			{
				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
				break ;
			}
		}
		else if (cmd->redirections[i]->redirect_type == R_OUT_TRUNC)
		{
			if (fds[FD_OUT] != NO_RED)
				close(fds[FD_OUT]);
			fds[FD_OUT] = open(cmd->redirections[i]->str,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fds[FD_OUT] == -1)
			{
				printf("%s: %s\n", cmd->redirections[i]->str, strerror(errno));
				break ;
			}
		}
		else
		{
			if (fds[FD_IN] != NO_RED)
				close(fds[FD_IN]);
			fds[FD_IN] = here_doc(cmd->redirections[i]->str);
		}
		i++;
	}
}

void	exec_single_builtin(t_command *info, t_cmd_parse *cmd)
{
	int	fds[2];
	int	old_std_in;
	int	old_std_out;

	open_redirections(cmd, fds);
	if (fds[FD_IN] == -1 || fds[FD_OUT] == -1)
	{
		info->exit_status = 1;
		return ;
	}
	if (fds[FD_IN] != NO_RED)
	{
		old_std_in = dup(0);
		dup2(fds[FD_IN], 0);
		close(fds[FD_IN]);
	}
	if (fds[FD_OUT] != NO_RED)
	{
		old_std_out = dup(1);
		dup2(fds[FD_OUT], 1);
		close(fds[FD_OUT]);
	}
	exec_builtin(info, cmd);
	if (fds[FD_IN] != NO_RED)
	{
		dup2(old_std_in, 0);
		close(old_std_in);
	}
	if (fds[FD_OUT] != NO_RED)
	{
		dup2(old_std_out, 1);
		close(old_std_out);
	}
}

int	*create_pipe_array(t_cmd_parse **cmds)
{
	int	size;
	int	*fd_array;
	int	i;
	int	temp;

	size = get_cmd_count(cmds) * 2;
	fd_array = safe_calloc(size + 1, sizeof(int));
	fd_array[size] = EOINTA;
	fd_array[size - 1] = 1;
	i = 1;
	while (i < size - 1)
	{
		pipe(&fd_array[i]);
		temp = fd_array[i];
		fd_array[i] = fd_array[i + 1];
		fd_array[i + 1] = temp;
		i += 2;
	}
	return (fd_array);
}

int	*create_pid_array(t_cmd_parse **cmds)
{
	int	size;
	int	*pids;

	size = get_cmd_count(cmds);
	pids = safe_calloc(size + 1, sizeof(int));
	pids[size] = EOINTA;
	return (pids);
}

void	manage_redirections(int *fds, t_cmd_parse **cmds)
{
	int	io[2];
	int	i;

	i = 0;
	while (cmds[i])
	{
		open_redirections(cmds[i], io);
		if (io[FD_IN] != NO_RED)
		{
			if (fds[i * 2 + FD_IN != 0])
				close(fds[i * 2 + FD_IN]);
			fds[i * 2 + FD_IN] = io[FD_IN];
		}
		if (io[FD_OUT] != NO_RED)
		{
			if (fds[i * 2 + FD_OUT] != 1)
				close(fds[i * 2 + FD_OUT]);
			fds[i * 2 + FD_OUT] = io[FD_OUT];
		}
		i++;
	}
}

void	close_irrelevant_fds(int *fds, int pos)
{
	int	i;

	i = 0;
	while (fds[i] != EOINTA)
	{
		if (pos * 2 != i && pos * 2 + 1 != i)
			close(fds[i]);
		i++;
	}
}

void	close_non_std_fds(int *fds)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (fds[i] != EOINTA)
	{
		if (fds[i] != 0 && fds[i] != 1 && fds[i] != 2)
			close(fds[i]);
		i++;
	}
}

void	create_child(t_command *info, t_cmd_parse **cmds, int pos)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("fork failed\n");
	if (pid == 0)
	{
		close_irrelevant_fds(info->fds, pos);
		dup2(info->fds[pos * 2 + FD_IN], 0);
		dup2(info->fds[pos * 2 + FD_OUT], 1);
		if (is_builtin(cmds[pos]->args[0]))
			exec_builtin(info, cmds[pos]);
		else if (!cmds[pos]->args[0])
		{
			info->exit_status = 0;
		}
		else
		{
			if (get_cmd_path(info, cmds[pos]->args) == 0)
			{
				execve(cmds[pos]->args[0], cmds[pos]->args,
					env_list_to_envp(info->env));
				perror("minishell: ");
			}
			else
			{
				print_in_color(RED, "🚨command not found:  ");
				print_in_color(RED, cmds[pos]->args[0]);
				printf("\n");
				info->exit_status = 127;
			}
		}
		exit(info->exit_status);
	}
	info->pids[pos] = pid;
}

int	wait_all(int *pids)
{
	int	i;
	int	exit_st;

	i = 0;
	while (pids[i] != EOINTA)
	{
		waitpid(pids[i], &exit_st, 0);
		i++;
	}
	return (exit_st / 256);
}

void	exec_cmd_array(t_command *info, t_cmd_parse **cmds)
{
	int	i;

	if (get_cmd_count(cmds) == 1 && is_builtin(cmds[0]->args[0]))
		exec_single_builtin(info, cmds[0]);
	else
	{
		info->fds = create_pipe_array(cmds);
		info->pids = create_pid_array(cmds);
		manage_redirections(info->fds, cmds);
		info->is_running_cmds = true;
		i = 0;
		while (cmds[i])
		{
			create_child(info, cmds, i);
			i++;
		}
		close_non_std_fds(info->fds);
		info->exit_status = wait_all(info->pids);
		free(info->fds);
		free(info->pids);
	}
	handle_exit_status(info);
	info->is_running_cmds = false;
}
