/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/13 11:37:59 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;

	path = get_pwd();
	print_in_color(BOLD_YELLOW, "┌─[");
	print_in_color(BOLD_YELLOW, getenv("USER"));
	print_in_color(BOLD_YELLOW, "] - ");
	print_in_color(GREEN, path);
	print_in_color(BOLD_YELLOW, " \n│");
	print_in_color(BOLD_YELLOW, "\n└──────────> ");
	print_in_color(BOLD_BLUE, "🔥Ready... 🔥 ");
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
	int		i;
	char	*tmp;

	tab_cmd = ft_split(str_cmd, ' ');
	if (!tab_cmd)
		return ;
	cmd->name = tab_cmd[0];
	cmd->option = "";
	cmd->option2 = "";
	cmd->cmd_str = str_cmd;
	if (!tab_cmd[1])
		return ;
	cmd->option = tab_cmd[1];
	i = 2;
	tmp = "";
	if (!tab_cmd[2])
		return ;
	while (tab_cmd[i])
	{
		if (tab_cmd[i])
			tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, tab_cmd[i]);
		i++;
	}
	cmd->option2 = tmp;
	// free(tmp);
	//  printf("%s\n%s\n", tab_cmd[0], tab_cmd[1]);
	// ft_strjoin( tab_cmd[1],"");
	// printf("==============%s\n%s\n", cmd->option, cmd->option2);
	// free(tab_cmd[0]);
	// free(tab_cmd[1]);
}

void	exec_cmd(t_command cmd, char **envp)
{
	int		i;
	char	*tmp;

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
			printf("%s", parse_env(cmd.option2));
		else
		{
			tmp = ft_strjoin(parse_env(cmd.option), parse_env(cmd.option2));
			printf("%s\n", tmp);
		}
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
		print_in_color(RED, "🚨command not found: ");
		print_in_color(RED, cmd.name);
		printf("\n");
	}
}
