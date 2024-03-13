/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:59:55 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/13 13:13:46 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*trim_str(char *str)
{
	int		i;
	int		j;
	bool	is_space;
	char	*trimmed_str;

	i = 0;
	j = 0;
	is_space = false;
	while (is_white_space(str[i]))
		i++;
	trimmed_str = calloc(sizeof(char), strlen(str) - i + 1);
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
	str = NULL;
	return (trimmed_str);
}

void	print_in_color(char *color, char *msg)
{
	printf("\033[%sm%s\033[0m", color, msg);
}

void	*safe_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = ft_calloc(nmemb, size);
	if (!ret)
		exit_prg_at_error("Malloc failure");
	return (ret);
}

int	ft_strcmp(const char *s1,const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
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

void	exit_prg_at_error(char *str)
{
	printf("Error\n");
	if (str)
		printf("%s\n", str);
	exit(EXIT_FAILURE);
}
