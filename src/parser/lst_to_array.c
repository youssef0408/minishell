/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 01:27:07 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/23 01:27:56 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	*lst_to_array(t_list *args)
{
	char	**array;
	int		i;
	int		size;

	size = ft_lstsize(args);
	array = safe_calloc(sizeof(char *), size + 1);
	i = 0;
	while (i < size)
	{
		array[i] = (char *)args->content;
		args = args->next;
		i++;
	}
	return ((void *)array);
}
