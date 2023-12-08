/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:22:46 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/08 01:45:27 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{	
	t_command	cmd;
	char		*cmd_str;

	while (true)
	{
		cmd_str = display_prompt();
		cmd_str = trim_str(cmd_str);
		if (strcmp(cmd_str, ""))
		{  
			parse_cmd(cmd_str, &cmd);
			exec_cmd(cmd);
			// printf("name: %s\n", cmd.name);
			// printf("opt: %s\n", cmd.option);
		}
	}
	free(cmd_str);
	return (0);
}
