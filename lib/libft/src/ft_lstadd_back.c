/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:51:26 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/21 16:24:17 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	last_elem = NULL;
	if (!lst || !new)
		return ;
	new->previous = NULL;
	if (*lst)
	{
		last_elem = ft_lstlast(*lst);
		last_elem->next = new;
		new->previous = last_elem;
	}
	else
		*lst = new;
}
