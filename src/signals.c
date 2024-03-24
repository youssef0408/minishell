/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:43 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/24 16:09:29 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern t_command	g_info;

static void	handle_ctl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_info.is_running_cmds == false)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	init_sigint_handler(void)
{
	struct sigaction	sig_init;

	sig_init.sa_flags = 0;
	sigemptyset(&sig_init.sa_mask);
	sig_init.sa_handler = handle_ctl_c;
	if (sigaction(SIGINT, &sig_init, NULL) == -1)
		ft_printf_fd("SIGINT ERROR!\n", 2);
}

static void	init_sigquit_handler(void)
{
	struct sigaction	sig_quit;

	sig_quit.sa_flags = 0;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
		ft_printf_fd("SIGINT ERROR!\n", 2);
}

void	init_signal_handlers(void)
{
	init_sigint_handler();
	init_sigquit_handler();
}
