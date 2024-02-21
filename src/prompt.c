/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:45:53 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 17:29:49 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*print_colored_message(const char *user, const char *path)
{
	char	*message;

	message = (char *)malloc(1024);
	if (message == NULL)
		return (NULL);
	ft_strcpy(message, "\033[1;33m┌─[\033[1;33m");
	ft_strcat(message, user);
	ft_strcat(message, "\033[1;33m]- \033[1;32m");
	ft_strcat(message, path);
	ft_strcat(message, " \n│\n└──────────> \033[1;34m🔥Ready... 🔥 \033[0m");
	return (message);
}

char	*display_prompt(void)
{
	char	*path;
	char	*read_cmd;
	// char	*msg = "minishell$ ";

	path = get_pwd();
	char *msg = print_colored_message(getenv("USER"), path);
	read_cmd = readline(msg);
	return (read_cmd);
}
