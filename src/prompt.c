/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/08 03:13:06 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;

	path = get_pwd();
	printColor(BOLD_YELLOW, "%s", "[]===<");
	printColor(BOLD_BLUE, "%s", " current dir: ");
	printColor(BOLD_GREEN, "%s\n", path);
	printColor(BOLD_YELLOW, "%s\n", "[]");
	printColor(BOLD_YELLOW, "%s","[]======> ");
	printColor(BOLD_BLUE, "%s","🔥Ready to Command the Shell... (✗_✗)🔥 ");
	read_cmd = readline("");
	return (read_cmd);
}

void	parse_cmd(char *str_cmd, t_command *cmd)
{
	char	**tab_cmd;

	tab_cmd = ft_split(str_cmd, ' ');
	if (!tab_cmd)
		return ;
	cmd->name = tab_cmd[0];
	cmd->option = "";
	if (tab_cmd[1])
		cmd->option = tab_cmd[1];
	//  printf("%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	// ft_strjoin( tab_cmd[1],"");
	// printf("==============%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	// free(tab_cmd[0]);
	// free(tab_cmd[1]);
}

void	exec_cmd(t_command cmd)
{
	if (!strcmp(cmd.name, "pwd"))
        exec_pwd(cmd.option);
	else if(!strcmp(cmd.name, "cd"))
		change_dir(cmd.option);
	else if(!strcmp(cmd.name, "exit"))
		exit(0);
    else
    	printColor(RED, "🚨%s %s\n", "command not found:", cmd.name);
}
