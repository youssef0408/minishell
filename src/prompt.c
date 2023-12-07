/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/06 21:59:47 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;

	path = get_pwd();
	printColor(GREEN, "%s\n", path);
	printColor(RED, "\t%s", "======>🔥");
	read_cmd = readline("");
	return (read_cmd);
}

void	parse_cmd(char *str_cmd, t_command *cmd)
{
	char	**tab_cmd;

	//(TO_DO) ignore white spaces and transform it to just one space
	tab_cmd = ft_split(str_cmd, ' ');
	if (!tab_cmd)
		return ;
	// printf("%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	cmd->name = tab_cmd[0];
	cmd->option = "";
	if (tab_cmd[1])
		cmd->option = tab_cmd[1];
	// free(tab_cmd[0]);
	// free(tab_cmd[1]);
}

void	exec_cmd(t_command cmd)
{
	if (!strcmp(cmd.name, "pwd"))
	{
        if(!strcmp(cmd.option, ""))
		    printf("%s\n", get_pwd());
        else
            printColor(RED, "%s%s\n", cmd.name,": too many arguments");
	}
    else
    	printColor(RED, "%s %s\n", "command not found:", cmd.name);
}
