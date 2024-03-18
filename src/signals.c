/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:43 by joe_jam           #+#    #+#             */
/*   Updated: 2024/03/18 12:45:39 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


extern t_command cmd;
void		rl_replace_line(const char *text, int clear_undo);

static void	handle_ctl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (cmd.is_running_cmds == false)
	{
		rl_replace_line("", 0);
		rl_forced_update_display();
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
		print_in_color(RED, "SIGINT ERROR!\n");
}
static void	init_sigquit_handler(void)
{
	struct sigaction	sig_quit;

	sig_quit.sa_flags = 0;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
		print_in_color(RED, "SIGQUIT ERROR!\n");
}

void	init_signal_handlers(void)
{
	init_sigint_handler();
	init_sigquit_handler();
}
