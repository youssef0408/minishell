/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:43 by joe_jam           #+#    #+#             */
/*   Updated: 2024/01/18 12:53:07 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void rl_replace_line (const char *text, int clear_undo);

static void	handle_ctl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	init_sigint_handler(void)
{
	struct sigaction	sig_init;

	sig_init.sa_flags = 0;
	sig_init.sa_handler = 0;
	sig_init.sa_mask = 0;
	sig_init.sa_handler = handle_ctl_c;
	if (sigaction(SIGINT, &sig_init, NULL) == -1)
		print_in_color(RED, "SIGINT ERROR!\n");
}
static void	init_sigquit_handler(void)
{
	struct sigaction	sig_quit;

	sig_quit.sa_flags = 0;
	sig_quit.sa_mask = 0;
	sig_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
		print_in_color(RED, "SIGQUIT ERROR!\n");
}

void	init_signal_handlers(void)
{
	init_sigint_handler();
	init_sigquit_handler();
}
