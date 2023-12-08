/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/08 02:44:35 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//to print in colors//
# define printColor(color, format, ...) printf("\033[%sm" format "\033[0m", color, __VA_ARGS__)
// # define printColor(color, msg) str= "\033[  " + color + msg "\033[0m"

# define RED "1;31"
# define GREEN "1;32"
# define YELLOW "1;33"
# define BLUE "1;34"
# define MAGENTA "1;35"
# define CYAN "1;36"
# define WHITE "1;37"
# define BOLD_RED "1;91"
# define BOLD_GREEN "1;92"
# define BOLD_YELLOW "1;93"
# define BOLD_BLUE "1;94"
# define BOLD_MAGENTA "1;95"
# define BOLD_CYAN "1;96"
# define BOLD_WHITE "1;97"



typedef struct s_command
{
	char	*name;
	char	*option;
}			t_command;

void		exec_cmd(t_command cmd);
char		*display_prompt(void);
char		*get_pwd(void);
void		parse_cmd(char *str_cmd, t_command *cmd);
bool		is_white_space(char c);
char		*trim_str(char *str);
void change_dir(char *str);
char *parse_env(char *str);
void exec_pwd(char *cmd);
void	clean_table(char **tab);
#endif