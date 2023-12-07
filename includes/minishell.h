/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/06 21:52:33 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <ctype.h>
# include <limits.h>
# include <math.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdint.h>
#include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//to print in colors//
# define printColor(color, format, ...) printf("\033[%sm" format "\033[0m", color, __VA_ARGS__)
// # define printColor(color, msg) str= "\033[  " + color + msg "\033[0m"

# define RED "1;31"
# define BLUE "1;34"
# define GREEN "1;32"
# define MAGENTA "1;35"
# define YELLOW "1;33"

typedef struct s_command
{
	char	*name;
	char	*option;
}			t_command;


void    exec_cmd(t_command cmd);
char		*display_prompt(void);
char		*get_pwd(void);
void        parse_cmd(char *str_cmd, t_command *cmd);

#endif