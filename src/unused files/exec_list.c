/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:25:20 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/31 13:59:43 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_redirection(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->fd_input = open(cmd->infile, O_RDONLY);
		dup2(cmd->fd_input, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		if (cmd->amend == true)
			cmd->fd_output = open(cmd->outfile, O_CREAT | O_RDWR | O_APPEND);
		else
			cmd->fd_output = open(cmd->outfile, O_CREAT | O_RDWR | O_TRUNC,
					0644);
		dup2(cmd->fd_output, STDOUT_FILENO);
	}
}
/*
 * Execute the command specified in the given command list.
 * 
 * Parameters:
 *   - cmd_list: A linked list node containing the command structure.
 * 
 * Details:
 *   - Extracts the command structure from the command list.
 *   - Logs the command being executed.
 *   - Handles redirection for the command.
 *   - Checks if the command is a built-in command and executes it if so.
 *   - If not a built-in command, attempts to execute the external command using execve.
 *   - Prints an error message using perror if execve fails.
 */
void	exec_leon(t_list *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->content;
	if (cmd && cmd->cmd_table)
	{
		log_printf("Executing: %s\n", cmd->cmd_table[0]);
		exec_redirection(cmd);
		if(execve(cmd->cmd_table[0], cmd->cmd_table, NULL)== -1)
			perror("execve");
    }
	}

void	process_exec(int i, int lst_size, int **pipes, t_list *cmd_list)
{
	t_command cmd;
	
	// cmd = NULL;
	if (lst_size == 1)
	{
		if(exec_builtin(cmd, cmd.env))
			exec_leon(cmd_list);
	}
	if (i == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	else if (i == lst_size - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(lst_size - 1, pipes);
	}
	exec_leon(cmd_list);
	exit(EXIT_SUCCESS);
}
// BUILT_IN
void	process_fork(t_list *cmd_list, int lst_size)

                  // Faire un bool si built in detecter pour skipper les affaires)
{
	pid_t	*pid;
	int		i;
	int		status;
	int		**pipes;

	pid = (pid_t *)safe_calloc(lst_size, sizeof(pid_t));
	pipes = pipes_creation(lst_size);
	i = -1;
	while (++i < lst_size && cmd_list)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0)
			process_exec(i, lst_size, pipes, cmd_list);
		else
			cmd_list = cmd_list->next;
	}
	close_pipes(lst_size - 1, pipes);
	i = -1;
	while (++i < lst_size)
		waitpid(pid[i], &status, 0);
	free(pid);
	free_array((void **)pipes);
}

void	main_exec(t_list *cmd_list, char **envp)
{
	int	nb_process;

	nb_process = ft_lstsize(cmd_list);
	update_cmd_list(cmd_list, envp);
	process_fork(cmd_list, nb_process);
}

// Faire un bool si built in detecter pour skipper les affaires
