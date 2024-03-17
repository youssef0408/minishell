/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/17 14:33:31 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	char		*cmd_str;
	t_cmd_parse	**parsed;

	(void)argc;
	(void)argv;
	cmd.env = convert_envp(envp);
	set_shlvl(&cmd.env);
	while (true)
	{
		init_signal_handlers();
		cmd_str = display_prompt();
		if (!cmd_str)
		{
			printf("exit\n");
			break ;
		}
		if (parse_input(cmd_str, &parsed, cmd.env) != -1)
			exec_cmd_array(&cmd, parsed);
		add_history(cmd_str);
	}
	free(cmd_str);
	// free and exit
	return (0);
}
