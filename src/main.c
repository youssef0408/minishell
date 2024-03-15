/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/14 23:37:00 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*cmd_list;
	char		*cmd_str;

	cmd.env = convert_envp(envp);
	(void)argc;
	(void)argv;
	while (true)
	{
		init_signal_handlers();
		cmd_list = NULL;
		cmd_str = display_prompt();
		if (!cmd_str)
		{
			printf("exit\n");
			break ;
		}
		if (parse_input(cmd_str, &cmd.parsed, cmd.env) != -1)
		{
			// init_cmd(cmd_str, &cmd);
			exec_cmd(&cmd, cmd.parsed);
		}
		add_history(cmd_str);
	}
	free(cmd_str);
	// free and exit
	return (0);
}
