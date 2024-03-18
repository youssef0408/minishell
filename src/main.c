/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/18 12:42:58 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_command	cmd;

int	main(int argc, char **argv, char **envp)
{
	char		*cmd_str;
	t_cmd_parse	**parsed;

	(void)argc;
	(void)argv;
	cmd.env = convert_envp(envp);
	set_shlvl(&cmd.env);
	cmd.exit_status = 0;
	cmd.is_running_cmds = false;
	init_signal_handlers();
	while (true)
	{
		cmd_str = display_prompt();
		if (!cmd_str)
		{
			printf("exit\n");
			break ;
		}
		if (parse_input(cmd_str, &parsed, cmd.env) != -1)
			exec_cmd_array(&cmd, parsed);
		add_history(cmd_str);
		free_array((void **)parsed, &free_cmd_parse);
		free(cmd_str);
	}	// free and exit
	ft_lstclear(&cmd.env, &free_key_value);
	return (0);
}
