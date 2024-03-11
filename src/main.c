/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/11 17:43:59 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	t_list		*cmd_list;
	char		*cmd_str;

	cmd.env = envp;
	(void)argc;
	(void)argv;
	while (true)
	{
		init_signal_handlers();
		cmd_list = NULL;
		cmd_str = display_prompt();
		cmd_str = trim_str(cmd_str);
		if (ft_strcmp(cmd_str, ""))
		{
			if (parse_input(cmd_str, &cmd.parsed, cmd.env) != -1)
			{
				init_cmd(cmd_str, &cmd);
				exec_cmd(cmd, cmd.env);
			}
			add_history(cmd_str);
		}
		if (!cmd_str)
		{
			printf("exit\n");
			break ;
		}
	}
	free(cmd_str);
	return (0);
}
