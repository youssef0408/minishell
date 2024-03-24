/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/24 16:24:07 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_command	g_info;

bool	is_tty_valid(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_printf_fd("Standard file descriptors not bound to a tty\n", 2);
		return (false);
	}
	return (true);
}

void	prog_init(char **envp)
{
	g_info.env = convert_envp(envp);
	set_shlvl(&g_info.env);
	g_info.exit_status = 0;
	g_info.is_running_cmds = false;
	init_signal_handlers();
	remove_from_env(&g_info.env, "OLDPWD");
}

void	run_shell_loop(void)
{
	char	*cmd_str;

	while (true)
	{
		cmd_str = display_prompt();
		if (!cmd_str)
			break ;
		if (parse_input(cmd_str, &g_info.cmds, g_info.env) != -1)
			exec_cmd_array(&g_info, g_info.cmds);
		add_history(cmd_str);
		free_array((void **)g_info.cmds, &free_cmd_parse);
		free(cmd_str);
	}
	rl_clear_history();
}

void	exit_cleanup(void)
{
	ft_lstclear(&g_info.env, &free_key_value);
	printf("\rexit\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!is_tty_valid())
		return (EXIT_FAILURE);
	prog_init(envp);
	run_shell_loop();
	exit_cleanup();
	return (EXIT_SUCCESS);
}
