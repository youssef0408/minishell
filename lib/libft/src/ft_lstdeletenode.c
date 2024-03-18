/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdeletenode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:32:34 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/18 16:32:19 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdeletenode(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL || node == NULL)
		return ;
	if (tmp == node)
	{
		*lst = tmp->next;
		del(node->content);
		node->content = NULL;
		free(node);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			del(node->content);
			node->content = NULL;
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
}
