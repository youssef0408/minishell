/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:59:55 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/08 00:57:55 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool is_white_space(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

char *trim_str(char *str)
{
    int i = 0;
    int j = 0;
    bool is_space = false;
    char *trimmed_str;

    while (is_white_space(str[i]))
        i++;
    trimmed_str = calloc(sizeof(char), strlen(str) - i + 1);
    // if (is_white_space(str[0]))
    // {
    //      trimmed_str[j] = ' ';
    //      j = 1;
    // }
    while (str[i])
    {
        if (is_white_space(str[i]))
            is_space = true;
        if (!is_white_space(str[i]))
        {
            if (is_space)
            {
                trimmed_str[j++] = ' ';
                is_space = false;
            }
            trimmed_str[j++] = str[i];
        }
        i++;
    }
    // if (is_white_space(str[i - 1]))
    // {
    //      trimmed_str[j] = ' ';
    //      j++;
    // }
    // trimmed_str[j] = '\0';
    str = NULL;
    return trimmed_str;
}

void	clean_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
