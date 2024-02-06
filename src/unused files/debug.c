/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:38:41 by ldufour           #+#    #+#             */
/*   Updated: 2024/01/10 10:16:40 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	log_printf(const char *format, ...)
{
	FILE	*logFile;
	va_list	args;

	logFile = fopen("logfile", "a");
	if (logFile == NULL)
	{
		fprintf(stderr, "Error opening log file!\n");
		return ;
	}
	va_start(args, format);
	vfprintf(logFile, format, args);
	va_end(args);
	fclose(logFile);
}

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->value)
		log_printf("(%s) ", token->value);
	else
		log_printf("(%c) ", (char)token->type);
}

void	print_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	log_printf("Command Table:\n");
	for (int i = 0; cmd->cmd_table[i] != NULL; ++i)
	{
		log_printf("  %s\n", cmd->cmd_table[i]);
	}
	log_printf("Input File: %s\n", cmd->infile ? cmd->infile : "N/A");
	log_printf("Output File: %s\n", cmd->outfile ? cmd->outfile : "N/A");
}
