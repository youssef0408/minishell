/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 23:38:22 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;

	path = get_pwd();
	
print_in_color(BOLD_YELLOW,"┌─[");
print_in_color(BOLD_YELLOW,getenv("USER"));
print_in_color(BOLD_YELLOW,"] - ");
print_in_color(GREEN,  path);
print_in_color(BOLD_YELLOW, " \n│");
print_in_color(BOLD_YELLOW,  "\n└──────────> ");
print_in_color(BOLD_BLUE,  "🔥Ready... 🔥 ");	
	// PRINTCOLOR(BOLD_YELLOW, "┌─[%s]",getenv("USER"));
	// PRINTCOLOR(GREEN, " - %s", path);
	// PRINTCOLOR(BOLD_YELLOW, " \n%s", "│");
	// PRINTCOLOR(BOLD_YELLOW, "%s", "\n└──────────> ");
	// PRINTCOLOR(BOLD_BLUE, "%s", "🔥Ready... 🔥 ");
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
	cmd->option2 = "";
	if (tab_cmd[1])
		cmd->option = tab_cmd[1];
	if (tab_cmd[2])
		cmd->option2 = tab_cmd[2];
	//  printf("%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	// ft_strjoin( tab_cmd[1],"");
	// printf("==============%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	// free(tab_cmd[0]);
	// free(tab_cmd[1]);
}

void	exec_cmd(t_command cmd, char **envp)
{
	int	i;

	i = 0;
	if (!strcmp(cmd.name, "pwd"))
		exec_pwd(cmd.option);
	else if (!strcmp(cmd.name, "cd"))
		change_dir(cmd.option);
	else if (!strcmp(cmd.name, "exit"))
		exit(0);
	else if (!strcmp(cmd.name, "echo"))
	{
		if (!strcmp(cmd.option, "-n"))
		{
			printf("%s", parse_env(cmd.option2));
		}
		else
			printf("%s\n", parse_env(cmd.option));
	}
	else if (!strcmp(cmd.name, "env"))
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	else
	{
		
		// PRINTCOLOR(RED, "🚨%s %s\n", "command not found:", cmd.name);
		print_in_color(RED , "🚨command not found: ");
		print_in_color(RED ,cmd.name);
		printf("\n");
	}
}
