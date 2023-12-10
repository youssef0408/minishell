/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:35:09 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/09 01:47:41 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (!del || !lst || !*lst)
		return ;
	while (*lst && lst)
	{
		nxt = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nxt;
	}
}
