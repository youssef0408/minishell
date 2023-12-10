/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:59:55 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 21:36:22 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	ft_count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**split_with_delimiter(char *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
    
	result = calloc(ft_count_words(s, c) + 3 ,(sizeof(char *) ));
	if (!result)
		return (NULL);
	while (s[j])
	{
		if (s[j] != c)
			j++;
		else
		{
			if (i != j)
			{
				result[k] = ft_substr(s, i, j - i);
				k++;
			}
			i = j;
			j++;
		}
	}
	result[k] = ft_substr(s, i, j - i);
   
	return (result);
}






void print_in_color(char *color, char *msg) 
{
    printf("\033[%sm%s\033[0m", color, msg );
}
