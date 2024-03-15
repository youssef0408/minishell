/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:20:32 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/15 16:41:07 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#define FD_IN 0
#define FD_OUT 1
#define NO_RED -2

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
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			// error message
			break ;
		}
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
	i = 0;
	while (cmd->redirections[i])
	{
		if (cmd->redirections[i]->redirect_type == R_AMBIGUOUS)
		{
			printf("%s: ambiguous redirect\n", cmd->redirections[i]->str);
			break ;
		}
		else if (cmd->redirections[i]->redirect_type == R_IN_FILE)
		{
			if (fds[FD_IN] != -2)
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
			if (fds[FD_OUT] != -2)
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
			if (fds[FD_OUT] != -2)
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
			if (fds[FD_IN] != -2)
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

	if (cmd->redirections)
		open_redirections(cmd, fds);
	if (fds[FD_IN] == -1 || fds[FD_OUT] == -1)
	{
		info->exit_status = 1;
		handle_exit_status(info);
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
		old_std_in = dup(1);
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
		dup2(old_std_in, 1);
		close(old_std_in);
	}
}

int *create_pipe_array(t_cmd_parse **cmds)
{
	int size = get_cmd_count(cmds) * 2;
	
}

void	exec_cmd(t_command *info, t_cmd_parse **cmds)
{
	// check if solo command and builtin
	if (get_cmd_count(cmds) == 1 && is_builtin(cmds[0]->args[0]))
		exec_single_builtin(info, cmds[0]);
	else
	{
		
	}
}

void	old_exec_cmd(t_command *info, t_cmd_parse **cmd)
{
	int		i;
	pid_t	pid;

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
			if (get_cmd_path(info, cmd[0]->args) == 0)
				execve(cmd[0]->args[0], cmd[0]->args,
					env_list_to_envp(info->env));
			print_in_color(RED, "🚨command not found:  ");
			print_in_color(RED, cmd[0]->args[0]);
			printf("\n");
		}
		exit(info->exit_status);
	}
	waitpid(pid, NULL, 0);
	// return (0);
}
