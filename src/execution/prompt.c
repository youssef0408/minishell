/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/26 23:07:29 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*variadic_strjoin(unsigned int arg_quantity, ...)
{
	va_list			arg_list;
	unsigned int	i;
	char			*arg_buffer;
	char			*temp;
	char			*result;

	va_start(arg_list, arg_quantity);
	i = 0;
	result = NULL;
	while (i < arg_quantity)
	{
		arg_buffer = va_arg(arg_list, char *);
		if (result == NULL)
			result = ft_strdup(arg_buffer);
		else
		{
			temp = ft_strjoin(result, arg_buffer);
			free(result);
			result = temp;
		}
		i++;
	}
	va_end(arg_list);
	return (result);
}

static char	*concatenate_prompt(char *name, char *pwd, char *end)
{
	char	*prompt;

	prompt = variadic_strjoin(9, ESC_BOLD_PURPLE, "[", name, "]-",
			ESC_BOLD_CYAN, pwd, ESC_BOLD_PURPLE, end, ESC_RESET_COLOR);
	free(name);
	free(pwd);
	free(end);
	return (prompt);
}

char	*display_prompt(t_list env)
{
	char	*name;
	char	*path;
	char	*read_cmd;
	char	*msg;
	char	*end;

	name = ft_strdup(get_value_with_key(&env, "USER"));
	path = get_pwd();
	end = ft_strdup("$ ");
	msg = concatenate_prompt(name, path, end);
	read_cmd = readline(msg);
	return (read_cmd);
}
