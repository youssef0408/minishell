/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:43:04 by bplante           #+#    #+#             */
/*   Updated: 2024/03/23 00:07:01 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_key(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

void	remove_from_env(t_list **env, const char *key)
{
	t_list		*node;

	node = get_kv_node(*env, key);
	if (node)
		ft_lstdeletenode(env, node, &free_key_value);
}

void	add_to_env(t_list **env, const char *key, char *value)
{
	t_key_value	*kv;
	t_list		*node;

	node = get_kv_node(*env, key);
	if (!value)
		value = ft_strdup("");
	if (node)
	{
		kv = (t_key_value *)node->content;
		free(kv->value);
		kv->value = value;
	}
	else
	{
		kv = safe_calloc(sizeof(t_key_value), 1);
		kv->key = ft_strdup(key);
		kv->value = value;
		lst_auto_add_back(env, (void *)kv);
	}
}

char	**env_list_to_envp(t_list *env)
{
	char		**env_array;
	int			i;
	char		*temp;
	t_key_value	*kv;

	i = ft_lstsize(env);
	env_array = safe_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env)
	{
		kv = (t_key_value *)env->content;
		temp = ft_strjoin(kv->key, "=");
		if (!temp)
			exit_prg_at_error("malloc failure");
		env_array[i] = ft_strjoin(temp, kv->value);
		if (!temp)
			exit_prg_at_error("malloc failure");
		i++;
		env = env->next;
		free(temp);
	}
	return (env_array);
}

const char	*get_value_with_key(t_list *env, const char *key)
{
	t_list		*node;
	t_key_value	*kv;

	node = get_kv_node(env, key);
	if (node)
	{
		kv = (t_key_value *)node->content;
		return (kv->value);
	}
	return (NULL);
}
