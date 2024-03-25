/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:37:27 by ldufour           #+#    #+#             */
/*   Updated: 2024/03/25 15:19:35 by bplante          ###   ########.fr       */
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
	add_to_env(&g_info.env, "?", ft_itoa(0));
	add_to_env(&g_info.env, "0", ft_strdup("minishell"));
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
		{
			if (!is_empty_cmd(g_info.cmds))
			{
				exec_cmd_array(&g_info, g_info.cmds);
				add_history(cmd_str);
			}
		}
		free_array((void **)g_info.cmds, &free_cmd_parse);
		free(cmd_str);
	}
	rl_clear_history();
}

void	exit_cleanup(void)
{
	ft_lstclear(&g_info.env, &free_key_value);
	printf("\17exit\n");
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

// TODO: when CTL+D exit should be written on the same lline as the prompt