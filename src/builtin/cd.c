/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:39:16 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/08 02:52:09 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_dir(char *str)
{
	char	*home;

	home = getenv("HOME");
	if (!str || !strcmp(str, "") || !strcmp(str, "~"))
		str = home;
	else
	{
		str = parse_env(str);
		if (!str || !strcmp(str, " "))
		//à verifier : la condition "!str" nest plus necessaire je renvoie plus jamais null
		{
			printColor(RED, "🚨cd: no such file or directory: %s\n", str);
			return ;
		}
	}
	if (chdir(str) != 0)
		printColor(RED, "🚨cd: no such file or directory: %s\n", str);
}

char	*parse_env(char *str)
{
	// je pense que je dois voir l'histoire des access avant de changer dir
	char	**tmp;
	char	*result;
	int		i;
	char	*env_value;

	result = NULL;
	tmp = ft_split(str, '$');
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		env_value = getenv(tmp[i]);
		if (env_value)
		{
			if (result)
			{
				free(result);
				result = ft_strjoin(result, env_value);
			}
			else
				result = ft_strdup(env_value);
		}
		else
		{
			if (result)
			{
				free(result);
				result = ft_strjoin(result, tmp[i]);
			}
		}
		i++;
	}
	if (!result)
		result = ft_strdup(str);
	clean_table(tmp);
	return (result);
}
