/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:51:44 by yothmani          #+#    #+#             */
/*   Updated: 2024/01/18 13:30:08 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	result = calloc(ft_count_words(s, c) + 3, (sizeof(char *)));
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

char	*parse_env2(t_command cmd, char *str)
{
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;
	char	*key;
	int		idx;

	result = "";
	tmp = split_with_delimiter(str, '$');
	if (!tmp)
		return (str);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] != '$')
			result = ft_strjoin(result, tmp[i]);
		else
		{
			if (ft_strlen(tmp[i]) == 1)
				result = ft_strjoin(result, tmp[i]);
			else
			{
				key = ft_substr(tmp[i], 1, ft_strlen(tmp[i]));
				idx = find_in_env(key, cmd.env);
				env_value = cmd.env[idx];
				if (env_value)
				{
					env_value = ft_substr(env_value, ft_strlen(key)+1, ft_strlen(env_value));
					result = ft_strjoin(result, env_value);
				}
			}
		}
		i++;
	}
	clean_table(tmp);
	return (result);
}

char	*parse_env(char *str)
{
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;

	result = "";
	tmp = split_with_delimiter(str, '$');
	if (!tmp)
		return (str);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] != '$')
			result = ft_strjoin(result, tmp[i]);
		else
		{
			if (ft_strlen(tmp[i]) == 1)
				result = ft_strjoin(result, tmp[i]);
			else
			{
				env_value = getenv(ft_substr(tmp[i], 1, ft_strlen(tmp[i])));
				if (env_value)
					result = ft_strjoin(result, env_value);
			}
		}
		i++;
	}
	clean_table(tmp);
	return (result);
}
