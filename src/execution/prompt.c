/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/26 01:06:27 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char	*create_prompt(const char *user, const char *path)
// {
// 	char	*tmp;
// 	char	*message;

// 	tmp = ft_strjoin("\033[1;33m[\033[1;33m", user);
// 	message = ft_strjoin(tmp, "\033[1;33m] \033[1;32m");
// 	free(tmp);
// 	tmp = ft_strjoin(message, path);
// 	free(message);
// 	message = ft_strjoin(tmp, "\033[1;34m $ \033[0m");
// 	free(tmp);
// 	return (message);
// }

// char	*display_prompt(void)
// {
// 	char	*path;
// 	char	*read_cmd;
// 	char	*msg;

// 	path = get_pwd();
// 	msg = create_prompt(getenv("USER"), path);
// 	read_cmd = readline(msg);
// 	free(path);
// 	free(msg);
// 	return (read_cmd);
// }

// char	*display_prompt(void)
// {
// 	char	*read_cmd;
// 	char	*msg;

// 	msg = "minishell$ ";
// 	read_cmd = readline(msg);
// 	return (read_cmd);
// }
// static char	*print_colored_message(const char *user, const char *path)
// {
// 	char	*message;

// 	message = (char *)malloc(1024);
// 	if (message == NULL)
// 		return (NULL);
// 	ft_strcpy(message, "\033[1;33m┌─[\033[1;33m");
// 	ft_strcat(message, user);
// 	ft_strcat(message, "\033[1;33m]- \033[1;32m");
// 	ft_strcat(message, path);
// 	ft_strcat(message, " \n│\n└──────────> \033[1;34m🔥Ready... 🔥 \033[0m");
// 	return (message);
// }
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

	prompt = variadic_strjoin(7, ESC_BOLD_RED, name, ESC_BOLD_PURPLE, pwd,
			ESC_BOLD_RED, end, ESC_RESET_COLOR);
	free(name);
	free(pwd);
	free(end);
	return (prompt);
}

char	*display_prompt(void)
{
	char *user = getenv("USER");
	char *path;
	char *name = ft_strdup(user);
	char *read_cmd;
	char *msg;
	char *end = ft_strdup("$ ");
	path = get_pwd();
	msg = concatenate_prompt(name, path, end);

	read_cmd = readline(msg);
	return (read_cmd);
}