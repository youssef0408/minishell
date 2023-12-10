/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:22:46 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 20:32:56 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;
	char		*cmd_str;

	(void)argc;
	(void)argv;
	while (true)
	{
		cmd_str = display_prompt();
		cmd_str = trim_str(cmd_str);
		if (strcmp(cmd_str, ""))
		{
			parse_cmd(cmd_str, &cmd);
			// printf("name: %s\n", cmd.name);
			// printf("opt: %s\n", cmd.option);
			// printf("opt2: %s\n", cmd.option2);
			exec_cmd(cmd, envp);
		}
	}
	free(cmd_str);
	return (0);
}
