/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstauto_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:45:53 by bplante           #+#    #+#             */
/*   Updated: 2024/03/19 12:44:33 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lst_auto_add_back(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (1);
	ft_lstadd_back(lst, new);
	return (0);
}
