/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:06:04 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/23 00:07:21 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_key_value(void *key_value)
{
	t_key_value	*kv;

	if (!key_value)
		return ;
	kv = (t_key_value *)key_value;
	free(kv->key);
	free(kv->value);
	free(kv);
}

char	*join_key_value(t_list *node)
{
	t_key_value	*kv;
	char		*temp;
	char		*ret;

	if (!node)
		return (NULL);
	kv = node->content;
	temp = ft_strjoin(kv->key, "=");
	ret = ft_strjoin(temp, kv->value);
	free(temp);
	return (ret);
}

t_list	*convert_envp(char **envp)
{
	t_list		*env;
	t_key_value	*kv;
	int			i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		kv = safe_calloc(sizeof(t_key_value), 1);
		kv->key = get_key(envp[i]);
		kv->value = ft_strdup(&envp[i][ft_strlen(kv->key) + 1]);
		lst_auto_add_back(&env, (void *)kv);
		i++;
	}
	return (env);
}

t_list	*get_kv_node(t_list *env, const char *key)
{
	t_key_value	*kv;

	while (env)
	{
		kv = (t_key_value *)env->content;
		if (ft_strcmp(key, kv->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
